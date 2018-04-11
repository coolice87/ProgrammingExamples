package main

import (
	"fmt"
	"io/ioutil"
	"net/http"
	"os"
)

var p = fmt.Println

func main() {
	response,err := http.Get("https://www.baidu.com/")
	if err != nil {
		p(err)
		os.Exit(1)
	}else{
		defer response.Body.Close()

		body,err := ioutil.ReadAll(response.Body)
		if err != nil {
			p(err)
			os.Exit(1)
		}
		p(string(body))
	
	}
}

