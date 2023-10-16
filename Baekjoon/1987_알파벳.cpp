#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// left, top, right, bottom
const int dr[4] = {0, -1, 0, 1};
const int dc[4] = {-1, 0, 1, 0};

bool visited[26];
int R, C;
char map[22][22];

int solve(int row, int col)
{
    char ch = map[row][col];
    visited[ch - 'A'] = true;

    int ret = 0;
    for (int idx = 0; idx < 4; idx++)
    {
        int next_row = row + dr[idx];
        int next_col = col + dc[idx];

        char next_ch = map[next_row][next_col];
        if ((next_ch != 0) && (!visited[next_ch - 'A']))
        {
            ret = max(ret, solve(next_row, next_col));
        }
    }

    visited[ch - 'A'] = false;
    return 1 + ret;
}

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    fill(&visited[0], &visited[26], false);
    fill(&map[0][0], &map[21][22], 0);

    scanf("%d %d", &R, &C);

    getchar();
    char ch;
    for (int row = 1; row <= R; row++)
    {
        for (int col = 1; col <= C; col++)
        {
            map[row][col] = getchar();
        }
        getchar();
    }

    int answer = solve(1, 1);
    printf("%d\n", answer);

    return 0;
}
