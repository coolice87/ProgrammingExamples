package main


import "os"
import "fmt"

func main() {
	allArg := os.Args
	param := os.Args[1:]

	prog := os.Args[0]
	param1 := os.Args[3]

	fmt.Println(allArg)
	fmt.Println(param)
	fmt.Println(prog)
	fmt.Println(param1)

}

