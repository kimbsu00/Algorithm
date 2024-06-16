#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAX = 987654321;

int N, K, S;
vector<vector<int>> directed_graph;

void floyd_warshall()
{
    for (int junction = 0; junction < N; junction++)
    {
        for (int start = 0; start < N; start++)
        {
            for (int end = 0; end < N; end++)
            {
                directed_graph[start][end] = min(directed_graph[start][end], directed_graph[start][junction] + directed_graph[junction][end]);
            }
        }
    }
}

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> N >> K;
    directed_graph.resize(N, vector<int>(N, MAX));

    int prev, next;
    for (int idx = 0; idx < K; idx++)
    {
        cin >> prev >> next;
        prev -= 1;
        next -= 1;
        directed_graph[prev][next] = 1;
    }

    floyd_warshall();

    cin >> S;
    vector<int> answer;
    for (int idx = 0; idx < S; idx++)
    {
        cin >> prev >> next;
        prev -= 1;
        next -= 1;

        if (directed_graph[prev][next] != MAX && directed_graph[prev][next] > 0)
        {
            answer.push_back(-1);
        }
        else if (directed_graph[next][prev] != MAX && directed_graph[next][prev] > 0)
        {
            answer.push_back(1);
        }
        else
        {
            answer.push_back(0);
        }
    }

    for (int ans : answer)
    {
        printf("%d\n", ans);
    }

    return 0;
}
