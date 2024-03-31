#include <iostream>
#include <vector>

using namespace std;

int find_parent(vector<int> &parent, int node)
{
    if (node < 0)
    {
        return -1;
    }
    else if (parent[node] == node)
    {
        return node;
    }
    else
    {
        return parent[node] = find_parent(parent, parent[node]);
    }
}

int solve(int G, vector<int> &airplane)
{
    vector<int> parent;
    for (int idx = 0; idx < G; idx++)
    {
        parent.push_back(idx);
    }

    int ret = 0;
    for (int idx = 0; idx < airplane.size(); idx++)
    {
        int root = find_parent(parent, airplane[idx]);

        if (root == -1)
        {
            break;
        }
        else
        {
            parent[root] = root - 1;
            ret += 1;
        }
    }

    return ret;
}

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int G, P;
    cin >> G >> P;

    vector<int> airplane(P);
    for (int idx = 0; idx < P; idx++)
    {
        cin >> airplane[idx];
        airplane[idx] -= 1;
    }

    int answer = solve(G, airplane);
    printf("%d\n", answer);

    return 0;
}
