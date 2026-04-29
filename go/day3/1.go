package main

import (
	"fmt"
)

func BubbleSort(arr []int, n int) []int {
	result := make([]int, n)
	copy(result, arr)
	for i := 0; i < n-1; i++ {
		for j := 0; j < n-i-1; j++ {
			if result[j] < result[j+1] {
				result[j], result[j+1] = result[j+1], result[j]
			}
		}
	}
	return result
}

func main() {
	fmt.Println("Введите длину массива:")
	var n int
	fmt.Scan(&n)
	arr := make([]int, n)
	fmt.Println("введите через пробел")
	for i := 0; i < n; i++ {
		fmt.Scan(&arr[i])
	}
	fmt.Println("Исходный список:", arr)
	sortedArr := BubbleSort(arr, n)
	fmt.Println("Отсортированный список:", sortedArr)
	fmt.Println("Введите k")
	var k int
	fmt.Scan(&k)
	fmt.Printf("%d\n", sortedArr[k-1])
}
