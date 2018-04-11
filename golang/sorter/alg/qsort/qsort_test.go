package qsort

import "testing"

func TestQuickSort1(t *testing.T){
	values := []int{5, 4, 3, 2, 1}
	QuickSort(values)

	if values[0] != 1 || values[1] != 2 {
		t.Error("QuickSort() fail ", values, "Expected 1 2 3 4 5")
	}
}


