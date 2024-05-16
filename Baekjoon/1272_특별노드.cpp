#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAX = 987654321;

int N, root_idx;
vector<int> weight;
vector<vector<int>> tree;
vector<bool> visited;
int cache[1004][1004][2];

int solve(int node, int special_node, int is_special)
{
    int &ret = cache[node][special_node][is_special];
    if (ret != -1)
    {
        return ret;
    }

    visited[node] = true;
    int sum;
    if (is_special)
    {
        sum = weight[node];
    }
    else
    {
        sum = weight[node] - weight[special_node];
    }

    for (int next : tree[node])
    {
        if (!visited[next])
        {
            if (is_special)
            {
                sum += min(solve(next, node, 0), solve(next, node, 1));
            }
            else
            {
                sum += min(solve(next, special_node, 0), solve(next, special_node, 1));
            }
        }
    }
    visited[node] = false;
    return ret = sum;
}

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    fill(&cache[0][0][0], &cache[1003][1003][2], -1);

    cin >> N >> root_idx;
    root_idx -= 1;

    weight = vector<int>(N);
    tree = vector<vector<int>>(N, vector<int>());
    visited = vector<bool>(N, false);

    for (int idx = 0; idx < N; idx++)
    {
        cin >> weight[idx];
    }

    int left, right;
    for (int idx = 1; idx < N; idx++)
    {
        cin >> left >> right;
        left -= 1;
        right -= 1;

        tree[left].push_back(right);
        tree[right].push_back(left);
    }

    int answer = solve(root_idx, root_idx, 1);
    printf("%d\n", answer);

    return 0;
}
