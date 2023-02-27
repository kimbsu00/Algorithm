#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct ComparePair
{
    bool operator()(pair<int, int> &left, pair<int, int> &right)
    {
        return left.second > right.second;
    }
};

int N, M;
vector<vector<pair<int, int>>> graph;

int prim_algorithm(int start)
{
    priority_queue<pair<int, int>, vector<pair<int, int>>, ComparePair> pq;
    vector<bool> visited(N, false);

    for (pair<int, int> p : graph[start])
    {
        pq.push(p);
    }
    visited[start] = true;

    int edge_cnt = 0;
    int total_cost = 0;
    int max_cost = -1;
    while (!pq.empty() && edge_cnt < N - 1)
    {
        pair<int, int> top = pq.top();
        pq.pop();

        int node = top.first;
        int cost = top.second;

        if (!visited[node])
        {
            edge_cnt += 1;
            total_cost += cost;

            if (max_cost < cost)
            {
                max_cost = cost;
            }

            visited[node] = true;
            for (pair<int, int> p : graph[node])
            {
                pq.push(p);
            }
        }
    }

    return total_cost - max_cost;
}

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> N >> M;
    graph = vector<vector<pair<int, int>>>(N, vector<pair<int, int>>());

    int A, B, C;
    for (int idx = 0; idx < M; idx++)
    {
        cin >> A >> B >> C;

        graph[A - 1].push_back({B - 1, C});
        graph[B - 1].push_back({A - 1, C});
    }

    cout << prim_algorithm(0) << "\n";

    return 0;
}
