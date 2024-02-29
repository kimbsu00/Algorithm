#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int N, H;
vector<vector<int>> tree;
vector<int> node_level;

int solve(int node, int depth, int delta, vector<bool> &visited)
{
    if (node_level[node] - delta <= H)
    {
        return 0;
    }

    visited[node] = true;

    int ret = depth > 1 ? 1 : 0;

    for (int child : tree[node])
    {
        if (!visited[child])
        {
            int next_delta = depth > 1 ? delta + 1 : delta;
            ret += solve(child, depth + 1, next_delta, visited);
        }
    }

    return ret;
}

int calc_level(int node, int depth, vector<bool> &visited)
{
    visited[node] = true;
    node_level[node] = depth;

    for (int child : tree[node])
    {
        if (!visited[child])
        {
            node_level[node] = max(node_level[node], calc_level(child, depth + 1, visited));
        }
    }
    return node_level[node];
}

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> N;
    tree = vector<vector<int>>(N, vector<int>());
    node_level = vector<int>(N, 0);

    int a, b;
    for (int idx = 1; idx < N; idx++)
    {
        cin >> a >> b;
        tree[a].push_back(b);
        tree[b].push_back(a);
    }
    cin >> H;

    vector<bool> visited(N, false);
    calc_level(0, 0, visited);

    if (node_level[0] <= H)
    {
        printf("0\n");
    }
    else
    {
        visited = vector<bool>(N, false);
        int answer = solve(0, 0, 0, visited);
        printf("%d\n", answer);
    }

    return 0;
}
