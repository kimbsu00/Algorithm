#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Radius
{
    int size, end_point;
} typedef radius;

struct Diameter
{
    int size, start_point, end_point;
} typedef diameter;

int N;
vector<int> fruits;
vector<vector<int>> tree;
vector<diameter> global_diameter;

bool compare_radius(const radius &left, const radius &right)
{
    if (left.size == right.size)
    {
        return left.end_point < right.end_point;
    }
    else
    {
        return left.size > right.size;
    }
}

bool compare_diameter(const diameter &left, const diameter &right)
{
    return left.size > right.size;
}

radius solve(int node, int dist, vector<bool> &visited)
{
    visited[node] = true;

    vector<radius> local_radius;
    for (int next : tree[node])
    {
        if (!visited[next])
        {
            radius tmp = solve(next, dist + fruits[node], visited);
            local_radius.push_back(tmp);
        }
    }

    radius ret = {dist + fruits[node], node};
    if (!local_radius.empty())
    {
        sort(local_radius.begin(), local_radius.end(), compare_radius);
        if (compare_radius(local_radius.front(), ret))
        {
            ret = local_radius.front();
        }

        if (local_radius.size() > 1)
        {
            radius left = local_radius[0];
            radius right = local_radius[1];
            int local_diameter = left.size + right.size - 2 * dist - fruits[node];
            global_diameter.push_back({local_diameter, left.end_point, right.end_point});
        }
    }

    return ret;
}

radius solve2(int node, int dist, vector<bool> &visited)
{
    visited[node] = true;

    radius ret = {dist + fruits[node], node};
    for (int next : tree[node])
    {
        if (!visited[next])
        {
            radius tmp = solve2(next, dist + fruits[node], visited);
            if (compare_radius(tmp, ret))
            {
                ret = tmp;
            }
        }
    }
    visited[node] = false;

    return ret;
}

/**
 * memory   3968KB
 * runtime  4ms
 */
void solution1()
{
    vector<bool> visited(N, false);
    radius ret = solve(0, 0, visited);

    diameter max_diameter = {ret.size, 0, ret.end_point};
    for (diameter d : global_diameter)
    {
        if (max_diameter.size < d.size)
        {
            max_diameter = d;
        }
        else if (max_diameter.size == d.size)
        {
            int max_diameter_node = max_diameter.start_point > max_diameter.end_point ? max_diameter.end_point : max_diameter.start_point;
            int cur_diameter_node = d.start_point > d.end_point ? d.end_point : d.start_point;
            if (max_diameter_node > cur_diameter_node)
            {
                max_diameter = d;
            }
        }
    }

    if (max_diameter.start_point > max_diameter.end_point)
    {
        printf("%d %d\n", max_diameter.size, max_diameter.end_point + 1);
    }
    else
    {
        printf("%d %d\n", max_diameter.size, max_diameter.start_point + 1);
    }
}

/**
 * memory   3500KB
 * runtime  4ms
 */
void solution2()
{
    vector<bool> visited(N, false);
    radius first = solve2(0, 0, visited);
    radius second = solve2(first.end_point, 0, visited);
    if (first.end_point > second.end_point)
    {
        printf("%d %d\n", second.size, second.end_point + 1);
    }
    else
    {
        printf("%d %d\n", second.size, first.end_point + 1);
    }
}

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> N;
    fruits = vector<int>(N, 0);
    tree = vector<vector<int>>(N, vector<int>());

    for (int idx = 0; idx < N; idx++)
    {
        cin >> fruits[idx];
    }

    int node_a, node_b;
    for (int idx = 1; idx < N; idx++)
    {
        cin >> node_a >> node_b;
        node_a -= 1;
        node_b -= 1;
        tree[node_a].push_back(node_b);
        tree[node_b].push_back(node_a);
    }

    solution1();
    // solution2();

    return 0;
}

/*
반례 모음

10
1 1 1 1 1 1 1 1 1 1000
1 2
2 3
3 4
4 5
1 6
6 7
7 8
8 9
1 10
answer: 1005 5


6
1 2 1000 3 1000 4
1 2
2 3
2 4
4 5
4 6
answer: 2005 3


6
1 1 1 1 1 1
1 2
2 3
2 4
3 5
5 6
answer: 5 1


7
1 1 1 100 1 1 1
1 2
2 3
2 4
2 5
3 6
6 7
answer: 104 4
*/
