#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

struct Pos
{
    int x, y;
};

double solve(vector<Pos> &pos, int idx, int depth, int x, int y)
{
    if (depth == 0)
    {
        return sqrt(((long long)x * x) + ((long long)y * y));
    }

    if (idx == pos.size())
    {
        return 1987654321.0;
    }

    int next_x = x - 2 * pos[idx].x;
    int next_y = y - 2 * pos[idx].y;

    return min(solve(pos, idx + 1, depth, x, y), solve(pos, idx + 1, depth - 1, next_x, next_y));
}

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T;
    cin >> T;

    int N, x, y;
    vector<double> answer;
    for (int tc = 0; tc < T; tc++)
    {
        cin >> N;

        vector<Pos> pos;
        int sum_x = 0, sum_y = 0;
        for (int idx = 0; idx < N; idx++)
        {
            cin >> x >> y;
            sum_x += x;
            sum_y += y;
            pos.push_back({x, y});
        }

        double ans = solve(pos, 0, N / 2, sum_x, sum_y);
        answer.push_back(ans);
    }

    for (double ans : answer)
    {
        printf("%.12lf\n", ans);
    }

    return 0;
}
