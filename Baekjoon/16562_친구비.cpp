#include <iostream>
#include <vector>

using namespace std;

int N, M, k;
vector<int> cost;
vector<int> parent;

int who_is_your_parent(int child)
{
    if (parent[child] == child)
    {
        return child;
    }

    return parent[child] = who_is_your_parent(parent[child]);
}

void they_are_firends(int a, int b)
{
    a = who_is_your_parent(a);
    b = who_is_your_parent(b);
    if (a != b)
    {
        if (cost[a] > cost[b])
        {
            parent[a] = b;
        }
        else
        {
            parent[b] = a;
        }
    }
}

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> N >> M >> k;

    cost = vector<int>(N + 1, 987654321);
    parent = vector<int>(N + 1, 0);

    for (int idx = 1; idx <= N; idx++)
    {
        cin >> cost[idx];
        parent[idx] = idx;
    }

    int a, b;
    for (int idx = 0; idx < M; idx++)
    {
        cin >> a >> b;
        they_are_firends(a, b);
    }

    int total_cost = 0;
    for (int idx = 1; idx <= N; idx++)
    {
        int parent = who_is_your_parent(idx);
        int tmp = who_is_your_parent(0);

        if (parent != tmp)
        {
            total_cost += cost[parent];
            they_are_firends(0, idx);
        }
    }

    if (total_cost > k)
    {
        cout << "Oh no\n";
    }
    else
    {
        cout << total_cost << "\n";
    }

    return 0;
}
