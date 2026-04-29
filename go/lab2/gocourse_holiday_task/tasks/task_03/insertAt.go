package task03

import (
	"errors"
)

func InsertAt(nums []int, index int, value int) ([]int, error) {
	if index < 0 || index > len((nums)) {
		return nil, errors.New("invalid index")
	}
	var app []int
	for i, number := range nums {
		if i == index {
			app = append(app, value)
		}
		app = append(app, number)
	}
	if index == len(nums) {
		app = append(app, value)
	}
	return app, nil
}
