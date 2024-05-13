#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

struct Edge
{
    int node, length;
} typedef edge;

struct CompareEdge
{
    bool operator()(const edge &left, const edge &right)
    {
        return left.length > right.length;
    }
};

const int MAX = 987654321;

int N, M, R;
vector<int> item_cnt;
vector<vector<edge>> graph;

int solve(int start_node)
{
    vector<int> dist(N, MAX);

    priority_queue<edge, vector<edge>, CompareEdge> pq;
    pq.push({start_node, 0});

    while (!pq.empty())
    {
        edge top = pq.top();
        pq.pop();

        int from = top.node;
        int length = top.length;

        if (dist[from] < length)
        {
            continue;
        }

        for (edge next : graph[from])
        {
            int to = next.node;
            int to_length = length + next.length;

            if (dist[to] > to_length)
            {
                dist[to] = to_length;
                pq.push({to, to_length});
            }
        }
    }

    int ret = 0;
    for (int node = 0; node < N; node++)
    {
        if (node == start_node || dist[node] <= M)
        {
            ret += item_cnt[node];
        }
    }
    return ret;
}

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> N >> M >> R;
    item_cnt = vector<int>(N, 0);
    graph = vector<vector<edge>>(N);

    for (int idx = 0; idx < N; idx++)
    {
        cin >> item_cnt[idx];
    }

    int a, b, length;
    for (int idx = 0; idx < R; idx++)
    {
        cin >> a >> b >> length;
        a -= 1;
        b -= 1;
        graph[a].push_back({b, length});
        graph[b].push_back({a, length});
    }

    int answer = 0;
    for (int node = 0; node < N; node++)
    {
        answer = max(answer, solve(node));
    }
    printf("%d\n", answer);

    return 0;
}
