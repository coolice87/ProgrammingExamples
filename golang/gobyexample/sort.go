package main

import (
	"fmt"
	"sort"
)

func main() {
	str := []string{"c", "a", "bt"}
	sort.Strings(str)
	fmt.Println("strings:", str)

	ints := []int{5, 4, 3}
	sort.Ints(ints)
	fmt.Println("ints:", ints)

	s := sort.IntsAreSorted(ints)
	fmt.Println("Sorted: ", s)
}

