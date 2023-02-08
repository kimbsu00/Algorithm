#include <iostream>
#include <queue>
#include <string>
#include <algorithm>

using namespace std;

class Pos
{
public:
    int row;
    int col;
    int time;

    Pos() : row(-1), col(-1), time(0) {}

    Pos(int p_row, int p_col) : row(p_row), col(p_col), time(0) {}

    Pos(int p_row, int p_col, int p_time) : row(p_row), col(p_col), time(p_time) {}
};

// left, top, right, bottom
const int dr[4] = {0, -1, 0, 1};
const int dc[4] = {-1, 0, 1, 0};

int R, C;
int map[102][102];
int dist[3][102][102];
Pos villains[3];

void solve()
{
    for (int idx = 0; idx < 3; idx++)
    {
        Pos villain = villains[idx];

        for (int row = 0; row < R + 2; row++)
        {
            for (int col = 0; col < C + 2; col++)
            {
                dist[idx][row][col] = map[row][col];
            }
        }

        queue<Pos> q;
        q.push(villain);

        while (!q.empty())
        {
            Pos pos = q.front();
            q.pop();

            for (int dir = 0; dir < 4; dir++)
            {
                int next_row = pos.row + dr[dir];
                int next_col = pos.col + dc[dir];

                if (dist[idx][next_row][next_col] == 0)
                {
                    q.push(Pos(next_row, next_col, pos.time + 1));
                    dist[idx][next_row][next_col] = pos.time + 1;
                }
            }
        }

        for (int row = 1; row < R + 1; row++)
        {
            for (int col = 1; col < C + 1; col++)
            {
                if (dist[idx][row][col] == 0)
                {
                    dist[idx][row][col] = -1;
                }
            }
        }
        
        dist[idx][villain.row][villain.col] = 0;
    }

    int min_time = 987654321;
    int cnt = 1;
    for (int row = 1; row < R + 1; row++)
    {
        for (int col = 1; col < C + 1; col++)
        {
            if (dist[0][row][col] >= 0 && dist[1][row][col] >= 0 && dist[2][row][col] >= 0)
            {
                int max_time = max(dist[0][row][col], max(dist[1][row][col], dist[2][row][col]));

                if (min_time > max_time)
                {
                    min_time = max_time;
                    cnt = 1;
                }
                else if (min_time == max_time)
                {
                    cnt += 1;
                }
            }
        }
    }

    if (min_time == 987654321)
    {
        cout << -1 << "\n";
    }
    else
    {
        cout << min_time << "\n"
             << cnt << "\n";
    }
}

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> R >> C;
    fill(&map[0][0], &map[101][102], 1);

    string input;
    for (int row = 1; row < R + 1; row++)
    {
        cin >> input;
        for (int col = 1; col < C + 1; col++)
        {
            map[row][col] = (input[col - 1] - '0');

            if (map[row][col] == 1)
            {
                map[row][col] = -1;
            }
        }
    }

    int r1, c1, r2, c2, r3, c3;
    cin >> r1 >> c1 >> r2 >> c2 >> r3 >> c3;
    villains[0] = Pos(r1, c1);
    villains[1] = Pos(r2, c2);
    villains[2] = Pos(r3, c3);

    solve();

    return 0;
}
