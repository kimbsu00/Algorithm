#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int N;
vector<int> weight;
vector<vector<int>> tree;
vector<vector<int>> directed_graph;
vector<bool> visited;

void tree_to_directed_graph(int node)
{
    visited[node] = true;

    for (int next : tree[node])
    {
        if (!visited[next])
        {
            directed_graph[node].push_back(next);
            tree_to_directed_graph(next);
        }
    }
}

int get_sum(vector<int> &sub_set)
{
    int ret = 0;
    for (int node : sub_set)
    {
        ret += weight[node];
    }
    return ret;
}

vector<int> solve(int node, bool isSubset)
{
    vector<int> ret;

    // node가 부분 집합에 포함되는 경우
    if (isSubset)
    {
        ret.push_back(node);
        for (int next : directed_graph[node])
        {
            vector<int> tmp = solve(next, false);
            ret.insert(ret.end(), tmp.begin(), tmp.end());
        }
    }
    // node가 부분 집합에 포함되지 않는 경우
    else
    {
        for (int next : directed_graph[node])
        {
            vector<int> tmp1 = solve(next, true);
            int sum1 = get_sum(tmp1);

            vector<int> tmp2 = solve(next, false);
            int sum2 = get_sum(tmp2);

            if (sum1 > sum2)
            {
                ret.insert(ret.end(), tmp1.begin(), tmp1.end());
            }
            else
            {
                ret.insert(ret.end(), tmp2.begin(), tmp2.end());
            }
        }
    }

    return ret;
}

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> N;

    weight = vector<int>(N);
    tree = vector<vector<int>>(N, vector<int>());
    directed_graph = vector<vector<int>>(N, vector<int>());
    visited = vector<bool>(N, false);

    int w;
    for (int idx = 0; idx < N; idx++)
    {
        cin >> w;
        weight[idx] = w;
    }

    int a, b;
    for (int idx = 1; idx < N; idx++)
    {
        cin >> a >> b;
        tree[a - 1].push_back(b - 1);
        tree[b - 1].push_back(a - 1);
    }

    tree_to_directed_graph(0);

    vector<int> with_root = solve(0, true);
    int with_root_sum = get_sum(with_root);

    vector<int> without_root = solve(0, false);
    int without_root_sum = get_sum(without_root);

    if (with_root_sum > without_root_sum)
    {
        sort(with_root.begin(), with_root.end(), less<int>());

        cout << with_root_sum << "\n";
        for (int node : with_root)
        {
            cout << (node + 1) << " ";
        }
        cout << "\n";
    }
    else
    {
        sort(without_root.begin(), without_root.end(), less<int>());
        
        cout << without_root_sum << "\n";
        for (int node : without_root)
        {
            cout << (node + 1) << " ";
        }
        cout << "\n";
    }

    return 0;
}
