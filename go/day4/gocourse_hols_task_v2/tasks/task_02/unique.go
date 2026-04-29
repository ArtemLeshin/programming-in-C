package task02

func Unique(nums []int) []int {

	result := make([]int, 0)

	if len(nums) == 0 {
		return result
	}

	seen := make(map[int]bool)
	for _, numb := range nums {
		if !seen[numb] {
			seen[numb] = true
			result = append(result, numb)
		}
	}

	return result
}
