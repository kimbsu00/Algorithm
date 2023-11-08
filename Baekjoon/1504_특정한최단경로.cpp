#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const int MAX = 1500000000;

int N, E;
vector<vector<pair<int, int>>> graph;

vector<int> dijkstra(int start)
{
    priority_queue<pair<int, int>> pq;
    pq.push({0, start});

    vector<int> dist = vector<int>(N, MAX);
    while (!pq.empty())
    {
        pair<int, int> top = pq.top();
        pq.pop();

        int cost = -top.first;
        int here = top.second;
        if (dist[here] < cost)
        {
            continue;
        }

        for (int idx = 0; idx < graph[here].size(); idx++)
        {
            pair<int, int> p = graph[here][idx];
            int there_cost = cost + p.first;
            int there = p.second;

            if (dist[there] > there_cost)
            {
                dist[there] = there_cost;
                pq.push({-there_cost, there});
            }
        }
    }
    return dist;
}

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> N >> E;
    graph = vector<vector<pair<int, int>>>(N, vector<pair<int, int>>());

    int a, b, c;
    for (int idx = 0; idx < E; idx++)
    {
        cin >> a >> b >> c;

        graph[a - 1].push_back({c, b - 1});
        graph[b - 1].push_back({c, a - 1});
    }

    int v1, v2;
    cin >> v1 >> v2;
    v1 -= 1;
    v2 -= 1;

    vector<int> dist_from_v1 = dijkstra(v1);
    vector<int> dist_from_v2 = dijkstra(v2);

    if ((dist_from_v1[0] == MAX || dist_from_v1[v2] == MAX || dist_from_v2[N - 1] == MAX) &&
        (dist_from_v2[0] == MAX || dist_from_v2[v1] == MAX || dist_from_v1[N - 1] == MAX))
    {
        cout << "-1\n";
    }
    else
    {
        int dist;
        if (v1 == 0 && v2 == N - 1)
        {
            dist = min(dist_from_v1[N - 1], dist_from_v2[0]);
        }
        else
        {
            dist = min(dist_from_v1[0] + dist_from_v1[v2] + dist_from_v2[N - 1],  // 1 - v1 - v2 - N
                       dist_from_v2[0] + dist_from_v2[v1] + dist_from_v1[N - 1]); // 1 - v2 - v1 - N
        }
        cout << dist << "\n";
    }

    return 0;
}
