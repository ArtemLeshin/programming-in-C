package task01

import "errors"

func Find(nums []int, target int) (int, error) {
	for ind, numb := range nums {
		if numb == target {
			return ind, nil
		}
	}
	return -1, errors.New("non implemented")
}
