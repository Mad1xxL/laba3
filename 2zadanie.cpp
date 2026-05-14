#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iomanip>

//мод числа
long long mod(long long base, long long power, long long modulo) {
    long long result = 1;

    while (power > 0) {
        if (power % 2 == 1) {
            result = (result * base) % modulo;
        }

        base = (base * base) % modulo;
        power /= 2;
    }

    return result;
}

//Простые числа до 500
std::vector<int> buildSimple() {
    const int limit = 500;

    std::vector<bool> isSimple(limit, true);
    std::vector<int> simple;

    isSimple[0] = false;
    isSimple[1] = false;

    for (int i = 2; i < limit; i++) {
        if (isSimple[i]) {
            simple.push_back(i);

            for (int j = i * i; j < limit; j += i) {
                isSimple[j] = false;
            }
        }
    }

    return simple;
}

//Проверка есть ли элемент x в контейнере
bool contains(const std::vector<long long>& values, long long x) {
    for (long long value : values) {
        if (value == x) {
            return true;
        }
    }

    return false;
}

//Генерация числа m
long long generateM(
    int bits,
    const std::vector<int>& simple,
    std::vector<long long>& simpleDel
) {
    int mBits = bits - 1;

    long long minM = 1LL << (mBits - 1);
    long long maxM = (1LL << mBits) - 1;

    while (true) {
        long long m = 1;
        simpleDel.clear();

        while (true) {
            int q = simple[std::rand() % simple.size()];

            if (m * q > maxM) {
                break;
            }

            m *= q;

            if (!contains(simpleDel, q)) {
                simpleDel.push_back(q);
            }
        }

        if (m >= minM && m <= maxM) {
            return m;
        }
    }
}

//Проверка числа тестом Миллера
bool millerTest(
    long long n,
    int t,
    const std::vector<long long>& simpleDel
) {
    if (n < 2) {
        return false;
    }

    if (n == 2 || n == 3) {
        return true;
    }

    if (n % 2 == 0 || n % 3 == 0) {
        return false;
    }

    std::vector<long long> bases;

    while ((int)bases.size() < t) {
        long long base = 2 + std::rand() % (n - 3);

        if (!contains(bases, base)) {
            bases.push_back(base);
        }
    }

    for (long long base : bases) {
        if (mod(base, n - 1, n) != 1) {
            return false;
        }
    }

    for (long long q : simpleDel) {
        bool hasNotOne = false;

        for (long long base : bases) {
            if (mod(base, (n - 1) / q, n) != 1) {
                hasNotOne = true;
                break;
            }
        }

        if (!hasNotOne) {
            return false;
        }
    }

    return true;
}

int main() {
    std::srand(std::time(0));

    int bits;

    std::cout << "Введите битность: ";
    std::cin >> bits;

    if (bits < 3 || bits > 30) {
        std::cout << "Ошибка: bits должен быть от 3 до 30\n";
        return 1;
    }

    std::vector<int> simple = buildSimple();

    std::cout << "\n-----------------------------------------------\n";
    std::cout << "| "
              << std::setw(3) << "N"
              << " | "
              << std::setw(14) << "Простое число"
              << " | "
              << std::setw(9) << "Результат"
              << " | "
              << std::setw(9) << "Rejected"
              << " |\n";
    std::cout << "-----------------------------------------------\n";

    for (int i = 1; i <= 10; i++) {
        long long number = 0;
        int rejected = 0;
        bool result = false;

        while (true) {
            std::vector<long long> simpleDel;

            long long m = generateM(bits, simple, simpleDel);
            number = 2 * m + 1;

            if (!contains(simpleDel, 2)) {
                simpleDel.push_back(2);
            }

            bool firstCheck = millerTest(number, 5, simpleDel);

            if (!firstCheck) {
                rejected++;
                result = false;
                break;
            }

            result = millerTest(number, 2, simpleDel);

            if (!result) {
                rejected++;
            }

            break;
        }

        std::cout << "| "
                  << std::setw(3) << i
                  << " | "
                  << std::setw(14) << number
                  << " | "
                  << std::setw(9) << (result ? "true" : "false")
                  << " | "
                  << std::setw(9) << rejected
                  << " |\n";
    }

    std::cout << "-----------------------------------------------\n";

    return 0;
}