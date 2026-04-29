//go:build debug

package internal

import "fmt"

// BubbleSort сортировка по УБЫВАНИЮ с отладочным выводом (debug версия)
func BubbleSort(arr []int) []int {
	fmt.Println("[DEBUG] Начало сортировки массива:", arr)

	result := make([]int, len(arr))
	copy(result, arr)

	// Пузырьковая сортировка по убыванию
	for i := 0; i < len(result)-1; i++ {
		for j := 0; j < len(result)-i-1; j++ {
			if result[j] < result[j+1] {
				result[j], result[j+1] = result[j+1], result[j]
				fmt.Printf("[DEBUG] Шаг %d-%d: %v\n", i, j, result)
			}
		}
	}

	fmt.Println("[DEBUG] Сортировка завершена. Результат:", result)
	return result
}
