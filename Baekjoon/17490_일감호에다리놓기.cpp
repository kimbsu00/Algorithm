#include <iostream>
#include <vector>
#include <queue>

using namespace std;

long long N, M, K;

long long solve(int node, vector<int> &rocks, vector<bool> &visited, vector<vector<int>> &graph)
{
    queue<int> q;
    q.push(node);

    long long ret = 987654321;
    while (!q.empty())
    {
        int cur_node = q.front();
        q.pop();

        if (ret > rocks[cur_node])
        {
            ret = rocks[cur_node];
        }
        visited[cur_node] = true;

        for (int next : graph[cur_node])
        {
            if (!visited[next])
            {
                q.push(next);
            }
        }
    }

    return ret;
}

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> N >> M >> K;

    vector<int> rocks(N, -1);
    for (int idx = 0; idx < N; idx++)
    {
        cin >> rocks[idx];
    }

    vector<vector<int>> graph(N, vector<int>());
    for (int node = 0; node < N; node++)
    {
        int left = node - 1;
        if (left < 0)
        {
            left = N - 1;
        }
        int right = (node + 1) % N;
        graph[node].push_back(left);
        graph[node].push_back(right);
    }

    int node_a, node_b;
    for (int idx = 0; idx < M; idx++)
    {
        cin >> node_a >> node_b;

        node_a -= 1;
        node_b -= 1;

        // about node_a
        if (graph[node_a][0] == node_b)
        {
            graph[node_a].erase(graph[node_a].begin());
        }
        else if (graph[node_a][1] == node_b)
        {
            graph[node_a].erase(graph[node_a].begin() + 1);
        }

        // about node_b
        if (graph[node_b][0] == node_a)
        {
            graph[node_b].erase(graph[node_b].begin());
        }
        else if (graph[node_b][1] == node_a)
        {
            graph[node_b].erase(graph[node_b].begin() + 1);
        }
    }

    long long answer = 0;
    // 공사 지점이 1개라면, 돌 다리를 만들 필요가 없음
    if (M > 1)
    {
        vector<bool> visited(N, false);
        for (int node = 0; node < N; node++)
        {
            if (!visited[node])
            {
                answer += solve(node, rocks, visited, graph);
            }
        }
    }

    if (answer <= K)
    {
        printf("YES\n");
    }
    else
    {
        printf("NO\n");
    }

    return 0;
}
