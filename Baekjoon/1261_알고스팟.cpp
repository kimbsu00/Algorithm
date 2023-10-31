#include <iostream>
#include <queue>

using namespace std;

struct Node
{
    int row, col, break_cnt;
};

const int dr[4] = {0, -1, 0, 1};
const int dc[4] = {-1, 0, 1, 0};

int N, M;
int map[100][100];
int cache[100][100];

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

void print_cache()
{
    for (int row = 0; row < N; row++)
    {
        for (int col = 0; col < M; col++)
        {
            printf("%d ", cache[row][col]);
        }
        printf("\n");
    }
}

bool check_range(int row, int col)
{
    return 0 <= row && row < N && 0 <= col && col < M;
}

int solve()
{
    queue<Node> q;
    q.push({0, 0, 0});

    while (!q.empty())
    {
        Node node = q.front();
        q.pop();

        if (node.break_cnt >= cache[node.row][node.col])
        {
            continue;
        }

        cache[node.row][node.col] = node.break_cnt;

        for (int idx = 0; idx < 4; idx++)
        {
            int next_row = node.row + dr[idx];
            int next_col = node.col + dc[idx];

            if (check_range(next_row, next_col))
            {
                if (map[next_row][next_col] == 1)
                {
                    q.push({next_row, next_col, node.break_cnt + 1});
                }
                else if (map[next_row][next_col] == 0)
                {
                    q.push({next_row, next_col, node.break_cnt});
                }
            }
        }
    }

    return cache[N - 1][M - 1];
}

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    fill(&cache[0][0], &cache[99][100], 987654321);
    scanf("%d %d", &M, &N);

    getchar();
    for (int row = 0; row < N; row++)
    {
        for (int col = 0; col < M; col++)
        {
            map[row][col] = getchar() - '0';
        }
        getchar();
    }

    int answer = solve();
    printf("%d\n", answer);

    return 0;
}
