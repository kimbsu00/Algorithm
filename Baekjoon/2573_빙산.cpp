#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

// left, top, right, bottom
const int dx[4] = {-1, 0, 1, 0};
const int dy[4] = {0, -1, 0, 1};

int N, M;
int total_ice_cnt = 0;
int ice[300][300];
bool visited[300][300];

/*
모든 빙산이 연결되어 있는지 여부를 반환하는 함수

@return 하나의 그래프인 경우 1, 두 개 이상의 그래프인 경우 0, 그래프가 없는 경우 -1
*/
int is_full_connected()
{
    fill(&visited[0][0], &visited[299][300], false);

    int s_row = -1;
    int s_col = -1;
    for (int row = 0; row < N; row++)
    {
        for (int col = 0; col < M; col++)
        {
            if (ice[row][col] > 0)
            {
                s_row = row;
                s_col = col;
            }

            if (s_row != -1 && s_col != -1)
            {
                break;
            }
        }
        if (s_row != -1 && s_col != -1)
        {
            break;
        }
    }

    if (s_row != -1 && s_col != -1)
    {
        queue<pair<int, int>> q;
        q.push({s_row, s_col});
        visited[s_row][s_col] = true;
        int count = 1;

        while (!q.empty())
        {
            pair<int, int> cur_pos = q.front();
            q.pop();

            for (int idx = 0; idx < 4; idx++)
            {
                int next_row = cur_pos.first + dx[idx];
                int next_col = cur_pos.second + dy[idx];

                if (ice[next_row][next_col] > 0 && !visited[next_row][next_col])
                {
                    visited[next_row][next_col] = true;
                    q.push({next_row, next_col});
                    count += 1;
                }
            }
        }

        return (count == total_ice_cnt ? 1 : 0);
    }
    else
    {
        return -1;
    }
}

void a_year_later()
{
    vector<pair<int, int>> no_ice_pos;
    for (int row = 0; row < N; row++)
    {
        for (int col = 0; col < M; col++)
        {
            if (ice[row][col] > 0)
            {
                for (int idx = 0; idx < 4; idx++)
                {
                    int next_row = row + dx[idx];
                    int next_col = col + dy[idx];

                    // 인접한 위치가 바다인 경우
                    if (ice[next_row][next_col] == 0)
                    {
                        ice[row][col] -= 1;
                    }

                    // 이번 년도에 얼음이 다 녹은 경우
                    if (ice[row][col] == 0)
                    {
                        ice[row][col] = -1;
                        no_ice_pos.push_back({row, col});
                        break;
                    }
                }
            }
        }
    }

    total_ice_cnt -= no_ice_pos.size();
    for (auto pos : no_ice_pos)
    {
        int row = pos.first;
        int col = pos.second;
        ice[row][col] = 0;
    }
}

int solve()
{
    int connect_flag = is_full_connected();

    int year = 0;
    while (connect_flag == 1)
    {
        a_year_later();
        year += 1;

        connect_flag = is_full_connected();
    }

    if (connect_flag == -1)
    {
        year = 0;
    }

    return year;
}

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    fill(&ice[0][0], &ice[299][300], 0);
    cin >> N >> M;

    for (int row = 0; row < N; row++)
    {
        for (int col = 0; col < M; col++)
        {
            cin >> ice[row][col];

            if (ice[row][col] > 0)
            {
                total_ice_cnt += 1;
            }
        }
    }

    cout << solve() << "\n";

    return 0;
}
