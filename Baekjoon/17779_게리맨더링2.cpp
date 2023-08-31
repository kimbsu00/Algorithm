#include <iostream>
#include <vector>

using namespace std;

const int INF = 987654321;

int N;
vector<vector<int>> map;

int get_minimum_diff(int x, int y, int d1, int d2)
{

    int people[5] = {0, 0, 0, 0, 0};
    vector<vector<int>> tmp = vector<vector<int>>(N, vector<int>(N, 0));

    for (int row = 0; row < N; row++)
    {
        for (int col = 0; col < N; col++)
        {
            // 1번 선거구
            if ((row < x + d1) && (col <= y) && (row < -col + x + y))
            {
                people[0] += map[row][col];
                tmp[row][col] = 1;
            }
            // 2번 선거구
            else if ((row <= x + d2) && (col < N) && (row < col + x - y))
            {
                people[1] += map[row][col];
                tmp[row][col] = 2;
            }
            // 3번 선거구
            else if ((x + d1 <= row) && (col < y - d1 + d2) && (row > col + x - y + 2 * d1))
            {
                people[2] += map[row][col];
                tmp[row][col] = 3;
            }
            // 4번 선거구
            else if ((x + d2 < row) && (y - d1 + d2 <= col) && (row > -col + x + y + 2 * d2))
            {
                people[3] += map[row][col];
                tmp[row][col] = 4;
            }
            // 5번 선거구
            else
            {
                people[4] += map[row][col];
                tmp[row][col] = 5;
            }
        }
    }

    if (people[0] == 0 || people[1] == 0 || people[2] == 0 || people[3] == 0 || people[4] == 0)
    {
        return INF;
    }

    int max_value = 0;
    int min_value = INF;
    for (int idx = 0; idx < 5; idx++)
    {
        if (max_value < people[idx])
        {
            max_value = people[idx];
        }

        if (min_value > people[idx])
        {
            min_value = people[idx];
        }
    }

    return max_value - min_value;
}

bool check_range(int x, int y, int d1, int d2)
{
    return (1 <= d1) && (1 <= d2) && (x + d1 + d2 < N) && (0 <= y - d1) && (y + d2 < N);
}

int solve(int x, int y)
{
    int d1 = 1;
    int d2 = 1;

    int ret = INF;
    for (d1 = 1; check_range(x, y, d1, d2); d1++)
    {
        for (d2 = 1; check_range(x, y, d1, d2); d2++)
        {
            ret = min(ret, get_minimum_diff(x, y, d1, d2));
        }
        d2 = 1;
    }

    return ret;
}

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> N;

    map = vector<vector<int>>(N, vector<int>(N, 0));
    for (int row = 0; row < N; row++)
    {
        for (int col = 0; col < N; col++)
        {
            cin >> map[row][col];
        }
    }

    int answer = INF;
    for (int x = 0; x < N; x++)
    {
        for (int y = 0; y < N; y++)
        {
            answer = min(answer, solve(x, y));
        }
    }

    cout << answer << "\n";

    return 0;
}
