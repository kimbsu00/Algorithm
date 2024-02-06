#include <iostream>
#include <queue>
#include <algorithm>

using namespace std;

const int MAX = 987654321;
const int dr[12] = {0, -1, 0, 1, -1, -2, -2, -1, 1, 2, 2, 1};
const int dc[12] = {-1, 0, 1, 0, -2, -1, 1, 2, 2, 1, -1, -2};
int K, W, H;
int map[200][200];
int visited[200][200][31];

struct Node
{
    int row, col, cnt, move;
};

bool check_range(int row, int col)
{
    return (0 <= row) && (row < H) && (0 <= col) && (col < W);
}

int solve()
{
    queue<Node> q;
    q.push({0, 0, K, 0});

    int answer = -1;
    while (!q.empty())
    {
        Node node = q.front();
        q.pop();

        if (node.row == H - 1 && node.col == W - 1)
        {
            answer = node.move;
            break;
        }

        int max_idx = -1;
        if (node.cnt > 0)
        {
            max_idx = 12;
        }
        else
        {
            max_idx = 4;
        }

        for (int idx = 0; idx < max_idx; idx++)
        {
            int next_row = node.row + dr[idx];
            int next_col = node.col + dc[idx];

            if (check_range(next_row, next_col) && map[next_row][next_col] == 0)
            {
                if (idx < 4 && visited[next_row][next_col][node.cnt] == 0)
                {
                    visited[next_row][next_col][node.cnt] = 1;
                    q.push({next_row, next_col, node.cnt, node.move + 1});
                }
                else if (idx >= 4 && visited[next_row][next_col][node.cnt - 1] == 0)
                {
                    visited[next_row][next_col][node.cnt - 1] = 1;
                    q.push({next_row, next_col, node.cnt - 1, node.move + 1});
                }
            }
        }
    }

    return answer;
}

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    fill(&visited[0][0][0], &visited[199][199][31], 0);
    cin >> K >> W >> H;

    for (int row = 0; row < H; row++)
    {
        for (int col = 0; col < W; col++)
        {
            cin >> map[row][col];
        }
    }

    int answer = solve();
    printf("%d\n", answer);

    return 0;
}
