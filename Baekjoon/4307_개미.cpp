#include <iostream>
#include <algorithm>

using namespace std;

int n;

pair<int, int> solve(int length, int ant_cnt, int *pos)
{
    int mid = length / 2;

    int min_time = -1;
    int max_time = -1;

    for (int idx = 0; idx < ant_cnt; idx++)
    {
        int cur_pos = pos[idx];
        if (cur_pos < mid)
        {
            min_time = max(min_time, cur_pos);

            max_time = max(max_time, length - cur_pos);
        }
        else
        {
            min_time = max(min_time, length - cur_pos);

            max_time = max(max_time, cur_pos);
        }
    }

    return {min_time, max_time};
}

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n;

    pair<int, int> *ans = new pair<int, int>[n];
    for (int tc = 0; tc < n; tc++)
    {
        int length, ant_cnt;
        cin >> length >> ant_cnt;

        int *pos = new int[ant_cnt];
        for (int idx = 0; idx < ant_cnt; idx++)
        {
            cin >> pos[idx];
        }

        ans[tc] = solve(length, ant_cnt, pos);

        delete[] pos;
    }

    for (int tc = 0; tc < n; tc++)
    {
        cout << ans[tc].first << " " << ans[tc].second << "\n";
    }

    return 0;
}
