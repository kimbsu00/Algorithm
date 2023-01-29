/*
url: https://www.acmicpc.net/problem/1967
    
"리프 - 루트 - 리프" 가 최장거리인 경우 1가지
"리프 - 루트가 아닌 다른 노드 - 리프" 가 최장거리인 경우 1가지
이렇게 총 2 가지의 경우를 고려해서 해결함.
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Edge
{
public:
    int child;
    int weight;

    Edge() : child(-1), weight(-1) {}

    Edge(int p_child, int p_weight) : child(p_child), weight(p_weight) {}
};

int N;
vector<vector<Edge>> tree;
vector<int> diameter;

int solve(int node, int sum)
{
    if (tree[node].empty())
    {
        return sum;
    }

    vector<int> distance;

    for (int idx = 0; idx < tree[node].size(); idx++)
    {
        int child = tree[node][idx].child;
        int weight = tree[node][idx].weight;

        int dist = solve(child, sum + weight);
        distance.push_back(dist);
    }

    if (distance.size() > 1)
    {
        sort(distance.begin(), distance.end(), greater<int>());
        diameter.push_back(distance[0] + distance[1] - 2 * sum);
    }

    return distance[0];
}

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> N;
    tree = vector<vector<Edge>>(N, vector<Edge>());

    int parent, child, weight;
    for (int idx = 0; idx < N - 1; idx++)
    {
        cin >> parent >> child >> weight;

        tree[parent - 1].push_back(Edge(child - 1, weight));
    }

    int answer = solve(0, 0);
    for (int d : diameter)
    {
        if (answer < d)
        {
            answer = d;
        }
    }

    cout << answer << "\n";

    return 0;
}
