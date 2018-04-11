package main

import "fmt"

const rate float64 = 0.2

func fact(year int) float64 {
	if year <=0 {
		return 1
	}

	return (1+rate) * fact(year - 1)
}


func main(){
	fmt.Println(fact(10))
}

