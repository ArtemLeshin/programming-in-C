package task02

func FilterEven(nums []int) []int {
	var chet []int
	for _, num := range nums {
		if num%2 == 0 {
			chet = append(chet, num)
		}
	}
	return chet //заглушка
}
