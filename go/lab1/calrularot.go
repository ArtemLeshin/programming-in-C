package main

import (
	"fmt"
)

func summ(a, b float64) float64 {
	return a + b
}
func min(a, b float64) float64 {
	return a - b
}
func prog(a, b float64) float64 {
	return a * b
}
func dell(a, b float64) float64 {
	if b == 0 {
		panic("Деление на ноль!")
	}
	return a / b
}

func consolprint() (float64, float64, string) {
	var op string
	var a, b float64

	fmt.Print("Введите операцию (+, -, *, /): ")
	fmt.Scanln(&op)

	fmt.Print("Введите первое число: ")
	fmt.Scanln(&a)

	fmt.Print("Введите второе число: ")
	fmt.Scanln(&b)

	return a, b, op
}

func main() {
	a, b, op := consolprint()
	var result float64
	switch op {
	case "+":
		result = summ(a, b)
	case "-":
		result = min(a, b)
	case "*":
		result = prog(a, b)
	case "/":
		result = dell(a, b)
	default:
		fmt.Println("Неизвестная операция")
	}
	fmt.Println("Результат:\n", result)
}
