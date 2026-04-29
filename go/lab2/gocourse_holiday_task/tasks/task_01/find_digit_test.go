	package task01_test

	import (
		"gocourse_htask/tasks/task_01"
		"testing"
		"errors"
	)

	func TestFind(t *testing.T) {
		result, result_err := task01.Find([]int{1, 2, 3, 4}, 4)
		expected := 3
		var expected_err error = nil

		if result != expected {
			t.Errorf("got: %d, want: %d\n", result, expected)
		}

		if !errors.Is(result_err, expected_err) {
    	t.Errorf("unexpected error: %v\n", result_err)
		}

		result2, err2 := task01.Find([]int{1, 2, 3, 4}, 10)
		if err2 == nil {
			t.Errorf("expected error for missing element, got nil")
		}

		if result2 != -1 {
			t.Errorf("expected index -1 for missing element, got %d", result2)
		}
	}