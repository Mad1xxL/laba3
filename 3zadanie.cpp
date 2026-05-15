#include <iostream>
#include <cmath>

int64_t gcd(int64_t a, int64_t b) {
    while (b) {
        int64_t r = a % b;
        a = b;
        b = r;
    }
    return a;
}

int main() {
    int a;
    int b;
    std::cin >> a >> b;

    if (b == 1) {
        std::cout << "infinity";
        return 0;
    }

    double sum = 0;
    double term = 1.0 / b;

    for (int n = 1; n <= 1000000 && term > 1e-15; n++) {
        if (n > 1) {
            term *= pow(1.0 * n / (n - 1), a) / b;
        }
        sum += term;
    }

    int64_t num = 0;
    int64_t den = 1;

    for (int64_t d = 1; d <= 1000000; d++) {
        int64_t n = round(sum * d);

        if (fabs(sum - 1.0 * n / d) < 1e-12) {
            num = n;
            den = d;
            break;
        }
    }

    int64_t g = gcd(abs(num), den);

    num /= g;
    den /= g;

    std::cout << num << "/" << den;

    return 0;
}