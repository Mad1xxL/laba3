#include <iostream>
#include <cmath>

long long gcd(long long a, long long b) {
    while (b) {
        long long r = a % b;
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

    long long num = 0;
    long long den = 1;

    for (long long d = 1; d <= 1000000; d++) {
        long long n = round(sum * d);

        if (fabs(sum - 1.0 * n / d) < 1e-12) {
            num = n;
            den = d;
            break;
        }
    }

    long long g = gcd(llabs(num), den);

    num /= g;
    den /= g;

    std::cout << num << "/" << den;

    return 0;
}