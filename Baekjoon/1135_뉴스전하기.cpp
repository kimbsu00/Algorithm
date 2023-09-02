#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int N;
vector<vector<int>> tree;
vector<bool> visited;

/**
 * root가 node인 회사에서 뉴스를 전하는데 걸리는 최소 시간
 */
int solve(int node)
{
    visited[node] = true;

    vector<int> time;
    for (int child : tree[node])
    {
        if (!visited[child])
        {
            time.push_back(solve(child));
        }
    }

    int ret = 0;
    if (!time.empty())
    {
        sort(time.begin(), time.end(), greater<int>());

        ret = time[0];
        for (int idx = 1; idx < time.size(); idx++)
        {
            int tmp = time[idx] + idx;
            if (ret < tmp)
            {
                ret = tmp;
            }
        }

        ret += 1;
    }

    return ret;
}

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> N;
    tree = vector<vector<int>>(N, vector<int>());
    visited = vector<bool>(N, false);

    int parent;
    cin >> parent;
    for (int node = 1; node < N; node++)
    {
        cin >> parent;
        tree[parent].push_back(node);
    }

    int answer = solve(0);
    cout << answer << "\n";

    return 0;
}
