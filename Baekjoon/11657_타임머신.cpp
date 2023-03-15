#include <iostream>
#include <vector>

using namespace std;

struct Edge
{
    int start, end;
    long long cost;

    Edge(int p_start, int p_end, long long p_cost) : start(p_start), end(p_end), cost(p_cost) {}
};

const long long INF = 9876543210;

int N, M;
vector<Edge> edges;

vector<long long> bellman_ford()
{
    vector<long long> ret(N, INF);
    ret[0] = 0;

    int iter_cnt = N - 1;
    while (iter_cnt--)
    {
        for (int idx = 0; idx < edges.size(); idx++)
        {
            Edge &edge = edges[idx];

            int start = edge.start;
            int end = edge.end;
            long long cost = edge.cost;

            long long distance = ret[start] + cost;
            if (ret[start] != INF && ret[end] > distance)
            {
                ret[end] = distance;
            }
        }
    }

    // cycle check
    for (int idx = 0; idx < edges.size(); idx++)
    {
        Edge &edge = edges[idx];

        int start = edge.start;
        int end = edge.end;
        long long cost = edge.cost;

        long long distance = ret[start] + cost;
        if (ret[start] != INF && ret[end] > distance)
        {
            ret.clear();
            break;
        }
    }

    return ret;
}

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> N >> M;

    int A, B, C;
    for (int idx = 0; idx < M; idx++)
    {
        cin >> A >> B >> C;
        edges.push_back(Edge(A - 1, B - 1, C));
    }

    vector<long long> answer = bellman_ford();
    if (answer.empty())
    {
        cout << "-1\n";
    }
    else
    {
        for (int idx = 1; idx < answer.size(); idx++)
        {
            cout << ((answer[idx] == INF) ? -1 : answer[idx]) << "\n";
        }
    }

    return 0;
}
