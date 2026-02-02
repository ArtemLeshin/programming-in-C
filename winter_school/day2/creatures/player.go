package Creatures

import (
	"day2/CPU"
	"fmt"
	"os"
	"os/exec"
)

type Position struct {
	X int
	Y int
}

// Moving проверяет возможность перемещения в новую позицию
func Moving(pos Position, dx, dy int, maze [][]rune) (Position, bool) {
	newX := pos.X + dx
	newY := pos.Y + dy

	// Проверяем границы: Y - строка, X - столбец
	if newY >= 0 && newY < len(maze) && newX >= 0 && newX < len(maze[0]) && maze[newY][newX] != '🧱' {
		return Position{X: newX, Y: newY}, true
	}
	return pos, false
}

// Rendering отрисовывает лабиринт и игрока
func Rendering(maze [][]rune, pos Position) {
	fmt.Print("\033[H\033[2J") // Очистка экрана
	for i, row := range maze {
		for j, cell := range row {
			if i == pos.Y && j == pos.X { // Y - строка, X - столбец
				fmt.Print("😎")
			} else {
				fmt.Print(string(cell))
			}
		}
		fmt.Println()
	}
	fmt.Println("История ходов:", len(history), "Время:", CPU.GetTime())
	fmt.Println("Управление: W/A/S/D - движение, T - отмена хода, Q - выход")
}

var history []Position

const maxHistory = 10

// saveMove сохраняет ход в историю
func saveMove(pos Position) {
	if len(history) >= maxHistory {
		history = history[1:]
	}
	history = append(history, pos)
}

// rewindTime отменяет последний ход
func rewindTime() (Position, bool) {
	if len(history) <= 1 { // Оставляем хотя бы одну позицию (стартовую)
		return Position{}, false
	}
	lastIndex := len(history) - 2 // Берем предпоследнюю позицию
	if lastIndex < 0 {
		return Position{}, false
	}
	lastPos := history[lastIndex]
	history = history[:lastIndex+1]
	return lastPos, true
}

// Setup запускает игровой цикл для одного лабиринта
// Возвращает true, если лабиринт пройден успешно, false если игрок вышел (Q)
func Setup(maze [][]rune, startX, startY, endX, endY int) (bool, error) {
	// Настройка терминала для чтения клавиш без Enter
	sttyConfig := exec.Command("stty", "-f", "/dev/tty", "cbreak", "min", "1", "-echo")
	sttyConfig.Run()
	defer exec.Command("stty", "-f", "/dev/tty", "sane").Run()

	CPU.StartTimer()
	history = make([]Position, 0, maxHistory)

	posPlayer := Position{X: startX, Y: startY}
	saveMove(posPlayer)
	Rendering(maze, posPlayer)

	var b = make([]byte, 1)
	for {
		os.Stdin.Read(b)
		if b[0] == 'q' || b[0] == 'Q' {
			// Игрок вышел
			return false, nil
		}

		var dx, dy int
		moved := false
		key := b[0]

		switch key {
		case 'w', 'W':
			dx, dy = 0, -1
			moved = true
		case 's', 'S':
			dx, dy = 0, 1
			moved = true
		case 'd', 'D':
			dx, dy = 1, 0
			moved = true
		case 'a', 'A':
			dx, dy = -1, 0
			moved = true
		case 't', 'T':
			if prevPos, ok := rewindTime(); ok {
				posPlayer = prevPos
				Rendering(maze, posPlayer)
			}
			continue
		}

		if moved {
			newPos, canMove := Moving(posPlayer, dx, dy, maze)
			if canMove {
				saveMove(posPlayer)
				posPlayer = newPos

				// Проверка победы - сравниваем координаты
				if posPlayer.X == endX && posPlayer.Y == endY {
					elapsed := CPU.GetTime()
					fmt.Printf("\n🎉 ПОЗДРАВЛЯЕМ! Лабиринт пройден за: %v\n", elapsed)
					fmt.Println("Нажмите любую клавишу для продолжения...")
					os.Stdin.Read(b)
					return true, nil // Лабиринт пройден успешно
				}
				Rendering(maze, posPlayer)
			}
		}
	}
}
