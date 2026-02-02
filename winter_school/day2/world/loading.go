package World

import (
	"os"
	"strings"
)

type Point struct{ X, Y int }

func LoadMaze(filename string) ([][]rune, Point, Point, error) {
	var maze [][]rune
	var start, end Point
	startFound, endFound := false, false

	data, err := os.ReadFile(filename)
	if err != nil {
		return nil, Point{}, Point{}, err
	}

	lines := strings.Split(string(data), "\n")
	for _, line := range lines {
		line = strings.TrimSpace(line)
		if len(line) == 0 {
			continue
		}
		maze = append(maze, []rune(line))
	}

	// Ищем S и E в лабиринте
	for y, row := range maze {
		for x, cell := range row {
			if cell == 'S' {
				start = Point{X: x, Y: y} // X - столбец, Y - строка
				startFound = true
			}
			if cell == 'E' {
				end = Point{X: x, Y: y} // X - столбец, Y - строка
				endFound = true
			}
		}
	}

	if !startFound {
		return maze, Point{}, Point{}, nil
	}
	if !endFound {
		return maze, start, Point{}, nil
	}

	return maze, start, end, nil
}
