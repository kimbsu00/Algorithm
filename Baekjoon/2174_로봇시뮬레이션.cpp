/*
  url: https://www.acmicpc.net/problem/2174
*/

#include <iostream>
#include <string>

using namespace std;

class Robot
{
public:
    int x;
    int y;
    char dir;

    Robot() : x(-1), y(-1), dir(' ') {}
    Robot(int px, int py, char p_dir) : x(px), y(py), dir(p_dir) {}
};

int A, B, N, M;
Robot robot[100];
int map[100][100];

string crash_into_wall(int robot_idx)
{
    return "Robot " + to_string(robot_idx + 1) + " crashes into the wall";
}

string crash_into_robot(int robot_idx1, int robot_idx2)
{
    return "Robot " + to_string(robot_idx1 + 1) + " crashes into robot " + to_string(robot_idx2 + 1);
}

string command(const int &robot_idx, const char &cmd, int repeat)
{
    if (repeat == 0)
        return "OK";

    string ret = "OK";
    char cur_dir = robot[robot_idx].dir;
    // 왼쪽으로 90도 회전
    if (cmd == 'L')
    {
        // 동쪽
        if (cur_dir == 'E')
            robot[robot_idx].dir = 'N';
        // 서쪽
        else if (cur_dir == 'W')
            robot[robot_idx].dir = 'S';
        // 남쪽
        else if (cur_dir == 'S')
            robot[robot_idx].dir = 'E';
        // 북쪽
        else
            robot[robot_idx].dir = 'W';

        ret = command(robot_idx, cmd, repeat - 1);
    }
    // 오른쪽으로 90도 회전
    else if (cmd == 'R')
    {
        // 동쪽
        if (cur_dir == 'E')
            robot[robot_idx].dir = 'S';
        // 서쪽
        else if (cur_dir == 'W')
            robot[robot_idx].dir = 'N';
        // 남쪽
        else if (cur_dir == 'S')
            robot[robot_idx].dir = 'W';
        // 북쪽
        else
            robot[robot_idx].dir = 'E';

        ret = command(robot_idx, cmd, repeat - 1);
    }
    // 앞으로 한 칸 이동
    else if (cmd == 'F')
    {
        int cur_x = robot[robot_idx].x;
        int cur_y = robot[robot_idx].y;
        // 동쪽
        if (cur_dir == 'E')
        {
            int next_x = cur_x + 1;
            if (next_x >= A)
            {
                ret = crash_into_wall(robot_idx);
            }
            else if (map[cur_y][next_x] != -1)
            {
                ret = crash_into_robot(robot_idx, map[cur_y][next_x]);
            }
            else
            {
                map[cur_y][cur_x] = -1;
                robot[robot_idx].x = next_x;
                map[cur_y][next_x] = robot_idx;

                ret = command(robot_idx, cmd, repeat - 1);
            }
        }
        // 서쪽
        else if (cur_dir == 'W')
        {
            int next_x = cur_x - 1;
            if (next_x < 0)
            {
                ret = crash_into_wall(robot_idx);
            }
            else if (map[cur_y][next_x] != -1)
            {
                ret = crash_into_robot(robot_idx, map[cur_y][next_x]);
            }
            else
            {
                map[cur_y][cur_x] = -1;
                robot[robot_idx].x = next_x;
                map[cur_y][next_x] = robot_idx;

                ret = command(robot_idx, cmd, repeat - 1);
            }
        }
        // 남쪽
        else if (cur_dir == 'S')
        {
            int next_y = cur_y + 1;
            if (next_y >= B)
            {
                ret = crash_into_wall(robot_idx);
            }
            else if (map[next_y][cur_x] != -1)
            {
                ret = crash_into_robot(robot_idx, map[next_y][cur_x]);
            }
            else
            {
                map[cur_y][cur_x] = -1;
                robot[robot_idx].y = next_y;
                map[next_y][cur_x] = robot_idx;

                ret = command(robot_idx, cmd, repeat - 1);
            }
        }
        // 북쪽
        else
        {
            int next_y = cur_y - 1;
            if (next_y < 0)
            {
                ret = crash_into_wall(robot_idx);
            }
            else if (map[next_y][cur_x] != -1)
            {
                ret = crash_into_robot(robot_idx, map[next_y][cur_x]);
            }
            else
            {
                map[cur_y][cur_x] = -1;
                robot[robot_idx].y = next_y;
                map[next_y][cur_x] = robot_idx;

                ret = command(robot_idx, cmd, repeat - 1);
            }
        }
    }

    return ret;
}

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> A >> B >> N >> M;

    fill(&map[0][0], &map[99][100], -1);

    int x, y;
    char dir;
    for (int idx = 0; idx < N; idx++)
    {
        cin >> x >> y >> dir;
        x -= 1;
        y = B - y;

        robot[idx] = Robot(x, y, dir);
        map[y][x] = idx;
    }

    int robot_idx, repeat;
    char cmd;
    string ret = "OK";
    for (int idx = 0; idx < M; idx++)
    {
        cin >> robot_idx >> cmd >> repeat;

        ret = command(robot_idx - 1, cmd, repeat);
        if (ret != "OK")
            break;
    }
    cout << ret << "\n";

    return 0;
}
