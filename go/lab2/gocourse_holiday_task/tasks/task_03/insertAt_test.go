package task03_test

import (
	"gocourse_htask/tasks/task_03"
	"testing"
	"slices"
)

func TestInsertAt(t *testing.T) {
	result, result_err := task03.InsertAt([]int{1, 2, 3, 4}, 2, 15)
	expected := []int{1, 2, 15, 3, 4}
	var expected_err error = nil

	if !slices.Equal(result, expected) {
		t.Errorf("got: %v, want: %v\n", result, expected)
	}

	if result_err != expected_err {
		t.Errorf("unexpected error: %v\n", result_err)
	}

	_, fail_err := task03.InsertAt([]int{1, 2, 3, 4}, 1000, 15)
	if fail_err == nil {
		t.Errorf("invalid index check: %v\n", fail_err)
	}

	_, fail_err2 := task03.InsertAt([]int{1, 2, 3, 4}, -1, 15)
	if fail_err2 == nil {
		t.Errorf("negative index check: %v\n", fail_err2)
	}
}