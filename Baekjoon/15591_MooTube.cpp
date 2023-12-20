#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int N, Q;
vector<vector<pair<int, int>>> graph;
vector<bool> visited;

int solve(int k, int v)
{
    vector<bool> visited(N, false);
    queue<int> q;
    q.push(v);
    visited[v] = true;

    int ret = 0;
    while (!q.empty())
    {
        int node = q.front();
        q.pop();

        for (pair<int, int> p : graph[node])
        {
            int next = p.first;
            int cost = p.second;

            if (!visited[next] && cost >= k)
            {
                ret += 1;
                q.push(next);
                visited[next] = true;
            }
        }
    }

    return ret;
}

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> N >> Q;
    graph = vector<vector<pair<int, int>>>(N, vector<pair<int, int>>());

    int p, q, r;
    for (int idx = 0; idx < N - 1; idx++)
    {
        cin >> p >> q >> r;
        p -= 1;
        q -= 1;

        graph[p].push_back({q, r});
        graph[q].push_back({p, r});
    }

    vector<int> answer;
    int k, v;
    for (int idx = 0; idx < Q; idx++)
    {
        cin >> k >> v;
        v -= 1;
        answer.push_back(solve(k, v));
    }

    for (int ans : answer)
    {
        printf("%d\n", ans);
    }

    return 0;
}
