#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

// left, top, right, bottom
const int dr[4] = {0, -1, 0, 1};
const int dc[4] = {-1, 0, 1, 0};

int N, L, R;
int people[52][52];
int group[52][52];
int avg[2500];

void print_map()
{
    printf("\n");
    for (int row = 1; row <= N; row++)
    {
        for (int col = 1; col <= N; col++)
        {
            printf("%d\t", people[row][col]);
        }
        printf("\n");
    }
    printf("\n");
}

pair<int, int> dfs(int row, int col, int group_idx)
{
    group[row][col] = group_idx;

    int cur_value = people[row][col];

    pair<int, int> ret = {people[row][col], 1};
    for (int idx = 0; idx < 4; idx++)
    {
        int next_row = row + dr[idx];
        int next_col = col + dc[idx];
        int next_value = people[next_row][next_col];

        int diff = abs(cur_value - next_value);
        if (next_value != -1 && group[next_row][next_col] == -1 && L <= diff && diff <= R)
        {
            pair<int, int> tmp = dfs(next_row, next_col, group_idx);
            ret.first += tmp.first;
            ret.second += tmp.second;
        }
    }

    return ret;
}

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    fill(&people[0][0], &people[51][52], -1);
    fill(&group[0][0], &group[51][52], -1);
    fill(&avg[0], &avg[2500], -1);

    cin >> N >> L >> R;

    for (int row = 1; row <= N; row++)
    {
        for (int col = 1; col <= N; col++)
        {
            cin >> people[row][col];
        }
    }

    int NN = N * N;
    int answer = 0;
    while (true)
    {
        fill(&group[0][0], &group[51][52], -1);
        fill(&avg[0], &avg[2500], -1);

        int group_idx = 0;
        for (int row = 1; row <= N; row++)
        {
            for (int col = 1; col <= N; col++)
            {
                if (group[row][col] == -1)
                {
                    pair<int, int> result = dfs(row, col, group_idx);
                    avg[group_idx] = result.first / result.second;
                    group_idx += 1;
                }
            }
        }

        if (group_idx == NN)
        {
            break;
        }
        else
        {
            for (int row = 1; row <= N; row++)
            {
                for (int col = 1; col <= N; col++)
                {
                    int group_idx = group[row][col];
                    people[row][col] = avg[group_idx];
                }
            }
            answer += 1;
        }
    }

    cout << answer << "\n";

    return 0;
}
