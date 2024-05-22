#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

const int MAX = 987654321;

struct ComparePair
{
    bool operator()(const pair<int, int> &left, const pair<int, int> &right)
    {
        return left.second > right.second;
    }
};

int N;
vector<int> well_cost;
vector<vector<int>> graph;

int prim_algorithm(int start)
{
    vector<bool> visited(N + 1, false);

    priority_queue<pair<int, int>, vector<pair<int, int>>, ComparePair> pq;
    for (int next = 0; next < N; next++)
    {
        if (start != next)
        {
            pq.push({next, graph[start][next]});
        }
    }
    visited[start] = true;

    int total_cost = 0;
    int edge_cnt = 0;
    while (!pq.empty() && edge_cnt < N)
    {
        pair<int, int> top = pq.top();
        pq.pop();

        int node = top.first;
        int cost = top.second;

        if (!visited[node])
        {
            edge_cnt += 1;
            total_cost += cost;
            visited[node] = true;

            for (int next = 0; next < N; next++)
            {
                if (next != node)
                {
                    pq.push({next, graph[node][next]});
                }
            }
        }
    }

    return total_cost;
}

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> N;
    well_cost = vector<int>(N);
    graph = vector<vector<int>>(N + 1, vector<int>(N + 1, 0));

    for (int idx = 0; idx < N; idx++)
    {
        cin >> well_cost[idx];
    }

    for (int cur_node = 0; cur_node < N; cur_node++)
    {
        for (int next_node = 0; next_node < N; next_node++)
        {
            cin >> graph[cur_node][next_node];
        }
    }

    for (int node = 0; node < N; node++)
    {
        graph[node][N] = well_cost[node];
        graph[N][node] = well_cost[node];
    }

    int answer = prim_algorithm(N);
    printf("%d\n", answer);

    return 0;
}
