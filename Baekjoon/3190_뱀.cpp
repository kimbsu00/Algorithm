#include <iostream>
#include <vector>
#include <queue>

using namespace std;

enum Marker
{
    BLANK,
    WALL,
    APPLE,
    SNAKE
};

struct Pos
{
    int row, col;
};

int N, K, L;
Marker map[102][102];
deque<Pos> snake;
/**
 * (0, LEFT)
 * (1, UP)
 * (2, RIGHT)
 * (3, DOWN)
 */
int dir = 2;

void print_map()
{
    for (int row = 0; row <= N + 1; row++)
    {
        for (int col = 0; col <= N + 1; col++)
        {
            printf("%d ", map[row][col]);
        }
        printf("\n");
    }

    printf("\n");
}

pair<int, bool> move_until_time(int cur_time, int time)
{
    if (cur_time >= time)
    {
        return {cur_time, true};
    }

    int ret = cur_time;
    while (ret < time)
    {
        ret += 1;

        Pos head = snake.front();
        Pos tail = snake.back();
        Pos next_head = {head.row, head.col};
        switch (dir)
        {
            // LEFT
        case 0:
            next_head.col -= 1;
            break;
            // UP
        case 1:
            next_head.row -= 1;
            break;
            // RIGHT
        case 2:
            next_head.col += 1;
            break;
            // DOWN
        case 3:
            next_head.row += 1;
            break;
        }

        Marker &what = map[next_head.row][next_head.col];
        if (what == Marker::WALL)
        {
            return {ret, false};
        }
        else if (what == Marker::SNAKE)
        {
            return {ret, false};
        }
        else if (what == Marker::APPLE)
        {
            what = Marker::SNAKE;
            snake.push_front(next_head);
        }
        else
        {
            what = Marker::SNAKE;
            map[tail.row][tail.col] = Marker::BLANK;
            snake.push_front(next_head);
            snake.pop_back();
        }

        // print_map();
    }

    return {ret, true};
}

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> N >> K;

    fill(&map[0][0], &map[101][102], Marker::WALL);
    for (int row = 1; row <= N; row++)
    {
        for (int col = 1; col <= N; col++)
        {
            map[row][col] = Marker::BLANK;
        }
    }

    int row, col;
    for (int idx = 0; idx < K; idx++)
    {
        cin >> row >> col;
        map[row][col] = Marker::APPLE;
    }
    map[1][1] = Marker::SNAKE;

    cin >> L;

    snake.push_back({1, 1});

    int X, time = 0;
    char C;
    bool done_flag = false;
    for (int idx = 0; idx < L; idx++)
    {
        cin >> X >> C;

        if (done_flag)
        {
            continue;
        }

        pair<int, bool> result = move_until_time(time, X);
        time = result.first;

        if (!result.second)
        {
            done_flag = true;
        }

        if (C == 'L')
        {
            dir -= 1;

            if (dir < 0)
            {
                dir = 3;
            }
        }
        else if (C == 'D')
        {
            dir += 1;
            dir %= 4;
        }
    }

    if (!done_flag)
    {
        pair<int, bool> result = move_until_time(time, 1000);
        time = result.first;
    }

    cout << time << "\n";

    return 0;
}
