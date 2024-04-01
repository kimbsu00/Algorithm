#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <string>

using namespace std;

struct Edge
{
    int from, to, cost;

    string to_string()
    {
        return "from=" + std::to_string(from + 1) + ", to=" + std::to_string(to + 1) + ", cost=" + std::to_string(cost);
    }
} typedef edge;

struct CompareEdge
{
    bool operator()(const Edge &left, const Edge &right)
    {
        if (left.to == right.to)
        {
            return left.from > right.from;
        }
        else
        {
            return left.to > right.to;
        }
    }
};

int N, M, C;
/**
 * [idx, idx+1] 범위에서 트럭이 수용할 수 있는 박스의 개수
 */
vector<int> range_capacity;

/**
 * [start, end] 범위에서 트럭이 수용할 수 있는 박스의 개수를 반환
 */
int get_range_capacity(int start, int end)
{
    int ret = C;
    for (int idx = start; idx < end; idx++)
    {
        ret = min(ret, range_capacity[idx]);
    }

    return ret;
}

void update_range_capacity(int start, int end, int delta)
{
    for (int idx = start; idx < end; idx++)
    {
        range_capacity[idx] += delta;
    }
}

int solve(priority_queue<Edge, vector<Edge>, CompareEdge> &pq)
{
    int ret = 0;

    while (!pq.empty())
    {
        Edge top = pq.top();
        pq.pop();

        int capacity = get_range_capacity(top.from, top.to);
        if (top.cost <= capacity)
        {
            ret += top.cost;
            update_range_capacity(top.from, top.to, -top.cost);
        }
        else if (capacity > 0)
        {
            ret += capacity;
            update_range_capacity(top.from, top.to, -capacity);
        }
    }

    return ret;
}

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> N >> C >> M;
    range_capacity = vector<int>(N - 1, C);

    int from, to, cost;
    priority_queue<Edge, vector<Edge>, CompareEdge> input;
    for (int idx = 0; idx < M; idx++)
    {
        cin >> from >> to >> cost;

        from -= 1;
        to -= 1;
        input.push({from, to, cost});
    }

    int answer = solve(input);
    printf("%d\n", answer);

    return 0;
}
