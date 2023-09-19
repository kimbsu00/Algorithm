#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int N, M;
vector<vector<int>> directed_graph;
vector<int> indegree;

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> N >> M;

    directed_graph = vector<vector<int>>(N, vector<int>());
    indegree = vector<int>(N, 0);

    queue<int> q;
    for (int pd = 0; pd < M; pd++)
    {
        int how_many;
        cin >> how_many;

        int nodeA, nodeB;
        cin >> nodeA;
        nodeA -= 1;

        for (int idx = 1; idx < how_many; idx++)
        {
            cin >> nodeB;
            nodeB -= 1;

            directed_graph[nodeA].push_back(nodeB);
            indegree[nodeB] += 1;
            nodeA = nodeB;
        }
    }

    for (int node = 0; node < N; node++)
    {
        if (indegree[node] == 0)
        {
            q.push(node);
        }
    }

    vector<int> answer;
    while (!q.empty())
    {
        int node = q.front();
        q.pop();
        indegree[node] = -1;

        answer.push_back(node);

        for (int next : directed_graph[node])
        {
            indegree[next] -= 1;

            if (indegree[next] == 0)
            {
                q.push(next);
            }
        }
    }

    if (answer.size() == N)
    {
        for (int ans : answer)
        {
            cout << ans + 1 << "\n";
        }
    }
    else
    {
        cout << "0\n";
    }

    return 0;
}
