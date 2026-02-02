package main

import (
	"fmt"
	"slices"
)

func DecimlToBinary(n int) []int {
	var bits []int
	if n == 0 {
		bits = append(bits, 0)
	}
	for n > 0 {
		bits = append(bits, n%2)
		n = n / 2
	}

	slices.Reverse(bits)
	return bits
}
func printRow(row []int) {
	for _, val := range row {
		if val == 1 {
			// Зеленый фон (ANSI 42) + пробел + сброс
			fmt.Print("\033[42m \033[0m")
		} else {
			// Серый фон (ANSI 100) + пробел + сброс
			fmt.Print("\033[100m \033[0m")
		}
	}
	fmt.Println()
}

func nextGeneration(current []int) []int {
	n := len(current)
	next := make([]int, n)
	for i := 0; i < n; i++ {
		left := 0
		right := 0
		if i > 0 {
			left = current[i-1]
		}
		if i < n-1 {
			right = current[i+1]
		}
		next[i] = left ^ right
	}
	return next
}

func main() {
	startBits := DecimlToBinary(1)
	row := make([]int, 64)
	index := (len(row) - len(startBits)) / 2
	copy(row[index:], startBits)

	for i := 0; i < 32; i++ {
		printRow(row)
		row = nextGeneration(row)
	}
}
