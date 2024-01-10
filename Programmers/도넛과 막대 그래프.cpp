#include <string>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

enum class GraphType
{
    DOUGHNUT,
    STICK,
    EIGHT,
    UNDEFINED
};

int indegree[1000000];
int outdegree[1000000];
vector<bool> visited;
// {next_node, visited}
vector<vector<pair<int, bool>>> directed_graph;

GraphType solve(int root)
{
    int node_cnt = 0;
    int edge_cnt = 0;

    queue<int> q;
    q.push(root);

    while (!q.empty())
    {
        int cur_node = q.front();
        q.pop();

        // 처음 방문하는 노드의 개수만 계산
        if (!visited[cur_node])
        {
            visited[cur_node] = true;
            node_cnt += 1;
        }

        for (pair<int, bool> &edge : directed_graph[cur_node])
        {
            // 방문하지 않은 엣지인 경우에만 이동
            if (!edge.second)
            {
                edge.second = true;
                edge_cnt += 1;

                q.push(edge.first);
            }
        }
    }

    if (node_cnt == edge_cnt)
    {
        return GraphType::DOUGHNUT;
    }
    else if ((node_cnt - 1) == edge_cnt)
    {
        return GraphType::STICK;
    }
    else if ((node_cnt + 1) == edge_cnt)
    {
        return GraphType::EIGHT;
    }

    return GraphType::UNDEFINED;
}

vector<int> solution(vector<vector<int>> edges)
{
    fill(&indegree[0], &indegree[1000000], 0);
    fill(&outdegree[0], &outdegree[1000000], 0);
    directed_graph = vector<vector<pair<int, bool>>>(1000000, vector<pair<int, bool>>());

    int last_node = -1;
    for (vector<int> edge : edges)
    {
        int prev = edge[0] - 1;
        int next = edge[1] - 1;

        indegree[next] += 1;
        outdegree[prev] += 1;

        last_node = max(last_node, max(prev, next));

        directed_graph[prev].push_back({next, false});
    }
    visited = vector<bool>(last_node + 1, false);

    int add_node = -1;
    for (int node = 0; node <= last_node; node++)
    {
        if (indegree[node] == 0 && outdegree[node] > 1)
        {
            add_node = node;
            break;
        }
    }
    // printf("add_node=%d\n", add_node);

    vector<int> answer(4, 0);
    answer[0] = add_node + 1;

    // 새로 추가된 노드에서 나온 엣지를 지워줌
    for (pair<int, bool> edge : directed_graph[add_node])
    {
        indegree[edge.first] -= 1;
    }

    for (int node = 0; node <= last_node; node++)
    {
        // Stick Graph Node
        if (indegree[node] == 0 && node != add_node)
        {
            answer[2] += 1;

            int cur_node = node;

            while (cur_node != -1)
            {
                visited[cur_node] = true;
                // printf("cur_node=%d\n", cur_node);

                if (directed_graph[cur_node].empty())
                {
                    cur_node = -1;
                }
                else
                {
                    cur_node = directed_graph[cur_node][0].first;
                }
            }
        }
    }

    for (pair<int, bool> edge : directed_graph[add_node])
    {
        if (!visited[edge.first])
        {
            // printf("root=%d\n", edge.first);
            GraphType type = solve(edge.first);

            if (type == GraphType::DOUGHNUT)
            {
                answer[1] += 1;
            }
            else if (type == GraphType::STICK)
            {
                answer[2] += 1;
            }
            else if (type == GraphType::EIGHT)
            {
                answer[3] += 1;
            }
        }
    }

    return answer;
}

int main(void)
{
    vector<vector<int>> edge;
    edge.push_back(vector<int>({2, 3}));
    edge.push_back(vector<int>({4, 3}));
    edge.push_back(vector<int>({1, 1}));
    edge.push_back(vector<int>({2, 1}));

    vector<int> answer = solution(edge);
    for (int idx = 0; idx < answer.size(); idx++)
    {
        printf("%d ", answer[idx]);
    }
    printf("\n");

    return 0;
}
