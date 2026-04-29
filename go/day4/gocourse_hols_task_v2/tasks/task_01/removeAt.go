package task01

import (
	"errors"
)

func RemoveAt(nums []int, index int) ([]int, error) {
	var result []int
	if index < 0 || index >= len(nums) {
		return nil, errors.New("index out of bounds") //заглушка
	}
	for i, numb := range nums {
		if i == index {
			continue
		}
		result = append(result, numb)
	}
	return result, nil
}
