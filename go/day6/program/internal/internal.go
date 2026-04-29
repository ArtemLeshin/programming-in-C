//go:build !debug

package internal

// BubbleSort сортировка по ВОЗРАСТАНИЮ (стандартная версия без debug)
func BubbleSort(arr []int) []int {
	result := make([]int, len(arr))
	copy(result, arr)

	// Пузырьковая сортировка по возрастанию
	for i := 0; i < len(result)-1; i++ {
		for j := 0; j < len(result)-i-1; j++ {
			if result[j] > result[j+1] {
				result[j], result[j+1] = result[j+1], result[j]
			}
		}
	}
	return result
}
