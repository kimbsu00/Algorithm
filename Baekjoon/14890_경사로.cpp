#include <iostream>
#include <vector>

using namespace std;

enum Type
{
    ROW,
    COL
};

int N, L;
int map[100][100];
vector<int> continuity;

int solve(Type dir, int value, int idx, int continuous_len)
{
    if (idx == N - 1)
    {
        continuity[idx] = continuous_len;
        return continuous_len;
    }

    int cur_height, next_hieght, diff;
    if (dir == Type::ROW)
    {
        cur_height = map[value][idx];
        next_hieght = map[value][idx + 1];
    }
    else
    {
        cur_height = map[idx][value];
        next_hieght = map[idx + 1][value];
    }
    diff = next_hieght - cur_height;

    if (diff == 0)
    {
        int ret = solve(dir, value, idx + 1, continuous_len + 1);
        continuity[idx] = ret;
        return ret;
    }
    else
    {
        solve(dir, value, idx + 1, 1);
        continuity[idx] = continuous_len;
        return continuous_len;
    }
}

bool check(Type dir, int value)
{
    vector<int> start_pos;

    for (int idx = 0; idx < N - 1; idx++)
    {
        int cur, next;
        if (dir == Type::ROW)
        {
            cur = map[value][idx];
            next = map[value][idx + 1];
        }
        else
        {
            cur = map[idx][value];
            next = map[idx + 1][value];
        }
        int diff = next - cur;

        // 높이 동일
        if (diff == 0)
        {
            // do nothing
        }
        // 한 칸 위로
        else if (diff == 1)
        {
            if (continuity[idx] < L)
            {
                return false;
            }
            else
            {
                start_pos.push_back(idx - L + 1);
            }
        }
        // 한 칸 아래로
        else if (diff == -1)
        {
            if (continuity[idx + 1] < L)
            {
                return false;
            }
            else
            {
                start_pos.push_back(idx + 1);
            }
        }
        // 너무 높아 ~,~
        else
        {
            return false;
        }
    }

    if (!start_pos.empty())
    {
        for (int idx = 0; idx < start_pos.size() - 1; idx++)
        {
            if (start_pos[idx] + L - 1 >= start_pos[idx + 1])
            {
                return false;
            }
        }
    }

    return true;
}

void print_continuity()
{
    for (int idx = 0; idx < N; idx++)
    {
        cout << continuity[idx] << " ";
    }
    cout << "\n\n";
}

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> N >> L;

    for (int row = 0; row < N; row++)
    {
        for (int col = 0; col < N; col++)
        {
            cin >> map[row][col];
        }
    }

    int answer = 0;
    continuity = vector(N, 0);
    for (int row = 0; row < N; row++)
    {
        solve(Type::ROW, row, 0, 1);
        if (check(Type::ROW, row))
        {
            answer += 1;
        }
    }
    for (int col = 0; col < N; col++)
    {
        solve(Type::COL, col, 0, 1);
        if (check(Type::COL, col))
        {
            answer += 1;
        }
    }

    cout << answer << "\n";

    return 0;
}
