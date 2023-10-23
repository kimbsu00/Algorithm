#include <iostream>
#include <queue>

using namespace std;

struct Tomato
{
    int row, col, height, time;
};

// left, front, right, back, up, down
const int dr[6] = {0, 1, 0, -1, 0, 0};
const int dc[6] = {-1, 0, 1, 0, 0, 0};
const int dh[6] = {0, 0, 0, 0, 1, -1};

int M, N, H;
int map[100][100][100];

void print_map()
{
    for (int height = 0; height < H; height++)
    {
        printf("height=%d\n", height);

        for (int row = 0; row < N; row++)
        {
            for (int col = 0; col < M; col++)
            {
                printf("%d ", map[row][col][height]);
            }
            printf("\n");
        }
        printf("\n");
    }
}

bool check_range(int row, int col, int height)
{
    return 0 <= row && row < N && 0 <= col && col < M && 0 <= height && height < H;
}

int solve(queue<Tomato> &q)
{
    int answer = 0;
    while (!q.empty())
    {
        Tomato tomato = q.front();
        q.pop();

        answer = max(answer, tomato.time);

        for (int idx = 0; idx < 6; idx++)
        {
            int next_row = tomato.row + dr[idx];
            int next_col = tomato.col + dc[idx];
            int next_height = tomato.height + dh[idx];

            if (check_range(next_row, next_col, next_height) && map[next_row][next_col][next_height] == 0)
            {
                q.push({next_row, next_col, next_height, tomato.time + 1});
                map[next_row][next_col][next_height] = 1;
            }
        }
    }

    return answer;
}

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> M >> N >> H;

    queue<Tomato> q;
    for (int height = 0; height < H; height++)
    {
        for (int row = 0; row < N; row++)
        {
            for (int col = 0; col < M; col++)
            {
                cin >> map[row][col][height];

                if (map[row][col][height] == 1)
                {
                    q.push({row, col, height, 0});
                }
            }
        }
    }

    int answer = solve(q);
    for (int height = 0; height < H; height++)
    {
        for (int row = 0; row < N; row++)
        {
            for (int col = 0; col < M; col++)
            {
                if (map[row][col][height] == 0)
                {
                    printf("-1\n");
                    return 0;
                }
            }
        }
    }
    printf("%d\n", answer);

    return 0;
}
