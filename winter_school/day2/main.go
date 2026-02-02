package main

import (
	"day2/CPU"
	"day2/Creatures"
	"day2/World"
	"fmt"
	"path/filepath"
)

func main() {
	basePath := "/Users/artemlesin/lab8.c/Laba9/winter_school/day2/maze/"

	for level := 1; level <= 7; level++ {
		mazeFile := filepath.Join(basePath, fmt.Sprintf("maze%d.txt", level))

		maze, start, end, err := World.LoadMaze(mazeFile)
		if err != nil {
			fmt.Printf("Ошибка загрузки лабиринта %d: %v\n", level, err)
			return
		}

		fmt.Printf("\n=== ЛАБИРИНТ %d ===\n", level)
		fmt.Printf("Старт: X=%d, Y=%d | Финиш: X=%d, Y=%d\n",
			start.X, start.Y, end.X, end.Y)

		CPU.ReplaceMazeWithEmoji(maze)

		// Запускаем игру для текущего лабиринта
		completed, err := Creatures.Setup(maze, start.X, start.Y, end.X, end.Y)

		if err != nil {
			fmt.Printf("Ошибка в игре: %v\n", err)
			return
		}

		if !completed {
			fmt.Printf("Игра завершена. Пройдено лабиринтов: %d\n", level-1)
			return
		}
	}

	fmt.Println("🎉 Все 7 лабиринтов успешно пройдены! Поздравляем! 🎉")
}
