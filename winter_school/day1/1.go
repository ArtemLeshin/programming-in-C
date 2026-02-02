package main

import (
	"fmt" // пакет для ввода/вывода
	"os"
	"strconv"
)

func main() {
	fmt.Println("Hello, Go!")
	N := os.Args
	if len(N) < 2 {
		fmt.Println("Пожалуйста введиет число")
		return
	}
	Num, err := strconv.Atoi(os.Args[1])
	if err != nil {
		fmt.Println("Ошибка")
		return
	}
	a := make([]int, Num)
	newElem := 0
	for i := range a {
		a[i] = i * i
		newElem = newElem + i*i
	}

	a = append(a, newElem)

	var filtered []int

	for i := range a {
		if a[i]%3 == 0 {
			filtered = append(filtered, a[i])
		}
	}

	fmt.Println(a)
	fmt.Println(filtered)
	ans := 100.0 - (float64(len(filtered)) / float64(len(a)) * 100.0)
	fmt.Println(ans, "%")

}
