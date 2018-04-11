package main

import (
	"bufio"
	"fmt"
	"log"
	"net"
)

func main() {
	listener,err := net.Listen("tcp", "localhost:8899")
	if err != nil {
		log.Fatal(err)
	}

	go broadcaster()

	for {
		conn,err := listener.Accept()
		if err != nil {
			log.Print(err)
			continue
		}

		go handleConn(conn)
	}
}

type client chan<- string

var (
	entering = make(chan client)
	leaving = make(chan client)
	messages = make(chan string)
)

func broadcaster() {
	clients := make(map[client]bool)
	for {
		select {
		case msg := <- messages:
			for cli := range clients {
				cli <- msg
			}
		case cli := <- entering:
			clients[cli] = true
		case cli := <- leaving :
			delete(clients, cli)
			close(cli)
		}
	}
}

func handleConn(conn net.Conn) {
	ch := make(chan string)
	go clientWriter(conn, ch)
	who := conn.RemoteAddr().String()
	ch <- "你是" + who
	messages <- who + "加入聊天"
	entering <- ch

	input := bufio.NewScanner(conn)
	for input.Scan() {
		messages <- who + ":" + input.Text()
	}
	leaving <- ch
	messages <- who + "已经离开"
	conn.Close()
}

func clientWriter(conn net.Conn, ch <-chan string) {
	for msg := range ch {
		fmt.Fprintln(conn, msg)
	}
}

