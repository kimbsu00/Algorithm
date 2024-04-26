#include <iostream>
#include <vector>
#include <string>
#include <queue>

using namespace std;

const int MAX = 987654321;

int N;
vector<vector<pair<int, int>>> graph;

struct ComparePair
{
    bool operator()(pair<int, int> &left, pair<int, int> &right)
    {
        return left.second > right.second;
    }
};

int prim_algorithm()
{
    priority_queue<pair<int, int>, vector<pair<int, int>>, ComparePair> pq;
    vector<bool> visited(N, false);

    for (pair<int, int> p : graph[0])
    {
        pq.push(p);
    }
    visited[0] = true;

    int edge_cnt = 0;
    int total_cost = 0;
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

            visited[node] = true;
            for (pair<int, int> p : graph[node])
            {
                pq.push(p);
            }
        }
    }

    return (edge_cnt == N - 1) ? total_cost : -1;
}

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> N;
    graph = vector<vector<pair<int, int>>>(N, vector<pair<int, int>>());

    int weight_sum = 0;
    string input;
    for (int from = 0; from < N; from++)
    {
        cin >> input;

        for (int to = 0; to < input.size(); to++)
        {
            char ch = input[to];

            // 1~26
            if ('a' <= ch && ch <= 'z')
            {
                int weight = ch - 'a' + 1;
                graph[from].push_back({to, weight});
                graph[to].push_back({from, weight});
                weight_sum += weight;
            }
            // 27~52
            else if ('A' <= ch && ch <= 'Z')
            {
                int weight = ch - 'A' + 27;
                graph[from].push_back({to, weight});
                graph[to].push_back({from, weight});
                weight_sum += weight;
            }
        }
    }

    int answer = prim_algorithm();
    if (answer != -1)
    {
        printf("%d\n", weight_sum - answer);
    }
    else
    {
        printf("-1\n");
    }

    return 0;
}
