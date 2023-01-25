#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <algorithm>

using namespace std;

const int MAX_VALUE = 987654321;

int N;
int people[10];
bool graph[10][10];
bool is_selected[10];

bool is_connected(vector<int> cur_team, bool select_flag)
{
    bool visited[10] = {
        false,
    };

    queue<int> q;
    q.push(cur_team[0]);
    visited[cur_team[0]] = true;

    int connected_cnt = 1;

    while (!q.empty())
    {
        int node = q.front();
        q.pop();

        for (int next = 0; next < N; next++)
        {
            if (graph[node][next] && is_selected[next] == select_flag && !visited[next])
            {
                visited[next] = true;
                q.push(next);
                connected_cnt += 1;
            }
        }
    }

    return (connected_cnt == cur_team.size());
}

/*
두 지역구로 나눌 수 있는 경우에 대하여,
같은 지역구에 속한 지역들이 서로 연결되어 있다면 true, 그렇지 않다면 false 리턴
*/
bool check()
{
    vector<int> red_team, blue_team;
    for (int node = 0; node < N; node++)
    {
        if (is_selected[node])
        {
            red_team.push_back(node);
        }
        else
        {
            blue_team.push_back(node);
        }
    }

    // 두 지역구로 나눌 수 없는 경우, return false
    if (red_team.size() == 0 || blue_team.size() == 0)
    {
        return false;
    }

    // red team 및 blue team 중에서 연결되지 않은 팀이 있는 경우, return false
    if (!is_connected(red_team, true) || !is_connected(blue_team, false))
    {
        return false;
    }

    return true;
}

int calculate_diff()
{
    int red_team = 0, blue_team = 0;
    for (int node = 0; node < N; node++)
    {
        if (is_selected[node])
        {
            red_team += people[node];
        }
        else
        {
            blue_team += people[node];
        }
    }
    return abs(red_team - blue_team);
}

int solve(int node, int count)
{
    int ret = MAX_VALUE;

    if (count > 0)
    {
        if (check())
        {
            ret = min(ret, calculate_diff());
        }
    }

    for (int next = node + 1; next < N; next++)
    {
        if (!is_selected[next])
        {
            is_selected[next] = true;
            ret = min(ret, solve(next, count + 1));
            is_selected[next] = false;
        }
    }

    return ret;
}

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> N;
    fill(people, people + 10, 0);
    fill(&graph[0][0], &graph[9][10], false);
    fill(is_selected, is_selected + 10, false);

    for (int idx = 0; idx < N; idx++)
    {
        cin >> people[idx];
    }

    for (int idx = 0; idx < N; idx++)
    {
        int total_cnt;
        cin >> total_cnt;

        int region;
        for (int cnt = 0; cnt < total_cnt; cnt++)
        {
            cin >> region;
            graph[idx][region - 1] = true;
        }
    }

    int answer = solve(0, 0);
    cout << (answer == MAX_VALUE ? -1 : answer) << "\n";

    return 0;
}
