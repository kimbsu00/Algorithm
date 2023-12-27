#include <iostream>
#include <vector>
#include <queue>
#include <cmath>

using namespace std;

struct Pos
{
    int x, y;
};

struct Edge
{
    int left, right;
    double cost;
    bool is_default;
};

struct CompareEdge
{
    bool operator()(Edge &left, Edge &right)
    {
        return left.cost > right.cost;
    }
};

int N, M;
vector<Pos> coord;
vector<Edge> mst;
vector<int> parent;

double calc_dist(const Pos &pos1, const Pos &pos2)
{
    return sqrt((1.0) * (pos1.x - pos2.x) * (pos1.x - pos2.x) + (1.0) * (pos1.y - pos2.y) * (pos1.y - pos2.y));
}

int find_parent(int node)
{
    if (parent[node] == node)
    {
        return node;
    }
    else
    {
        return find_parent(parent[node]);
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

void kruskal_algorithm()
{
    priority_queue<Edge, vector<Edge>, CompareEdge> pq;
    for (int node1 = 0; node1 < N; node1++)
    {
        Pos pos1 = coord[node1];
        for (int node2 = node1 + 1; node2 < N; node2++)
        {
            Pos pos2 = coord[node2];
            double cost = calc_dist(pos1, pos2);
            pq.push(Edge{node1, node2, cost, false});
        }
    }

    while (mst.size() < N - 1 && !pq.empty())
    {
        Edge edge = pq.top();
        pq.pop();

        if (find_parent(edge.left) != find_parent(edge.right))
        {
            merge_union(edge.left, edge.right);
            mst.push_back(edge);
        }
    }
}

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> N >> M;
    for (int idx = 0; idx < N; idx++)
    {
        parent.push_back(idx);
    }

    int x, y;
    for (int idx = 0; idx < N; idx++)
    {
        cin >> x >> y;
        coord.push_back(Pos{x, y});
    }

    int left_god, right_god;
    for (int idx = 0; idx < M; idx++)
    {
        cin >> left_god >> right_god;
        left_god -= 1;
        right_god -= 1;

        Pos left_pos = coord[left_god];
        Pos right_pos = coord[right_god];
        double cost = calc_dist(left_pos, right_pos);

        if (find_parent(left_god) != find_parent(right_god))
        {
            merge_union(left_god, right_god);
            mst.push_back(Edge{left_god, right_god, cost, true});
        }
    }

    kruskal_algorithm();

    double answer = 0.0;
    for (Edge edge : mst)
    {
        if (!edge.is_default)
        {
            answer += edge.cost;
        }
    }
    printf("%.2lf\n", answer);

    return 0;
}
