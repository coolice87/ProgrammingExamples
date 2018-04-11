package main

import (
	"time"
	"fmt"
)

func main() {
	requests := make(chan int, 5)
	for i:=1; i<=5; i++ {
		requests <- i
	}
	close(requests)

	limiter := time.Tick(time.Millisecond * 200)

	for req := range requests {
		<-limiter
		fmt.Println("request ", req, time.Now())
	}

	busyLimiter := make(chan time.Time, 3)
	for i:=0; i<3; i++ {
		busyLimiter <- time.Now()
	}

	go func() {
		for t := range time.Tick(time.Millisecond * 200) {
			busyLimiter <- t
		}
	}()

	busyRequests := make(chan int, 5)
	for i:=1; i<=5; i++ {
		busyRequests <- i
	}
	close(busyRequests)

	for req := range busyRequests {
		<- busyLimiter
		fmt.Println("request", req, time.Now())
	}
}

