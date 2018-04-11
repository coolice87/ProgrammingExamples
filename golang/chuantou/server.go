//server端,运行在有外网IP的服务器上
package main

import (
	"fmt"
	"flag"
	"net"
	"os"
	"runtime"
	"strconv"
	"time"
)

var pl = fmt.Println
var pf = fmt.Printf

var localPort *string = flag.String("localPort", "3002", "usr访问端口")
var remotePort *string = flag.String("remotePort", "20012", "与client通讯端口")

//与client相关的conn
type client struct {
	conn net.Conn
	err chan bool
	//心跳包通道
	heart chan bool
	writ chan bool
	
	recv chan []byte
	send chan []byte
}

//读取client过来的数据
func (self *client) read() {
	for {
		self.conn.SetReadDeadline(time.Now().Add(time.Second * 40))
		var recv []byte = make([]byte, 10240)

		n,err := self.conn.Read(recv)
		if err != nil {
			self.heart <- true
			self.err <- true
			self.writ <- true
			pl("长时间未传输或者client已经关闭, 断开并继续accept新的tcp, ", err)			
		}

		//收到心跳包
		if recv[0] == 'h' && recv[1] == 'h' {
			self.conn.Write([]byte("hh"))
			continue
		} 

		self.recv <- recv[:n]
	}
}

func (self client) write() {
	for {
		var send []byte = make([]byte, 10240)
		select {
		case send = <-self.send:
			self.conn.Write(send)
		case <- self.writ :
			pl("close client write")
			break
		}
	}
}

//与usr相关的conn
type user struct {
	conn net.Conn
	err chan bool
	writ chan bool

	recv chan []byte
	send chan []byte
}

func (self user) read() {
	self.conn.SetReadDeadline(time.Now().Add(time.Millisecond * 800))

	for {
		var recv []byte = make([]byte, 10240)
		n,err := self.conn.Read(recv)
		self.conn.SetReadDeadline(time.Time{})
		if err != nil {
			self.err <- true
			self.writ <- true
			pl("读取user fail", err)
			break
		}
		self.recv <- recv[:n]
	}
}

func (self user) write() {
	for {
		var send []byte = make([]byte, 10240)
		select {
		case send = <- self.send :
			self.conn.Write(send)
		case <- self.writ :
			pl("close user write")
			break
		}
	}
}

func main() {
	runtime.GOMAXPROCS(runtime.NumCPU())

	flag.Parse()
	if flag.NFlag() != 2 {
		flag.PrintDefaults()
		os.Exit(1)
	}
	local,_ := strconv.Atoi(*localPort)
	remote,_ := strconv.Atoi(*remotePort)
	if !(local >=0 && local <65536) {
		pl("local port is invalid")
		os.Exit(1)
	}
	if !(remote >=0 && remote <65536) {
		pl("remote port is invalid")
		os.Exit(1)
	}

	c,err := net.Listen("tcp", ":"+*remotePort)
	log(err)
	u,err := net.Listen("tcp", ":"+*localPort)
	log(err)
	
TOP:
	//listen user conn
	uconn := make(chan net.Conn)
	go goaccept(u, uconn)
	//一定要先接受client
	pl("准备好连接")
	clientconn := accept(c)
	pl("client have connect", clientconn.LocalAddr().String())
	recv := make(chan []byte)
	send := make(chan []byte)
	heart := make(chan bool, 1)
	er := make(chan bool, 1)
	writ := make(chan bool)
	client := &client{clientconn, er, heart, writ, recv, send}
	go client.read()
	go client.write()

	for {
		select {
		case <- client.heart :
			goto TOP
		case userconn := <- uconn :
			recv = make(chan []byte)
			send = make(chan []byte)
			er = make(chan bool, 1)
			writ = make(chan bool)
			user := &user{userconn, er, writ, recv, send}
			go user.read()
			go user.write()
			go handle(client, user)
			goto TOP 
		}
	}
}

func accept(con net.Listener) net.Conn {
	corU,err := con.Accept()
	logExit(err)
	return corU
}

func goaccept(con net.Listener, uconn chan net.Conn) {
	corU,err := con.Accept()
	logExit(err)
	uconn <- corU
}

func log(err error) {
	if err != nil {
		pf("error: %v\n", err)
	}
}

func logExit(err error) {
	if err != nil {
		pl("Have closed ", err)
		runtime.Goexit()
	}
}

//两个socket衔接处理
func handle(client *client, user *user) {
	for {
		var clientrecv = make([]byte, 10240)
		var userrecv = make([]byte, 10240)
		select {
		case clientrecv = <- client.recv :
			user.send <-clientrecv
		case userrecv = <-user.recv:
			client.send <- userrecv
		case <- user.err :
			client.conn.Close()
			user.conn.Close()
			runtime.Goexit()
		case <- client.err :
			user.conn.Close()
			client.conn.Close()
			runtime.Goexit()
		}
	}
}



