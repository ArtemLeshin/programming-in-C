package CPU

import (
	"fmt"
	"time"
)

var startTime time.Time

func StartTimer() {
	startTime = time.Now()
}

func GetTime() string {
	elapsed := time.Since(startTime)
	return fmt.Sprintf("%.1fs", elapsed.Seconds())
}
func ReplaceMazeWithEmoji(maze [][]rune) {
	for i := range maze {
		for j := range maze[i] {
			switch maze[i][j] {
			case '#':
				maze[i][j] = '🧱'
			case ' ':
				maze[i][j] = '　'
			case 'S':
				maze[i][j] = '🚪'
			case 'E':
				maze[i][j] = '🏁'
			case 'P':
				maze[i][j] = '😎'
			}
		}
	}
}
