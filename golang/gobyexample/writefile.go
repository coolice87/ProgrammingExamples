package main

import (
	"fmt"
	"bufio"
	"io/ioutil"
	"os"
)

var pf = fmt.Printf

func check(e error) {
	if e != nil {
		panic(e)
	}
}

func main() {
	d1 := []byte("hello\ngo\n")
	err := ioutil.WriteFile("/tmp/wdat1", d1, 0644)
	check(err)

	f,err := os.Create("/tmp/wdat2")
	check(err)
	defer f.Close()

	d2 := []byte{115, 111, 109, 101, 10}
	n2,err := f.Write(d2)
	check(err)
	pf("wrote %d bytes\n", n2)

	n3,err := f.WriteString("writes\n")
	pf("wrote %d bytes\n", n3)
	f.Sync()

	w := bufio.NewWriter(f)
	n4,err := w.WriteString("buffered\n")
	pf("wrote %d bytes\n", n4)

	w.Flush()
}


