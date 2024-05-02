#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int N;
vector<int> pay, cache;

pair<int, int> solve(int day)
{
    int cur_pay = pay[day];

    int left_cnt = 0;
    int idx = day - 1;
    while (idx >= 0)
    {
        if (pay[idx] >= cur_pay)
        {
            if (cache[idx] != -1)
            {
                left_cnt += cache[idx] + 1;
                idx -= (cache[idx] + 1);
            }
            else
            {
                left_cnt += 1;
                idx -= 1;
            }
        }
        else
        {
            break;
        }
    }

    int right_cnt = 0;
    idx = day + 1;
    while (idx < N)
    {
        if (pay[idx] >= cur_pay)
        {
            right_cnt += 1;
            idx += 1;
        }
        else
        {
            break;
        }
    }

    return {left_cnt, right_cnt};
}

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> N;
    pay = vector<int>(N, 0);
    cache = vector<int>(N, -1);

    for (int idx = 0; idx < N; idx++)
    {
        cin >> pay[idx];
    }

    int answer = 0;
    for (int day = 0; day < N; day++)
    {
        pair<int, int> ret = solve(day);
        cache[day] = ret.first;

        int sum = ret.first + ret.second + 1;
        answer = max(answer, sum * pay[day]);
    }

    printf("%d\n", answer);

    return 0;
}
