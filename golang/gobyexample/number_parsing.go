package main

import "fmt"
import "strconv"

func main() {
	f,_ := strconv.ParseFloat("1.34", 32)
	fmt.Println(f)

	i,_ := strconv.ParseInt("123", 0, 32)
	fmt.Println(i)
	i1,_ := strconv.ParseInt("123", 16, 32)
	fmt.Println(i1)

	d,_ := strconv.ParseInt("0x1c8", 0, 32)
	fmt.Println(d)

	u,_ := strconv.ParseUint("789", 0, 32)
	fmt.Println(u)

	k,_ := strconv.Atoi("135")
	fmt.Println(k)

	_,e := strconv.Atoi("wat")
	fmt.Println(e)

}

