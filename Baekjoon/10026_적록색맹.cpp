#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

const int RED = 0;
const int GREEN = 1;
const int BLUE = 2;

// left, top, right, bottom
const int dr[4] = {0, -1, 0, 1};
const int dc[4] = {-1, 0, 1, 0};

int N;
int map[102][102][2];
bool visited[102][102][2];

void solve(int row, int col, const int &color_blind)
{
    // Out of index
    if (map[row][col][color_blind] == -1)
    {
        return;
    }

    visited[row][col][color_blind] = true;

    int cur_color = map[row][col][color_blind];
    for (int idx = 0; idx < 4; idx++)
    {
        int next_row = row + dr[idx];
        int next_col = col + dc[idx];
        int next_color = map[next_row][next_col][color_blind];

        if (!visited[next_row][next_col][color_blind] && cur_color == next_color)
        {
            solve(next_row, next_col, color_blind);
        }
    }
}

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    scanf("%d", &N);

    fill(&map[0][0][0], &map[101][101][2], -1);
    fill(&visited[0][0][0], &visited[101][101][2], false);

    for (int row = 1; row <= N; row++)
    {
        getchar();
        for (int col = 1; col <= N; col++)
        {
            char ch = getchar();

            if (ch == 'R')
            {
                map[row][col][0] = RED;
                map[row][col][1] = RED;
            }
            else if (ch == 'G')
            {
                map[row][col][0] = GREEN;
                map[row][col][1] = RED;
            }
            else if (ch == 'B')
            {
                map[row][col][0] = BLUE;
                map[row][col][1] = BLUE;
            }
        }
    }

    int normal_cnt = 0;
    int color_blind_cnt = 0;
    for (int row = 1; row <= N; row++)
    {
        for (int col = 1; col <= N; col++)
        {
            if (!visited[row][col][0])
            {
                normal_cnt += 1;
                solve(row, col, 0);
            }

            if (!visited[row][col][1])
            {
                color_blind_cnt += 1;
                solve(row, col, 1);
            }
        }
    }

    cout << normal_cnt << " " << color_blind_cnt << "\n";

    return 0;
}
