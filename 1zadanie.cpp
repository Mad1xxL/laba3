#include <iostream>
#include <iomanip>
#include <cmath>


double f(double x) {

    // 1. Левая полуокружность
    if (x >= -6.0 && x <= -4.0) {
        return -sqrt(4.0 - (x + 4.0) * (x + 4.0));
    }

    // 2. y = cbrt(2x)
    else if (x > -4.0 && x <= 4.0) {
        return cbrt(2.0 * x);
    }

    // 3. Правая полуокружность
    else if (x > 4.0 && x <= 6.0) {
        return sqrt(4.0 - (x - 4.0) * (x - 4.0));
    }

    // Вне заданных участков графика
    else {
        return 0.0;
    }
}

int main() {
    double Xn, Xk, dx;

    std::cout << "Введите начальный X, конечный X, шаг dx: ";
    std::cin >> Xn >> Xk >> dx;

    // Проверка шага
    if (dx <= 0) {
        std::cout << "Ошибка: шаг должен быть положительным!" << std::endl;
        return 1;
    }

    std::cout << std::fixed << std::setprecision(4);

    std::cout << "\n-------------------------------\n";
    std::cout << "|     x        |       y      |\n";
    std::cout << "-------------------------------\n";

    for (double x = Xn; x <= Xk + 1e-9; x += dx) {

        if (x < -6.0 || x > 6.0) {
            std::cout << "| "
                    << std::setw(12) << x
                    << " | "
                    << std::setw(12) << "Not defined"
                    << " |\n";
        }
        else {
            double y = f(x);

            std::cout << "| "
                    << std::setw(12) << x
                    << " | "
                    << std::setw(12) << y
                    << " |\n";
        }
    }

    std::cout << "-------------------------------\n";

    return 0;
}