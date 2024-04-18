#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct Flower
{
    int start, end;
} typedef flower;

int N;
vector<flower> flowers;

int solve()
{
    int ret = 0;
    int start = 301;
    while (start < 1201)
    {
        int next_start = start;
        for (int idx = 0; idx < flowers.size(); idx++)
        {
            if (flowers[idx].start <= start && next_start < flowers[idx].end)
            {
                next_start = flowers[idx].end;
            }
        }

        if (next_start == start)
        {
            return 0;
        }
        else
        {
            start = next_start;
            ret += 1;
        }
    }

    return ret;
}

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> N;
    flowers = vector<flower>(N);

    int start_month, start_day, end_month, end_day;
    for (int idx = 0; idx < N; idx++)
    {
        cin >> start_month >> start_day >> end_month >> end_day;
        flowers[idx] = {start_month * 100 + start_day, end_month * 100 + end_day};
    }

    int answer = solve();
    printf("%d\n", answer);

    return 0;
}
