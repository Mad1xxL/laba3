#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>
#include <cstdint>

int main()  {
    int n = 0;
    int m = 0;
    std::cin >> n >> m;

    std::vector<int64_t> a(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }

    std::vector<long long> prefix(n + 1, 0);
    for (int i = 0; i < n; i++) {
        prefix[i + 1] = prefix[i] + a[i];
    }

    int64_t scorePlayers[2] = {0, 0};
    int prevTake[2] = {0, 0};
    int player = 0;                             // 0 — Павел, 1 — Вика
    int pos = 0;

    while (pos < n) {
        int nOstaloc = n - pos;
        int limit = std::min(m, nOstaloc);  
        int64_t bestSum = INT64_MIN;          // Лучшая найденная сумма
        int bestTake = -1;

        for (int take = 1; take <= limit; take++)   {       // Перебор всех возможных ходов
            if (take == prevTake[player])  {
                continue;
            }

            int64_t s = prefix[pos + take] - prefix[pos];
            if (s > bestSum || (s == bestSum && take < bestTake))   {
                bestSum = s;
                bestTake = take;
            }
        }

        if (bestTake == -1) {                   // Если ход не найден
            bestTake = 1;
        }

        scorePlayers[player] += prefix[pos + bestTake] - prefix[pos];   // Добавляем очки текущему игроку
        prevTake[player] = bestTake;
        pos += bestTake;
        player = 1 - player;
    }

    // Победа Павла — 1, иначе 0
    std::cout << (scorePlayers[0] > scorePlayers[1] ? 1 : 0) << "\n";

    return 0;
}