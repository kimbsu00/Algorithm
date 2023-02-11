#include <iostream>
#include <algorithm>

using namespace std;

const int INF = 987654321;

int n, m;
int dist[100][100];

void floyd_warshall()
{
    for (int city = 0; city < n; city++)
    {
        for (int start = 0; start < n; start++)
        {
            for (int end = 0; end < n; end++)
            {
                dist[start][end] = min(dist[start][end], dist[start][city] + dist[city][end]);
            }
        }
    }
}

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> m;

    fill(&dist[0][0], &dist[99][100], INF);
    int start, end, cost;
    for (int idx = 0; idx < m; idx++)
    {
        cin >> start >> end >> cost;
        dist[start - 1][end - 1] = min(dist[start - 1][end - 1], cost);
    }

    for (int city = 0; city < n; city++)
    {
        dist[city][city] = 0;
    }

    floyd_warshall();

    for (int start = 0; start < n; start++)
    {
        for (int end = 0; end < n; end++)
        {
            if (dist[start][end] == INF)
            {
                cout << 0 << " ";
            }
            else
            {
                cout << dist[start][end] << " ";
            }
        }
        cout << "\n";
    }

    return 0;
}
