package main

import (
	"fmt"
	"math/rand"
	"time"
)

func seed(grid [][]bool) {
	for i := range grid {
		for j := range grid[i] {
			grid[i][j] = rand.Float64() < 0.25
		}
	}
}
func countNeighbors(grid [][]bool, row, col int) int {
	count := 0
	h, w := len(grid), len(grid[0])
	for i := -1; i <= 1; i++ {
		for j := -1; j <= 1; j++ {
			if i == 0 && j == 0 {
				continue
			}
			r := (row + i + h) % h
			c := (col + j + w) % w
			if grid[r][c] {
				count++
			}
		}
	}
	return count
}

func nextGen(current [][]bool) [][]bool {
	h, w := len(current), len(current[0])
	next := make([][]bool, h)
	for i := range next {
		next[i] = make([]bool, w)
	}
	for i := 0; i < h; i++ {
		for j := 0; j < w; j++ {
			neign := countNeighbors(current, i, j)
			alive := current[i][j]
			if alive && (neign == 2 || neign == 3) {
				next[i][j] = true
			} else if !alive && neign == 3 {
				next[i][j] = true
			}
		}
	}

	return next
}

func main() {
	h := 30
	w := 60
	grid := make([][]bool, h)
	for i := range grid {
		grid[i] = make([]bool, w)
	}
	seed(grid)
	for {

		// Очистка экрана для отрисовки следующего кадра
		fmt.Print("\033[H\033[2J")
		for i := range grid {
			for j := range grid[i] {
				if grid[i][j] {
					fmt.Print("█")
				} else {
					fmt.Print(".")
				}
			}
			fmt.Println("")
		}

		// Рандом
		fmt.Printf("Random int [0, 99]: %d\n", rand.Intn(100))

		// Ваша реализация
		grid = nextGen(grid)

		// Сон между кадрами
		time.Sleep(100 * time.Millisecond)
	}
}
