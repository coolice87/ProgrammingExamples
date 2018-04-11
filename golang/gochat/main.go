package main

import (
	"flag"
	"html/template"
	"log"
	"net/http"
	"os"
	"bytes"
	"path/filepath"
	"fmt"
	"strings"

	"gochat/ws"
)

var pl = fmt.Println
var pf = fmt.Printf

var (
	addr = flag.String("addr", "192.168.2.200:8899", "http service address")
	redisServer = flag.String("redisServer", "127.0.0.1:6379", "redis addr")
	redisPasswd = flag.String("redisPassword", "", "redis password")
)

func getTemplatePath() *bytes.Buffer {
	root_path,_ := os.Getwd()
	path := bytes.Buffer{}
	path.WriteString(root_path)
	local_path := filepath.FromSlash("/templates/")
	path.WriteString(local_path)
	
	return &path
}

func serveHome(w http.ResponseWriter, r *http.Request) {
	log.Println(r.URL)

	if r.URL.Path != "/" {
		http.Error(w, "Not found", 404)
		return
	}

	if r.Method != "GET" {
		http.Error(w, "Method not allowed", 405)
		return
	}

	w.Header().Set("Content-Type", "text/html; charset=utf-8")
	templatefile := getTemplatePath()
	templatefile.WriteString("home.html")
	homeTemplate:=template.Must(template.ParseFiles(templatefile.String()))
	homeTemplate.Execute(w, r.Host)
}

func room(w http.ResponseWriter, r *http.Request) {
	log.Println(r.URL)

	if r.URL.Path != "/room" {
		http.Error(w, "Not found", 404)
		return 
	}

	w.Header().Set("Content-Type", "text/html; charset=utf-8")
	switch r.Method {
		case "GET" : {
			templatefile := getTemplatePath()
			templatefile.WriteString("room.html")
			client := ws.NewClient(*redisServer, *redisPasswd)
			client.Run("SET", "room", "dsd,d")
			rest := client.Run("GET", "room")
			pf("%s", rest)	
			strings.Split(rest.(string), ",")
			homeTemplate := template.Must(template.ParseFiles(templatefile.String()))
			homeTemplate.Execute(w, "")
			defer client.Close()
		}
		case "POST": {
		
		}
	}
}

func main() {
	flag.Parse()

	hub := ws.NewHub()
	go hub.Run()

	fs := http.FileServer(http.Dir("static/"))
	http.Handle("/static/", http.StripPrefix("/static/", fs))
	http.HandleFunc("/", serveHome)
	http.HandleFunc("/room", room)
	http.HandleFunc("/ws", func(w http.ResponseWriter, r *http.Request){
		ws.ServeWs(hub, w, r)
		})
	pf(" server on %s", *addr)
	err := http.ListenAndServe(*addr, nil)
	if err != nil {
		log.Fatal("ListenAndServe:", err)
	}
}


