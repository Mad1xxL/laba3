package main

import (
	"fmt"
	"math"
)

func gcd(a, b int64) int64 {
	for b != 0 {
		r := a % b
		a = b
		b = r
	}
	return a
}

func main() {
	var a, b int

	fmt.Scan(&a, &b)

	if b == 1 {
		fmt.Println("infinity")
		return
	}

	sum := 0.0
	term := 1.0 / float64(b)

	for n := 1; n <= 1000000 && term > 1e-15; n++ {

		if n > 1 {
			term *= math.Pow(float64(n)/float64(n-1), float64(a)) / float64(b)
		}

		sum += term
	}

	var num int64 = 0
	var den int64 = 1

	for d := int64(1); d <= 1000000; d++ {

		n := int64(math.Round(sum * float64(d)))

		if math.Abs(sum-float64(n)/float64(d)) < 1e-12 {
			num = n
			den = d
			break
		}
	}

	g := gcd(int64(math.Abs(float64(num))), den)

	num /= g
	den /= g

	fmt.Printf("%d/%d\n", num, den)
}