#include <iostream>
#include <cmath>
#include <iomanip>
#include <vector>

using namespace std;

int main() {
    double T_0 = 0;
    double T_sr = 0;
    double r = 0;
    int minutes = 0;

    cout << "Введите начальную температуру кофе: ";
    cin >> T_0;

    cout << "Введите температуру окружающей среды: ";
    cin >> T_sr;

    cout << "Введите коэффициент охлаждения r: ";
    cin >> r;

    cout << "Введите время наблюдения в минутах: ";
    cin >> minutes;

    vector<double> time;
    vector<double> temp;

    time.resize(minutes);
    temp.resize(minutes);

    cout << "\nТаблица изменения температуры кофе:\n";
    cout << "---------------------------------\n";
    cout << "| Минута | Температура кофе, °C |\n";
    cout << "---------------------------------\n";

    for (int t = 1; t <= minutes; t++) {
        double currentTemp = T_sr + (T_0 - T_sr) * exp(-r * t);

        time[t - 1] = t;
        temp[t - 1] = currentTemp;

        cout << "| "
             << setw(6) << t
             << " | "
             << setw(20) << fixed << setprecision(2) << currentTemp
             << " |\n";
    }

    cout << "---------------------------------\n";

    int n = minutes;

    double sum_x = 0;
    double sum_y = 0;
    double sum_xy = 0;
    double sum_x2 = 0;

    for (int i = 0; i < n; i++) {
        double x = time[i];
        double y = temp[i];

        sum_x += x;
        sum_y += y;
        sum_xy += x * y;
        sum_x2 += x * x;
    }

    double denominator = n * sum_x2 - sum_x * sum_x;

    if (fabs(denominator) < 1e-9) {
        cout << "Аппроксимацию вычислить невозможно\n";
    } else {
        double a = (n * sum_xy - sum_x * sum_y) / denominator;
        double b = (sum_y - a * sum_x) / n;

        double mean_y = sum_y / n;
        double ss_res = 0;
        double ss_tot = 0;

        for (int i = 0; i < n; i++) {
            double predict = a * time[i] + b;

            ss_res += (temp[i] - predict) * (temp[i] - predict);
            ss_tot += (temp[i] - mean_y) * (temp[i] - mean_y);
        }

        double r2 = 0;

        if (ss_tot > 0) {
            r2 = 1 - ss_res / ss_tot;
        }

        cout << fixed << setprecision(4);
        cout << "\nЛинейная аппроксимация:\n";
        cout << "a = " << a << " °C/мин\n";
        cout << "b = " << b << " °C\n";
        cout << "Коэффициент детерминации R^2 = " << r2 << "\n";
    }

    return 0;
}