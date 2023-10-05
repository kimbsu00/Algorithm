#include <iostream>
#include <vector>
#include <string>
#include <cmath>

using namespace std;

int xm, ym, xb, yb;
int N;
int direction[8][2] = {
    {0, 1},   // 0   - up
    {-1, 1},  // 45  - left up
    {-1, 0},  // 90  - left
    {-1, -1}, // 135 - left down
    {0, -1},  // 180 - down
    {1, -1},  // 225 - right down
    {1, 0},   // 270 - right
    {1, 1},   // 315 - right up
};
vector<int> command;
vector<vector<int>> path;

double get_dist(long long x1, long long y1, long long x2, long long y2)
{
    return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

double solve()
{
    double ret = 1987654321;

    int x = xm;
    int y = ym;
    int origin_dir = 0;

    for (int idx = 0; idx < path.size(); idx++)
    {
        origin_dir += command[idx];
        origin_dir %= 8;

        for (int bias = 0; bias < 8; bias++)
        {
            int bias_dir = (origin_dir + bias) % 8;
            int dest_x = x + direction[bias_dir][0];
            int dest_y = y + direction[bias_dir][1];

            for (int dir = 0; dir < 8; dir++)
            {
                int rotated_dir = (dir + bias) % 8;

                dest_x += (path[N - 1][dir] - path[idx][dir]) * direction[rotated_dir][0];
                dest_y += (path[N - 1][dir] - path[idx][dir]) * direction[rotated_dir][1];
            }

            ret = min(ret, get_dist(xb, yb, dest_x, dest_y));
        }

        x += direction[origin_dir][0];
        y += direction[origin_dir][1];
    }

    return ret;
}

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> xm >> ym >> xb >> yb;
    cin >> N;

    string input;
    cin >> input;

    path = vector<vector<int>>(N, vector<int>(8, 0));
    int dir = input[0] - '0';
    path[0][dir] += 1;
    command.push_back(dir);

    for (int idx = 1; idx < input.size(); idx++)
    {
        int cmd = input[idx] - '0';
        command.push_back(cmd);

        for (int tmp = 0; tmp < 8; tmp++)
        {
            // idx번째 명령어까지 수행했을 때, tmp 방향으로 이동한 횟수를 의미함
            path[idx][tmp] = path[idx - 1][tmp];
        }

        dir = (dir + cmd) % 8;
        path[idx][dir] += 1;
    }

    double answer = solve();
    printf("%f\n", answer);

    return 0;
}
