package utils_test

import (
	"task5_example/utils"
	"testing"
)

func equalSlices(a, b []int) bool {
	if len(a) != len(b) {
		return false
	}
	for i := 0; i < len(a); i++ {
		if a[i] != b[i] {
			return false
		}
	}
	return true
}

func TestFilterAndSort(t *testing.T) {
	tests := []struct {
		name      string
		nums      []int
		min       int
		expected  []int
		shouldErr bool
	}{
		{
			name:      "нормальная работа",
			nums:      []int{5, 2, 8, 1, 9},
			min:       3,
			expected:  []int{5, 8, 9},
			shouldErr: false,
		},
		{
			name:      "с отрицательными числами",
			nums:      []int{-5, -1, 0, 1, 5},
			min:       0,
			expected:  []int{0, 1, 5},
			shouldErr: false,
		},
		{
			name:      "с дубликатами",
			nums:      []int{3, 1, 4, 1, 5, 9, 2},
			min:       3,
			expected:  []int{3, 4, 5, 9},
			shouldErr: false,
		},
		{
			name:      "ошибка: nil слайс",
			nums:      nil,
			min:       0,
			expected:  nil,
			shouldErr: true,
		},
		{
			name:      "ошибка: пустой слайс",
			nums:      []int{},
			min:       0,
			expected:  nil,
			shouldErr: true,
		},
		{
			name:      "ошибка: все числа меньше min",
			nums:      []int{1, 2, 3},
			min:       10,
			expected:  nil,
			shouldErr: true,
		},
	}

	for _, tt := range tests {
		t.Run(tt.name, func(t *testing.T) {
			got, err := utils.FilterAndSort(tt.nums, tt.min)

			if tt.shouldErr {
				if err == nil {
					t.Errorf("ожидалась ошибка, но получили nil")
				}
				return
			}

			if err != nil {
				t.Errorf("не ожидалась ошибка, получили: %v", err)
				return
			}

			if !equalSlices(got, tt.expected) {
				t.Errorf("получили %v, ожидалось %v", got, tt.expected)
			}
		})
	}
}
