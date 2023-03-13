#include <iostream>
#include <queue>

using namespace std;

// left, top, right, bottom
const int dr[4] = {0, -1, 0, 1};
const int dc[4] = {-1, 0, 1, 0};

int height, width;
int cheese[100][100];

bool check_index_range(int row, int col)
{
    return (0 <= row) && (row < height) && (0 <= col) && (col < width);
}

void fill_air(int row, int col)
{
    if (cheese[row][col] != 0)
        return;

    cheese[row][col] = -1;

    for (int idx = 0; idx < 4; idx++)
    {
        int next_row = row + dr[idx];
        int next_col = col + dc[idx];

        if (check_index_range(next_row, next_col) && cheese[next_row][next_col] == 0)
        {
            fill_air(next_row, next_col);
        }
    }
}

pair<int, int> solve()
{
    int prev_cnt = 0;
    int hour = 0;

    queue<pair<int, int>> q;
    while (true)
    {
        int cheese_cnt = 0;

        for (int row = 0; row < height; row++)
        {
            for (int col = 0; col < width; col++)
            {
                if (cheese[row][col] == 1)
                {
                    cheese_cnt += 1;
                    for (int idx = 0; idx < 4; idx++)
                    {
                        int next_row = row + dr[idx];
                        int next_col = col + dc[idx];
                        int value = cheese[next_row][next_col];

                        if (value == -1)
                        {
                            q.push({row, col});
                            break;
                        }
                    }
                }
            }
        }

        if (cheese_cnt == 0)
        {
            break;
        }

        prev_cnt = cheese_cnt;
        hour += 1;

        while (!q.empty())
        {
            pair<int, int> pos = q.front();
            q.pop();

            int row = pos.first;
            int col = pos.second;
            cheese[row][col] = -1;

            for (int idx = 0; idx < 4; idx++)
            {
                int next_row = row + dr[idx];
                int next_col = col + dc[idx];
                int value = cheese[next_row][next_col];

                if (value == 0)
                {
                    fill_air(next_row, next_col);
                }
            }
        }
    }

    return {hour, prev_cnt};
}

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    fill(&cheese[0][0], &cheese[99][100], 0);
    cin >> height >> width;

    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            cin >> cheese[row][col];
        }
    }

    fill_air(0, 0);

    pair<int, int> answer = solve();
    cout << answer.first << "\n"
         << answer.second << "\n";

    return 0;
}
