package main

import "fmt"
import "syscall"
import "os"
import "os/exec"

func main() {
	binary,err := exec.LookPath("ls")
	if err != nil {
		panic(err)
	}

	args := []string{"ls", "-alh"}

	env := os.Environ()

	fmt.Println(binary, "\n", args, "\n", env)

	err = syscall.Exec(binary, args, env)
	if err != nil {
		panic(err)
	}
}

