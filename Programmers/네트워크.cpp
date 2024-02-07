#include <string>
#include <vector>

using namespace std;

void solve(int node, vector<vector<int>> &graph, vector<bool> &visited)
{
    visited[node] = true;

    for (int next : graph[node])
    {
        if (!visited[next])
        {
            solve(next, graph, visited);
        }
    }
}

int solution(int n, vector<vector<int>> computers)
{
    vector<vector<int>> graph(n, vector<int>());
    for (int node_a = 0; node_a < n; node_a++)
    {
        for (int node_b = node_a + 1; node_b < n; node_b++)
        {
            if (computers[node_a][node_b])
            {
                graph[node_a].push_back(node_b);
                graph[node_b].push_back(node_a);
            }
        }
    }
    vector<bool> visited(n, false);

    int answer = 0;
    for (int node = 0; node < n; node++)
    {
        if (!visited[node])
        {
            solve(node, graph, visited);
            answer += 1;
        }
    }

    return answer;
}
