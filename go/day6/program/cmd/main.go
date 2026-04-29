package main

import (
	"embed"
	"fmt"
	"program/internal"
)

//go:generate echo "Работает"
//go:generate date

//go:embed folder/file1.txt
var fileByte string

//go:embed folder/*.txt
var folder embed.FS

func main() {
	fmt.Println("Лабораторная работа: Сборка проекта в дистрибутив\n")

	// Демонстрация go:embed
	fmt.Println("--- Демонстрация //go:embed ---")
	fmt.Printf("Содержимое file1.txt: %s\n", fileByte)

	file2Content, _ := folder.ReadFile("folder/file2.txt")
	fmt.Printf("Содержимое file2.txt: %s\n\n", string(file2Content))

	// Основная программа сортировки
	fmt.Println("--- Программа сортировки массива ---")
	fmt.Println("Введите длину массива:")
	var n int
	fmt.Scan(&n)

	arr := make([]int, n)
	fmt.Println("Введите элементы через пробел:")
	for i := 0; i < n; i++ {
		fmt.Scan(&arr[i])
	}

	fmt.Println("Исходный массив:", arr)

	// Сортировка (поведение зависит от build tags)
	sortedArr := internal.BubbleSort(arr)

	fmt.Println("Отсортированный массив:", sortedArr)

	fmt.Println("\nВведите номер элемента для поиска (k):")
	var k int
	fmt.Scan(&k)

	if k > 0 && k <= len(sortedArr) {
		fmt.Printf("%d-й элемент в отсортированном массиве: %d\n", k, sortedArr[k-1])
	} else {
		fmt.Println("Ошибка: некорректный номер элемента")
	}
}
