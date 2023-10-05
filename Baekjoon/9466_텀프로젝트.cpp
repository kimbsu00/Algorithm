#include <iostream>
#include <vector>

using namespace std;

int T, n;
int visited[100000];
bool finished[100000];

int count_cycle_node_cnt(vector<int> &graph, int start, int node)
{
    if (start == node)
    {
        return 1;
    }

    return 1 + count_cycle_node_cnt(graph, start, graph[node]);
}

int solve(vector<int> &graph, int node)
{
    visited[node] = true;

    int ret = 0;
    int next_node = graph[node];
    if (!visited[next_node])
    {
        ret = solve(graph, next_node);
    }
    else if (!finished[next_node])
    {
        ret = count_cycle_node_cnt(graph, node, graph[node]);
    }

    finished[node] = true;
    return ret;
}

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> T;

    vector<int> answer(T, 0);
    for (int tc = 0; tc < T; tc++)
    {
        fill(&visited[0], &visited[100000], false);
        fill(&finished[0], &finished[100000], false);

        cin >> n;

        vector<int> graph(n, -1);

        for (int idx = 0; idx < n; idx++)
        {
            cin >> graph[idx];
            graph[idx] -= 1;
        }

        int node_in_group = 0;
        for (int node = 0; node < n; node++)
        {
            if (!visited[node])
            {
                node_in_group += solve(graph, node);
            }
        }

        answer[tc] = n - node_in_group;
    }

    for (int ans : answer)
    {
        cout << ans << "\n";
    }

    return 0;
}
