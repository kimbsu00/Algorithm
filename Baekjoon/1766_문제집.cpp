#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int N, M;
vector<vector<int>> graph;
vector<int> indegree;

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> N >> M;

    graph = vector<vector<int>>(N, vector<int>());
    indegree = vector<int>(N, 0);

    int prev, next;
    for (int idx = 0; idx < M; idx++)
    {
        cin >> prev >> next;
        prev -= 1;
        next -= 1;

        graph[prev].push_back(next);
        indegree[next] += 1;
    }

    priority_queue<int> pq;
    for (int node = 0; node < N; node++)
    {
        if (indegree[node] == 0)
        {
            pq.push(-node);
        }
    }

    while (!pq.empty())
    {
        int node = -pq.top();
        pq.pop();

        for (int next : graph[node])
        {
            indegree[next] -= 1;

            if (indegree[next] == 0)
            {
                pq.push(-next);
            }
        }

        cout << (node + 1) << " ";
    }
    cout << "\n";

    return 0;
}
