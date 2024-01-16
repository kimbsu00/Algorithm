#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int N;
vector<vector<int>> graph;
vector<int> build_time;
vector<int> total_build_time;

int solve(int node)
{
    if (total_build_time[node] != -1)
    {
        return total_build_time[node];
    }

    int ret = build_time[node];

    int tmp = 0;
    for (int next : graph[node])
    {
        tmp = max(tmp, solve(next));
    }

    return total_build_time[node] = ret + tmp;
}

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> N;

    graph = vector<vector<int>>(N, vector<int>());
    build_time = vector<int>(N, 0);
    total_build_time = vector<int>(N, -1);

    int cost;
    int node = 0;
    for (int idx = 0; idx < N; idx++)
    {
        cin >> cost;
        build_time[idx] = cost;

        while (true)
        {
            cin >> node;
            node -= 1;

            if (node < 0)
            {
                break;
            }
            else
            {
                graph[idx].push_back(node);
            }
        }
    }

    for (int node = 0; node < N; node++)
    {
        if (total_build_time[node] == -1)
        {
            total_build_time[node] = solve(node);
        }
    }

    for (int answer : total_build_time)
    {
        printf("%d\n", answer);
    }

    return 0;
}
