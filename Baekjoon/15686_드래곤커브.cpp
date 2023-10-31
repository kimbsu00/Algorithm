#include <iostream>
#include <vector>

using namespace std;

// RIGHT, TOP, LEFT, BOTTOM
const int dr[4] = {0, -1, 0, 1};
const int dc[4] = {1, 0, -1, 0};

int N, X, Y, D, G;
bool is_dragon_curve_pos[101][101];
int dragon_curve_dir[2049];

bool check_range(int row, int col)
{
    return 0 <= row && row <= 100 && 0 <= col && col <= 100;
}

void make_dragon_curve(int init_row, int init_col, int init_dir)
{
    vector<pair<int, int>> vec;
    vec.push_back({init_row, init_col});
    dragon_curve_dir[0] = init_dir;

    if (check_range(init_row, init_col))
    {
        is_dragon_curve_pos[init_row][init_col] = true;
    }

    int row = init_row;
    int col = init_col;
    for (int idx = 0; idx <= G; idx++)
    {
        int start = (idx == 0) ? 0 : 1 << (idx - 1);
        int size = 1 << idx;

        for (int dir_idx = start; dir_idx < size; dir_idx++)
        {
            int dir = dragon_curve_dir[dir_idx];
            row += dr[dir];
            col += dc[dir];

            vec.push_back({row, col});

            if (check_range(row, col))
            {
                is_dragon_curve_pos[row][col] = true;
            }
        }

        for (int dir_idx = 0; dir_idx < size; dir_idx++)
        {
            int dir = dragon_curve_dir[dir_idx];
            int next_idx = size * 2 - dir_idx - 1;
            dragon_curve_dir[next_idx] = (dir + 1) % 4;
        }
    }
}

int solve()
{
    int ret = 0;

    for (int row = 0; row < 100; row++)
    {
        for (int col = 0; col < 100; col++)
        {
            pair<int, int> lt = {row, col};
            pair<int, int> rt = {row, col + 1};
            pair<int, int> lb = {row + 1, col};
            pair<int, int> rb = {row + 1, col + 1};

            if (is_dragon_curve_pos[lt.first][lt.second] &&
                is_dragon_curve_pos[rt.first][rt.second] &&
                is_dragon_curve_pos[lb.first][lb.second] &&
                is_dragon_curve_pos[rb.first][rb.second])
            {
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

    fill(&is_dragon_curve_pos[0][0], &is_dragon_curve_pos[100][101], false);

    for (int idx = 0; idx < N; idx++)
    {
        fill(&dragon_curve_dir[0], &dragon_curve_dir[1025], -1);

        cin >> X >> Y >> D >> G;

        make_dragon_curve(Y, X, D);
    }

    int answer = solve();
    cout << answer << "\n";

    return 0;
}
