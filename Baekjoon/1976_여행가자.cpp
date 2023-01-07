#include <iostream>
#include <string>

using namespace std;

int N, M;
int **graph;
int *plan;
bool *visited;

void traversal(int cur_city)
{
    visited[cur_city] = true;
    plan[cur_city] = 0;

    for (int next = 0; next < N; next++)
    {
        int can_go = graph[cur_city][next];

        if (can_go && !visited[next])
            traversal(next);
    }
}

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> N >> M;

    graph = new int *[N];
    for (int idx = 0; idx < N; idx++)
    {
        graph[idx] = new int[N];
    }

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            cin >> graph[i][j];
        }
    }

    int start = -1;
    plan = new int[N];
    fill(plan, plan + N, 0);

    int input;
    for (int idx = 0; idx < M; idx++)
    {
        cin >> input;
        input -= 1;

        if (start == -1)
            start = input;

        plan[input] = 1;
    }

    visited = new bool[N];
    fill(visited, visited + N, false);

    traversal(start);
    int sum = 0;
    for (int idx = 0; idx < N; idx++)
    {
        sum += plan[idx];
    }

    cout << (sum == 0 ? "YES\n" : "NO\n");

    return 0;
}
