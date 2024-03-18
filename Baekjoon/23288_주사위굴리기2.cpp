#include <iostream>
#include <queue>

using namespace std;

enum Direction
{
    LEFT,
    TOP,
    RIGHT,
    BOTTOM
};

/**
 * 전개도는 아래와 같이 인덱싱 되어 있음
 *      0
 *  1   2   3
 *      4
 *      5
 */
int dice[6] = {2, 4, 1, 3, 5, 6};
// LEFT, TOP, RIGHT, BOTTOM
const int dr[4] = {0, -1, 0, 1};
const int dc[4] = {-1, 0, 1, 0};

int N, M, K;
int map[20][20];
int nearby_count[20][20];
bool visited[20][20];

bool check_range(int row, int col)
{
    return 0 <= row && row < N && 0 <= col && col < M;
}

void count(int row, int col)
{
    queue<pair<int, int>> q, set;
    q.push({row, col});
    visited[row][col] = true;

    int num = map[row][col];
    int cnt = 0;
    while (!q.empty())
    {
        pair<int, int> front = q.front();
        q.pop();

        set.push(front);
        cnt += 1;

        int cur_row = front.first;
        int cur_col = front.second;

        for (int idx = 0; idx < 4; idx++)
        {
            int next_row = cur_row + dr[idx];
            int next_col = cur_col + dc[idx];

            if (check_range(next_row, next_col) && map[next_row][next_col] == num && !visited[next_row][next_col])
            {
                visited[next_row][next_col] = true;
                q.push({next_row, next_col});
            }
        }
    }

    while (!set.empty())
    {
        pair<int, int> front = set.front();
        set.pop();
        nearby_count[front.first][front.second] = cnt;
    }
}

void lets_roll_the_dice(int dir)
{
    /**
     * 전개도는 아래와 같이 인덱싱 되어 있음
     *      0
     *  1   2   3
     *      4
     *      5
     */

    int origin[6] = {dice[0],
                     dice[1],
                     dice[2],
                     dice[3],
                     dice[4],
                     dice[5]};
    if (dir == LEFT)
    {
        /**
         * 0 -> 0
         * 1 -> 5
         * 2 -> 1
         * 3 -> 2
         * 4 -> 4
         * 5 -> 3
         */
        dice[0] = origin[0];
        dice[5] = origin[1];
        dice[1] = origin[2];
        dice[2] = origin[3];
        dice[4] = origin[4];
        dice[3] = origin[5];
    }
    else if (dir == TOP)
    {
        /**
         * 0 -> 5
         * 1 -> 1
         * 2 -> 0
         * 3 -> 3
         * 4 -> 2
         * 5 -> 4
         */
        dice[5] = origin[0];
        dice[1] = origin[1];
        dice[0] = origin[2];
        dice[3] = origin[3];
        dice[2] = origin[4];
        dice[4] = origin[5];
    }
    else if (dir == RIGHT)
    {
        /**
         * 0 -> 0
         * 1 -> 2
         * 2 -> 3
         * 3 -> 5
         * 4 -> 4
         * 5 -> 1
         */
        dice[0] = origin[0];
        dice[2] = origin[1];
        dice[3] = origin[2];
        dice[5] = origin[3];
        dice[4] = origin[4];
        dice[1] = origin[5];
    }
    else if (dir == BOTTOM)
    {
        /**
         * 0 -> 2
         * 1 -> 1
         * 2 -> 4
         * 3 -> 3
         * 4 -> 5
         * 5 -> 0
         */
        dice[2] = origin[0];
        dice[1] = origin[1];
        dice[4] = origin[2];
        dice[3] = origin[3];
        dice[5] = origin[4];
        dice[0] = origin[5];
    }
}

int solve()
{
    int top = 0, row = 0, col = 0;
    int dir = RIGHT;
    int ret = 0;
    for (int it = 0; it < K; it++)
    {
        while (true)
        {
            if (dir == LEFT)
            {
                if (col > 0)
                {
                    lets_roll_the_dice(LEFT);
                    col -= 1;
                    break;
                }
                else
                {
                    dir = RIGHT;
                }
            }
            else if (dir == TOP)
            {
                if (row > 0)
                {
                    lets_roll_the_dice(TOP);
                    row -= 1;
                    break;
                }
                else
                {
                    dir = BOTTOM;
                }
            }
            else if (dir == RIGHT)
            {
                if (col < M - 1)
                {
                    lets_roll_the_dice(RIGHT);
                    col += 1;
                    break;
                }
                else
                {
                    dir = LEFT;
                }
            }
            else if (dir == BOTTOM)
            {
                if (row < N - 1)
                {
                    lets_roll_the_dice(BOTTOM);
                    row += 1;
                    break;
                }
                else
                {
                    dir = TOP;
                }
            }
        }

        int B = map[row][col];
        int cnt = nearby_count[row][col];
        ret += B * cnt;

        int A = dice[5];
        if (A > B)
        {
            dir = (dir + 1) % 4;
        }
        else if (A < B)
        {
            dir -= 1;
            if (dir < 0)
            {
                dir = 3;
            }
        }
        else
        {
            // do nothing
        }
    }

    return ret;
}

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> N >> M >> K;

    for (int row = 0; row < N; row++)
    {
        for (int col = 0; col < M; col++)
        {
            cin >> map[row][col];
        }
    }

    fill(&nearby_count[0][0], &nearby_count[19][20], 0);
    fill(&visited[0][0], &visited[19][20], false);

    for (int row = 0; row < N; row++)
    {
        for (int col = 0; col < M; col++)
        {
            if (!visited[row][col])
            {
                count(row, col);
            }
        }
    }

    int answer = solve();
    printf("%d\n", answer);

    return 0;
}
