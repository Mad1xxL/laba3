#include <iostream>

long long gcd (long long a, long long b){
    return b == 0 ? a : gcd(b, a % b);
}

void matSum(int a, int b)    {
    if (b == 1) {
        std::cout << "infinity" << std::endl;
        return;
    }

    int num;
    int den;

    if (a == 1) {
        num = b;
        den = (b-1) * (b-1);
    }

    else if (a == 2) {
        num = b * (b+1);
        den = (b-1) * (b-1) * (b-1);
    }

    else if (a == 3) {
        num = b * (b * b + 4 * b + 1);
        den = (b-1) * (b-1) * (b-1) * (b-1);
    }

    }

    num /= nod;
    den /= nod;

    std::cout << num << "/" << den << std::endl;
}

int main()  {
    int a;
    std::cout << "Введите значение a: ";
    std::cin >> a;

    int b;
    std::cout << "Введите значение b: ";
    std::cin >> b;

    if (b == 1) {
        std::cout << "infinity" << std::endl;
        return 0;
    }

    

    matSum(a,b);
    
    return 0;
}