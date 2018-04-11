package main

import (
	"flag"
	"fmt"
	"net"
	"os"
	"runtime"
	"strconv"
	"strings"
	"time"
)

var pl = fmt.Println
var pf = fmt.Printf

var host *string = flag.String("host", "127.0.0.1", "请输入服务器IP")
var remotePort *string = flag.String("remotePort", "20012", "服务器端口")
var localPort *string = flag.String("localPort", "8899", "本地端口")

//browser conn
type browser struct {
	conn net.Conn
	err chan bool
	writ chan bool
	recv chan []byte
	send chan []byte
}

//read browser data
func (self browser) read() {
	for {
		var recv []byte = make([]byte, 10240)
		n,err := self.conn.Read(recv)
		if err != nil {
			self.err <- true
			self.writ <- true
			break
		}

		self.recv <- recv[:n]
	}
}

//write data to browser
func (self browser) write() {
	for {
		var send []byte = make([]byte, 10240)
		select {
		case send = <- self.send:
			self.conn.Write(send)
		case <- self.writ :
			pl("browser write close")
			break	
		}
	}
}

//server conn
type server struct {
	conn net.Conn
	err chan bool
	writ chan bool
	recv chan []byte
	send chan []byte
}

//read server data
func (self *server) read() {
	var isheart bool = false
	self.conn.SetReadDeadline(time.Now().Add(time.Second * 20))
	for {
		var recv []byte = make([]byte, 10240)
		n,err := self.conn.Read(recv)
		if err != nil {
			if strings.Contains(err.Error(), "timeout") && !isheart {
				pl("send heart package")
				self.conn.Write([]byte("hh"))
				self.conn.SetReadDeadline(time.Now().Add(time.Second * 4))
				isheart = true
				continue
			}

			//only keep connect
			self.recv <- []byte("0")
			self.err <- true
			self.writ <- true
			pl("Maybe server have been closed")
			break
		}

		if recv[0] == 'h' && recv[1] == 'h' {
			pl("Have a heart package")
			self.conn.SetReadDeadline(time.Now().Add(time.Second * 20))
			isheart = false
			break
		}
		self.recv <- recv[:n]
	}
}

//write data to server
func (self *server) write() {
	for {
		var send []byte = make([]byte, 10240)

		select {
		case send = <- self.send :
			self.conn.Write(send)
		case <- self.writ:
			pl("server have been closed")
			break
		}
	}
}


func main() {
	runtime.GOMAXPROCS(runtime.NumCPU())
	flag.Parse()

	if flag.NFlag() != 3 {
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

	target := net.JoinHostPort(*host, *remotePort)
	pl(target)
	for {
		serverconn := dail(target)
		recv := make(chan []byte)
		send := make(chan []byte)
		err := make(chan bool, 1)
		writ := make(chan bool)
		next := make(chan bool)
		server := &server{serverconn, err, writ, recv, send}
		go server.read()
		go server.write()
		go handle(server, next)
		<-next
	}
}

func log (err error) {
	if err != nil {
		pf("error :%v\n", err)
	}
}

func logExit(err error) {
	if err != nil {
		pf("thread exit: %v\n", err)
		runtime.Goexit()
	}
}

func dail(hostport string) net.Conn {
	conn,err := net.Dial("tcp", hostport)
	logExit(err)
	return conn
}

func handle(server *server, next chan bool) {
	var serverrecv = make([]byte, 10240)
	pl("wait server msg")
	serverrecv = <-server.recv
	next <- true
	pl("开始新TCP连接, 消息: ", string(serverrecv))
	var browse *browser
	serverconn := dail("127.0.0.1:" + *localPort)
	recv := make(chan []byte)
	send := make(chan []byte)
	err := make(chan bool, 1)
	writ := make(chan bool)
	browse = &browser{serverconn, err, writ, recv, send}
	go browse.read()
	go browse.write()
	browse.send <- serverrecv

	for {
		var serverrecv = make([]byte, 10240)
		var browerecv = make([]byte, 10240)

		select {
			case serverrecv = <- server.recv :
				if serverrecv[0] != '0' {
					browse.send <-serverrecv
				}
			case browerecv = <- browse.recv :
				server.send <- browerecv
			case <-server.err:
				server.conn.Close()
				browse.conn.Close()
				runtime.Goexit()
			case <-browse.err:
				server.conn.Close()
				browse.conn.Close()
				runtime.Goexit()
		}
	}
}



