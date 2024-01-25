#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAX = 987654321;

int N;
vector<vector<int>> graph;
vector<int> visited;
vector<int> parent;
vector<bool> is_cycle;
vector<int> answer;

void set_cycle(int start, int node)
{
    int cur_node = node;
    while (cur_node != start)
    {
        is_cycle[cur_node] = true;
        cur_node = parent[cur_node];
    }
    is_cycle[start] = true;
}

void check_cycle(int prev, int node, int order)
{
    visited[node] = order;
    parent[node] = prev;

    for (int next : graph[node])
    {
        if (next == prev)
            continue;

        if (order > visited[next])
        {
            set_cycle(next, node);
        }
        else if (visited[next] == MAX)
        {
            check_cycle(node, next, order + 1);
        }
    }
}

int solve(int node)
{
    if (is_cycle[node])
    {
        return 0;
    }

    int ret = MAX;

    visited[node] = 1;
    for (int next : graph[node])
    {
        if (!visited[next])
        {
            ret = min(ret, 1 + solve(next));
        }
    }
    visited[node] = 0;

    return ret;
}

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> N;
    graph = vector<vector<int>>(N, vector<int>());
    visited = vector<int>(N, MAX);
    parent = vector<int>(N, -1);
    is_cycle = vector<bool>(N, false);

    int A, B;
    for (int idx = 0; idx < N; idx++)
    {
        cin >> A >> B;
        graph[A - 1].push_back(B - 1);
        graph[B - 1].push_back(A - 1);
    }

    for (int node = 0; node < N; node++)
    {
        if (visited[node] == MAX)
        {
            check_cycle(node, node, 1);
        }
    }

    answer = vector<int>(N, -1);
    for (int node = 0; node < N; node++)
    {
        visited = vector<int>(N, 0);
        answer[node] = solve(node);
    }

    for (int ans : answer)
    {
        printf("%d ", ans);
    }
    printf("\n");

    return 0;
}
