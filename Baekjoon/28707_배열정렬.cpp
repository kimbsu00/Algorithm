#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <algorithm>

using namespace std;

struct Node
{
    int cost;
    vector<int> list;
} typedef node;

struct CompareNode
{
    bool operator()(const node &left, const node &right)
    {
        return left.cost > right.cost;
    }
} typedef compare_node;

struct Edge
{
    int from, to, cost;
} typedef edge;

int N, M;
vector<edge> edges;

void print_node(node &n)
{
    printf("cost=%d\n", n.cost);
    printf("list=[");
    for (int idx = 0; idx < n.list.size(); idx++)
    {
        int num = n.list[idx];
        if (idx != n.list.size() - 1)
        {
            printf("%d, ", num);
        }
        else
        {
            printf("%d", num);
        }
    }
    printf("]\n\n");
}

template <typename T>
void swap(const T &left, const T &right)
{
    T tmp = left;
    left = right;
    right = tmp;
}

int solve(vector<int> &init_list)
{
    node init_state = {0, init_list};
    priority_queue<node, vector<node>, compare_node> pq;
    pq.push(init_state);

    map<vector<int>, int> dist;

    while (!pq.empty())
    {
        node top = pq.top();
        pq.pop();

        // print_node(top);

        if (dist[top.list] >= top.cost)
        {
            for (edge eg : edges)
            {
                int from = eg.from;
                int to = eg.to;
                int cost = eg.cost;

                vector<int> next_vec(top.list.begin(), top.list.end());
                swap(next_vec[from], next_vec[to]);
                int next_cost = top.cost + cost;

                if ((dist.count(next_vec) == 0) || dist[next_vec] > next_cost)
                {
                    dist[next_vec] = next_cost;
                    pq.push({next_cost, next_vec});
                }
            }
        }
    }

    sort(init_list.begin(), init_list.end(), less<int>());
    if (dist.count(init_list) > 0)
    {
        return dist[init_list];
    }
    else
    {
        return -1;
    }
}

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> N;

    vector<int> input(N);
    for (int idx = 0; idx < N; idx++)
    {
        cin >> input[idx];
    }

    cin >> M;
    int left, right, cost;
    for (int idx = 0; idx < M; idx++)
    {
        cin >> left >> right >> cost;
        left -= 1;
        right -= 1;

        edges.push_back({left, right, cost});
    }

    int answer = solve(input);
    printf("%d\n", answer);

    return 0;
}
