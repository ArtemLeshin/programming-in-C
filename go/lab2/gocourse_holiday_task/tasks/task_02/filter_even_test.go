package task02_test

import (
	"gocourse_htask/tasks/task_02"
	"testing"
	"slices"
)

func TestFilterEven(t *testing.T) {
	result := task02.FilterEven([]int{1, 2, 3, 4, 5, 6, 7, 8})
	expected := []int{2, 4, 6, 8}

	if !slices.Equal(result, expected) {
		t.Errorf("got: %v, want: %v\n", result, expected)
	}

	result2 := task02.FilterEven([]int{1, 3, 5, 7})
	if len(result2) != 0 {
		t.Errorf("expected empty slice for no even numbers, got: %v", result2)
	}

	result3 := task02.FilterEven([]int{2, 4, 6, 8})
	expected3 := []int{2, 4, 6, 8}
	if !slices.Equal(result3, expected3) {
		t.Errorf("got: %v, want: %v\n", result3, expected3)
	}
}