#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int K, V, E;

void bfs(vector<vector<int>> &graph, vector<int> &group, int start)
{
    queue<int> q;
    q.push(start);

    group[start] = 1;

    while (!q.empty())
    {
        int node = q.front();
        q.pop();

        for (int next : graph[node])
        {
            if (group[next] == -1)
            {
                if (group[node] == 1)
                    group[next] = 2;
                else
                    group[next] = 1;

                q.push(next);
            }
        }
    }
}

bool solve(vector<vector<int>> &graph)
{
    vector<int> group(graph.size(), -1);

    for (int node = 0; node < graph.size(); node++)
    {
        if (group[node] == -1)
        {
            bfs(graph, group, node);
        }
    }

    bool is_bipartite = true;
    for (int node = 0; node < graph.size(); node++)
    {
        for (int adjacent : graph[node])
        {
            if (group[node] == group[adjacent])
            {
                is_bipartite = false;
                break;
            }
        }
        if (!is_bipartite)
            break;
    }

    return is_bipartite;
}

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> K;

    for (int tc = 0; tc < K; tc++)
    {
        cin >> V >> E;

        vector<vector<int>> graph(V, vector<int>());
        int u, v;
        for (int idx = 0; idx < E; idx++)
        {
            cin >> u >> v;
            graph[u - 1].push_back(v - 1);
            graph[v - 1].push_back(u - 1);
        }

        bool answer = solve(graph);
        cout << (answer ? "YES\n" : "NO\n");
    }

    return 0;
}
