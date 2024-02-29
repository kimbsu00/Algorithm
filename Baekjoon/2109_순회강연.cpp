#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

struct Node
{
    int price, deadline;
} typedef node;

struct compare
{
    bool operator()(const node &left, const node &right)
    {
        return left.price > right.price;
    }
};

bool vec_compare(const node &left, const node &right)
{
    return left.deadline < right.deadline;
}

int N;
vector<node> input;

int solve()
{
    priority_queue<node, vector<node>, compare> pq;
    for (int idx = 0; idx < N; idx++)
    {
        node &inp = input[idx];
        if (inp.deadline > pq.size())
        {
            pq.push(inp);
        }
        else
        {
            const node &top = pq.top();
            if (top.price < inp.price)
            {
                pq.pop();
                pq.push(inp);
            }
        }
    }

    int ret = 0;
    while (!pq.empty())
    {
        ret += pq.top().price;
        pq.pop();
    }
    return ret;
}

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> N;

    int P, D;
    for (int idx = 0; idx < N; idx++)
    {
        cin >> P >> D;
        input.push_back({P, D});
    }
    sort(input.begin(), input.end(), vec_compare);

    int answer = solve();
    printf("%d\n", answer);

    return 0;
}
