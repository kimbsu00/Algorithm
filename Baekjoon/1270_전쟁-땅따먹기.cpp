#include <iostream>
#include <map>

using namespace std;

int n;

long long solve(int T, long long *soldier)
{
    map<long long, int> m;

    for (int idx = 0; idx < T; idx++)
    {
        pair<map<long long, int>::iterator, bool> p = m.insert({soldier[idx], 1});

        // 새로 추가한 경우
        if (p.second)
        {
            // do nothing
        }
        // 이전에 추가한적 있는 경우
        else
        {
            p.first->second += 1;
        }
    }

    long long country = -1;
    int max_soldier = -1;
    for (auto it = m.begin(); it != m.end(); it++)
    {
        if (max_soldier < it->second)
        {
            country = it->first;
            max_soldier = it->second;
        }
    }

    return max_soldier > (T / 2) ? country : -1;
}

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n;

    for (int idx = 0; idx < n; idx++)
    {
        int T;
        cin >> T;

        long long *soldier = new long long[T];
        for (int t = 0; t < T; t++)
        {
            cin >> soldier[t];
        }

        long long answer = solve(T, soldier);
        cout << (answer == -1 ? "SYJKGW" : to_string(answer)) << "\n";

        delete[] soldier;
    }

    return 0;
}
