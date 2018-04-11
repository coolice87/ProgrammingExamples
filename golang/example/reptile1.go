package main

import (
	"fmt"
	"log"
	"net/http"
	"os"
)

func main() {
	resp,err := http.Get("https://www.baidu.com")
	if err != nil {
		fmt.Println(err)
		log.Fatal(err)
	}
	defer resp.Body.Close()

	if resp.StatusCode == http.StatusOK {
		fmt.Println(resp.StatusCode)
	}

	buf := make([]byte, 1024)
	//createfile
	f,err := os.OpenFile("baidu.html", os.O_RDWR|os.O_CREATE|os.O_APPEND, os.ModePerm)
	if err != nil {
		panic(err)
		return
	}
	defer f.Close()

	for {
		n,_ := resp.Body.Read(buf)
		if 0 == n {
			break
		}
		f.WriteString(string(buf[:n]))
	}
	
}

