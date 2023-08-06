#include <iostream>
#include <vector>

using namespace std;

const int INF = 7654321;

class Edge
{
public:
    int start;
    int end;
    int cost;

    Edge() : start(-1), end(-1), cost(-1) {}

    Edge(int p_start, int p_end, int p_cost) : start(p_start), end(p_end), cost(p_cost) {}
};

bool solve(int start, int N, vector<Edge> &edges)
{
    vector<int> distance(N, INF);
    distance[start] = 0;

    for (int idx = 0; idx < N - 1; idx++)
    {
        for (Edge edge : edges)
        {
            int from = edge.start;
            int to = edge.end;
            int cost = edge.cost;

            if (distance[to] > distance[from] + cost)
            {
                distance[to] = distance[from] + cost;
            }
        }
    }

    for (Edge edge : edges)
    {
        int from = edge.start;
        int to = edge.end;
        int cost = edge.cost;

        if (distance[to] > distance[from] + cost)
        {
            return true;
        }
    }

    return false;
}

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int TC, N, M, W;
    cin >> TC;

    vector<bool> answer;
    vector<Edge> edges;
    for (int tc = 0; tc < TC; tc++)
    {
        edges.clear();
        cin >> N >> M >> W;

        int S, E, T;
        for (int idx = 0; idx < M; idx++)
        {
            cin >> S >> E >> T;
            S -= 1;
            E -= 1;
            edges.push_back(Edge(S, E, T));
            edges.push_back(Edge(E, S, T));
        }

        for (int idx = 0; idx < W; idx++)
        {
            cin >> S >> E >> T;
            S -= 1;
            E -= 1;
            edges.push_back(Edge(S, E, -T));
        }

        answer.push_back(solve(0, N, edges));
    }

    for (bool ans : answer)
    {
        cout << (ans ? "YES" : "NO") << "\n";
    }

    return 0;
}
