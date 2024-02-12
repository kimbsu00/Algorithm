#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int N;
vector<int> building;

int solve(int idx)
{
    int ret = 0;
    int cur_building = building[idx];

    if (idx > 0)
    {
        ret += 1;

        double slope = building[idx] - building[idx - 1];

        for (int x = idx - 2; x >= 0; x--)
        {
            int prev_building = building[x];
            double cur_slope = (double)(cur_building - prev_building) / (double)(idx - x);
            if (cur_slope < slope)
            {
                slope = cur_slope;
                ret += 1;
            }
        }
    }

    if (idx < N - 1)
    {
        ret += 1;

        double slope = building[idx + 1] - building[idx];

        for (int x = idx + 2; x < N; x++)
        {
            int next_building = building[x];
            double cur_slope = (double)(next_building - cur_building) / (double)(x - idx);
            if (cur_slope > slope)
            {
                slope = cur_slope;
                ret += 1;
            }
        }
    }

    return ret;
}

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> N;
    int height;
    for (int idx = 0; idx < N; idx++)
    {
        cin >> height;
        building.push_back(height);
    }

    int answer = 0;
    for (int idx = 0; idx < N; idx++)
    {
        answer = max(answer, solve(idx));
    }
    printf("%d\n", answer);

    return 0;
}
