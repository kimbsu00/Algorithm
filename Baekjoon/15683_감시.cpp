#include <iostream>
#include <vector>

struct Position
{
    int row, col;
};

enum Direction
{
    LEFT,
    TOP,
    RIGHT,
    BOTTOM
};

using namespace std;

int N, M;
int map[8][8];
vector<Position> cctv;

void print_map()
{
    for (int row = 0; row < N; row++)
    {
        for (int col = 0; col < M; col++)
        {
            printf("%d ", map[row][col]);
        }
        printf("\n");
    }
}

int get_rectangle_area_size()
{
    int ret = 0;
    for (int row = 0; row < N; row++)
    {
        for (int col = 0; col < M; col++)
        {
            if (map[row][col] == 0)
            {
                ret += 1;
            }
        }
    }
    return ret;
}

void commit(int row, int col, Direction dir, int idx)
{
    int value = (idx * 10) + 9;
    if (dir == Direction::LEFT)
    {
        for (int idx = col - 1; idx >= 0; idx--)
        {
            if (map[row][idx] == 0)
            {
                map[row][idx] = value;
            }
            else if (map[row][idx] == 6)
            {
                break;
            }
        }
    }
    else if (dir == Direction::TOP)
    {
        for (int idx = row - 1; idx >= 0; idx--)
        {
            if (map[idx][col] == 0)
            {
                map[idx][col] = value;
            }
            else if (map[idx][col] == 6)
            {
                break;
            }
        }
    }
    else if (dir == Direction::RIGHT)
    {
        for (int idx = col + 1; idx < M; idx++)
        {
            if (map[row][idx] == 0)
            {
                map[row][idx] = value;
            }
            else if (map[row][idx] == 6)
            {
                break;
            }
        }
    }
    else if (dir == Direction::BOTTOM)
    {
        for (int idx = row + 1; idx < N; idx++)
        {
            if (map[idx][col] == 0)
            {
                map[idx][col] = value;
            }
            else if (map[idx][col] == 6)
            {
                break;
            }
        }
    }
}

void discard(int row, int col, Direction dir, int idx)
{
    int value = (idx * 10) + 9;
    if (dir == Direction::LEFT)
    {
        for (int idx = col - 1; idx >= 0; idx--)
        {
            if (map[row][idx] == value)
            {
                map[row][idx] = 0;
            }
            else if (map[row][idx] == 6)
            {
                break;
            }
        }
    }
    else if (dir == Direction::TOP)
    {
        for (int idx = row - 1; idx >= 0; idx--)
        {
            if (map[idx][col] == value)
            {
                map[idx][col] = 0;
            }
            else if (map[idx][col] == 6)
            {
                break;
            }
        }
    }
    else if (dir == Direction::RIGHT)
    {
        for (int idx = col + 1; idx < M; idx++)
        {
            if (map[row][idx] == value)
            {
                map[row][idx] = 0;
            }
            else if (map[row][idx] == 6)
            {
                break;
            }
        }
    }
    else if (dir == Direction::BOTTOM)
    {
        for (int idx = row + 1; idx < N; idx++)
        {
            if (map[idx][col] == value)
            {
                map[idx][col] = 0;
            }
            else if (map[idx][col] == 6)
            {
                break;
            }
        }
    }
}

int solve(int idx)
{
    if (idx >= cctv.size())
    {
        return get_rectangle_area_size();
    }

    int row = cctv[idx].row;
    int col = cctv[idx].col;
    int num = map[row][col];

    int answer = 987654321;
    // 1 Direction
    if (num == 1)
    {
        commit(row, col, Direction::LEFT, idx);
        answer = min(answer, solve(idx + 1));
        discard(row, col, Direction::LEFT, idx);

        commit(row, col, Direction::TOP, idx);
        answer = min(answer, solve(idx + 1));
        discard(row, col, Direction::TOP, idx);

        commit(row, col, Direction::RIGHT, idx);
        answer = min(answer, solve(idx + 1));
        discard(row, col, Direction::RIGHT, idx);

        commit(row, col, Direction::BOTTOM, idx);
        answer = min(answer, solve(idx + 1));
        discard(row, col, Direction::BOTTOM, idx);
    }
    // 2 Direction / Opposite
    else if (num == 2)
    {
        commit(row, col, Direction::LEFT, idx);
        commit(row, col, Direction::RIGHT, idx);
        answer = min(answer, solve(idx + 1));
        discard(row, col, Direction::LEFT, idx);
        discard(row, col, Direction::RIGHT, idx);

        commit(row, col, Direction::TOP, idx);
        commit(row, col, Direction::BOTTOM, idx);
        answer = min(answer, solve(idx + 1));
        discard(row, col, Direction::TOP, idx);
        discard(row, col, Direction::BOTTOM, idx);
    }
    // 2 Direction / 90 degree
    else if (num == 3)
    {
        commit(row, col, Direction::LEFT, idx);
        commit(row, col, Direction::TOP, idx);
        answer = min(answer, solve(idx + 1));
        discard(row, col, Direction::LEFT, idx);
        discard(row, col, Direction::TOP, idx);

        commit(row, col, Direction::TOP, idx);
        commit(row, col, Direction::RIGHT, idx);
        answer = min(answer, solve(idx + 1));
        discard(row, col, Direction::TOP, idx);
        discard(row, col, Direction::RIGHT, idx);

        commit(row, col, Direction::RIGHT, idx);
        commit(row, col, Direction::BOTTOM, idx);
        answer = min(answer, solve(idx + 1));
        discard(row, col, Direction::RIGHT, idx);
        discard(row, col, Direction::BOTTOM, idx);

        commit(row, col, Direction::BOTTOM, idx);
        commit(row, col, Direction::LEFT, idx);
        answer = min(answer, solve(idx + 1));
        discard(row, col, Direction::BOTTOM, idx);
        discard(row, col, Direction::LEFT, idx);
    }
    // 3 Direction
    else if (num == 4)
    {
        commit(row, col, Direction::LEFT, idx);
        commit(row, col, Direction::TOP, idx);
        commit(row, col, Direction::RIGHT, idx);
        answer = min(answer, solve(idx + 1));
        discard(row, col, Direction::LEFT, idx);
        discard(row, col, Direction::TOP, idx);
        discard(row, col, Direction::RIGHT, idx);

        commit(row, col, Direction::TOP, idx);
        commit(row, col, Direction::RIGHT, idx);
        commit(row, col, Direction::BOTTOM, idx);
        answer = min(answer, solve(idx + 1));
        discard(row, col, Direction::TOP, idx);
        discard(row, col, Direction::RIGHT, idx);
        discard(row, col, Direction::BOTTOM, idx);

        commit(row, col, Direction::RIGHT, idx);
        commit(row, col, Direction::BOTTOM, idx);
        commit(row, col, Direction::LEFT, idx);
        answer = min(answer, solve(idx + 1));
        discard(row, col, Direction::RIGHT, idx);
        discard(row, col, Direction::BOTTOM, idx);
        discard(row, col, Direction::LEFT, idx);

        commit(row, col, Direction::BOTTOM, idx);
        commit(row, col, Direction::LEFT, idx);
        commit(row, col, Direction::TOP, idx);
        answer = min(answer, solve(idx + 1));
        discard(row, col, Direction::BOTTOM, idx);
        discard(row, col, Direction::LEFT, idx);
        discard(row, col, Direction::TOP, idx);
    }
    // 4 Direction
    else if (num == 5)
    {
        commit(row, col, Direction::LEFT, idx);
        commit(row, col, Direction::TOP, idx);
        commit(row, col, Direction::RIGHT, idx);
        commit(row, col, Direction::BOTTOM, idx);
        answer = min(answer, solve(idx + 1));
        discard(row, col, Direction::LEFT, idx);
        discard(row, col, Direction::TOP, idx);
        discard(row, col, Direction::RIGHT, idx);
        discard(row, col, Direction::BOTTOM, idx);
    }

    return answer;
}

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> N >> M;

    for (int row = 0; row < N; row++)
    {
        for (int col = 0; col < M; col++)
        {
            cin >> map[row][col];

            if (0 < map[row][col] && map[row][col] < 6)
            {
                cctv.push_back({row, col});
            }
        }
    }

    int answer = solve(0);
    cout << answer << "\n";

    return 0;
}
