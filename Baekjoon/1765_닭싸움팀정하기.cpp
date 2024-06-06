#include <iostream>
#include <vector>

using namespace std;

int N, M;
vector<vector<int>> firends;
vector<vector<int>> enemy;
vector<int> parent;

int find_parent(int node)
{
    if (parent[node] == node)
    {
        return node;
    }
    else
    {
        return parent[node] = find_parent(parent[node]);
    }
}

void merge_union(int node1, int node2)
{
    int parent1 = find_parent(node1);
    int parent2 = find_parent(node2);

    if (parent1 < parent2)
    {
        parent[parent2] = parent1;
    }
    else if (parent1 > parent2)
    {
        parent[parent1] = parent2;
    }
}

void dfs(int node, vector<bool> &visited)
{
    visited[node] = true;
    int cur_parent = find_parent(node);

    for (int next : firends[node])
    {
        if (!visited[next])
        {
            parent[next] = cur_parent;
            dfs(next, visited);
        }
    }
}

void solve()
{
    for (int node = 0; node < N; node++)
    {
        for (int idx = 0; idx < enemy[node].size(); idx++)
        {
            int enemy1 = enemy[node][idx];
            for (int idx2 = 0; idx2 < enemy[node].size(); idx2++)
            {
                int enemy2 = enemy[node][idx2];
                merge_union(enemy1, enemy2);
            }
        }
    }
}

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> N >> M;
    firends = vector<vector<int>>(N);
    enemy = vector<vector<int>>(N);

    for (int node = 0; node < N; node++)
    {
        parent.push_back(node);
    }

    char type;
    int p, q;
    for (int idx = 0; idx < M; idx++)
    {
        cin >> type >> p >> q;
        p -= 1;
        q -= 1;

        if (type == 'F')
        {
            firends[p].push_back(q);
            firends[q].push_back(p);
        }
        else if (type == 'E')
        {
            enemy[p].push_back(q);
            enemy[q].push_back(p);
        }
    }

    vector<bool> visited(N, false);
    for (int node = 0; node < N; node++)
    {
        if (!visited[node])
        {
            dfs(node, visited);
        }
    }
    solve();

    int answer = 0;
    vector<bool> is_counted(N, false);
    for (int node = 0; node < N; node++)
    {
        int root = find_parent(node);
        if (!is_counted[root])
        {
            is_counted[root] = true;
            answer += 1;
        }
    }
    printf("%d\n", answer);

    return 0;
}
