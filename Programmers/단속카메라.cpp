#include <string>
#include <vector>
#include <queue>

using namespace std;

struct Transaction
{
    int in, out;
} typedef transaction;

struct CompareTransaction
{
    // out을 기준으로 오름차순 정렬
    bool operator()(const Transaction &left, const Transaction &right)
    {
        return left.out > right.out;
    }
};

int solve(vector<vector<int>> &routes)
{
    priority_queue<transaction, vector<transaction>, CompareTransaction> pq;
    for (int idx = 0; idx < routes.size(); idx++)
    {
        int in = routes[idx][0] + 30000;
        int out = routes[idx][1] + 30000;
        pq.push({in, out});
    }

    int ret = 0;
    int last_camera = -1;
    while (!pq.empty())
    {
        transaction top = pq.top();
        pq.pop();

        if (top.in <= last_camera && last_camera <= top.out)
        {
            // do nothing
        }
        else
        {
            last_camera = top.out;
            ret += 1;
        }
    }
    return ret;
}

int solution(vector<vector<int>> routes)
{
    return solve(routes);
}
