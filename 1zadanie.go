package main

import (
	"fmt"
	"math"
)

// Кусочно-заданная функция
func f(x float64) float64 {

	// 1. Левая полуокружность
	if x >= -6.0 && x <= -4.0 {
		return -math.Sqrt(4.0 - (x+4.0)*(x+4.0))
	}

	// 2. y = cbrt(2x)
	if x > -4.0 && x <= 4.0 {
		return math.Cbrt(2.0 * x)
	}

	// 3. Правая полуокружность
	if x > 4.0 && x <= 6.0 {
		return math.Sqrt(4.0 - (x-4.0)*(x-4.0))
	}

	// Вне заданных участков графика
	return 0.0
}

func main() {
	var Xn, Xk, dx float64

	fmt.Print("Введите начальный X, конечный X, шаг dx: ")
	fmt.Scan(&Xn, &Xk, &dx)

	if dx <= 0 {
		fmt.Println("Ошибка: шаг должен быть положительным!")
		return
	}

	fmt.Println("\n------------------------------------------")
	fmt.Println("|     x    |             y              |")
	fmt.Println("------------------------------------------")

	for x := Xn; x <= Xk+1e-9; x += dx {
		y := f(x)

		fmt.Printf("| %8.4f | %24.4f |\n", x, y)
	}

	fmt.Println("------------------------------------------")
}