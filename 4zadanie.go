package main

import (
	"fmt"
	"math"
)

func main() {
	var n, m int
	fmt.Scan(&n, &m)

	a := make([]int64, n)

	for i := 0; i < n; i++ {
		fmt.Scan(&a[i])
	}

	prefix := make([]int64, n+1)

	for i := 0; i < n; i++ {
		prefix[i+1] = prefix[i] + a[i]
	}

	scorePlayers := [2]int64{0, 0}
	prevTake := [2]int{0, 0}

	player := 0 // 0 — Павел, 1 — Вика
	pos := 0

	for pos < n {
		nOstaloc := n - pos
		limit := min(m, nOstaloc)

		bestSum := int64(math.MinInt64)
		bestTake := -1

		for take := 1; take <= limit; take++ {
			if take == prevTake[player] {
				continue
			}

			s := prefix[pos+take] - prefix[pos]

			if s > bestSum || (s == bestSum && take < bestTake) {
				bestSum = s
				bestTake = take
			}
		}

		if bestTake == -1 {
			bestTake = 1
		}

		scorePlayers[player] += prefix[pos+bestTake] - prefix[pos]
		prevTake[player] = bestTake
		pos += bestTake
		player = 1 - player
	}

	if scorePlayers[0] > scorePlayers[1] {
		fmt.Println(1)
	} else {
		fmt.Println(0)
	}
}