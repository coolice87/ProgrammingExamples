package main

import "os"

func main() {
//	panic("a problem")
	_, err := os.Create("/home/xu_longfei/file")
	if err != nil {
		panic(err)
	}
}

