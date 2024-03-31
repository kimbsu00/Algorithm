#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const int MAX = 987654321;

int dijkstra(vector<vector<pair<int, int>>> &graph, int start)
{
    priority_queue<pair<int, int>> pq;
    pq.push({0, start});

    vector<int> dist(graph.size(), MAX);
    while (!pq.empty())
    {
        pair<int, int> top = pq.top();
        pq.pop();

        int cost = -top.first;
        int from = top.second;
        if (cost > dist[from])
        {
            continue;
        }

        for (pair<int, int> next : graph[from])
        {
            int to_cost = next.second + cost;
            int to = next.first;

            if (to_cost < dist[to])
            {
                dist[to] = to_cost;
                pq.push({-to_cost, to});
            }
        }
    }

    return dist.back();
}

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int N, M;
    cin >> N >> M;

    vector<vector<pair<int, int>>> graph(N, vector<pair<int, int>>());
    int A, B, C;
    for (int idx = 0; idx < M; idx++)
    {
        cin >> A >> B >> C;

        graph[A - 1].push_back({B - 1, C});
        graph[B - 1].push_back({A - 1, C});
    }

    int answer = dijkstra(graph, 0);
    printf("%d\n", answer);

    return 0;
}
