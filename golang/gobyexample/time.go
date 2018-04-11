package main

import "fmt"
import "time"

var p = fmt.Println

func main() {
	now := time.Now()
	p(now)	

	p(now.Year())
	p(now.Month())
	p(now.Day())
	p(now.Hour())
	p(now.Minute())
	p(now.Second())
	p(now.Weekday())
	
	then := time.Date(2012, 11, 17, 20, 34, 58, 0, time.UTC)
	p(then)
	diff := now.Sub(then)
	p(diff)
}

