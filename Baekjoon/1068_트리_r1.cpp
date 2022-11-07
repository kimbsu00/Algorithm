#include <iostream>
#include <vector>

using namespace std;

int N;
vector<int> parent;
vector<vector<int>> children;

void cut(int node)
{
    int parent_node = parent[node];

    if (parent_node != -1)
    {
        for (auto it = children[parent_node].begin(); it != children[parent_node].end(); it++)
        {
            if (*it == node)
            {
                children[parent_node].erase(it);
                break;
            }
        }
    }
}

void dfs(int node)
{
    for (int child : children[node])
    {
        dfs(child);
    }
    children[node].push_back(-1);
}

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> N;

    int root = -1;
    parent = vector<int>(N, -1);
    children = vector<vector<int>>(N, vector<int>());

    for (int node = 0; node < N; node++)
    {
        int parent_node;
        cin >> parent_node;
        parent[node] = parent_node;

        if (parent_node != -1)
        {
            children[parent_node].push_back(node);
        }
        else
        {
            root = node;
        }
    }

    int rm_node;
    cin >> rm_node;

    int leaf_count = 0;
    if (rm_node != root)
    {
        dfs(rm_node);
        cut(rm_node);
        for (int node = 0; node < N; node++)
        {
            if (children[node].empty())
            {
                leaf_count += 1;
            }
        }
    }
    cout << leaf_count << "\n";

    return 0;
}
