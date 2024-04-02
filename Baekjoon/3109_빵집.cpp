#include <iostream>
#include <vector>

using namespace std;

// RIGHT_TOP, RIGHT, RIGHT_BOTTOM
const int dr[3] = {-1, 0, 1};
const int dc[3] = {1, 1, 1};

int R, C;
vector<vector<int>> map;

bool check_range(int row, int col)
{
    return 0 <= row && row < R && 0 <= col && col < C;
}

bool solve(int row, int col, int cnt)
{
    map[row][col] = cnt;

    if (col == C - 1)
    {
        return true;
    }

    for (int idx = 0; idx < 3; idx++)
    {
        int next_row = row + dr[idx];
        int next_col = col + dc[idx];

        if (check_range(next_row, next_col) && map[next_row][next_col] == 0)
        {
            if (solve(next_row, next_col, cnt))
            {
                return true;
            }
        }
    }

    return false;
}

void print_map()
{
    for (int row = 0; row < R; row++)
    {
        for (int col = 0; col < C; col++)
        {
            if (map[row][col] == -1)
            {
                printf("x ");
            }
            else if (map[row][col] == 0)
            {
                printf("0 ");
            }
            else
            {
                printf("%c ", 'a' + map[row][col] - 1);
            }
        }
        cout << "\n";
    }
}

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> R >> C;
    map = vector<vector<int>>(R, vector<int>(C, 0));

    char ch;
    for (int row = 0; row < R; row++)
    {
        for (int col = 0; col < C; col++)
        {
            cin >> ch;

            if (ch == '.')
            {
                map[row][col] = 0;
            }
            else if (ch == 'x')
            {
                map[row][col] = -1;
            }
        }
    }

    // getchar();
    int answer = 0;
    int cnt = 1;
    for (int row = 0; row < R; row++)
    {
        if (solve(row, 0, cnt++))
        {
            answer += 1;
        }
        // print_map();
        // getchar();
    }
    printf("%d\n", answer);

    return 0;
}

/*
반례모음

- 4% 반례
15 15
.xxxxxxxxxx....
...x.......xxx.
...x.......x...
..xx.......xx..
...x........xx.
.x.x......x.x..
...x......xx...
.x.x....xxx....
.x....x.x......
.x.....xx.x....
.x..x.xx.......
.....xx........
....x..........
......x........
...............
정답: 1
 */
