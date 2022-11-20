/*
  url: https://www.acmicpc.net/problem/1715
*/

#include <iostream>
#include <queue>

using namespace std;

int N;
priority_queue<int> pq;

int solve()
{
    int ret = 0;

    while (pq.size() > 1)
    {
        int a = -pq.top();
        pq.pop();
        int b = -pq.top();
        pq.pop();

        ret += a + b;
        pq.push(-(a + b));
    }

    return ret;
}

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> N;

    int input;
    for (int idx = 0; idx < N; idx++)
    {
        cin >> input;
        pq.push(-input);
    }

    cout << solve() << "\n";

    return 0;
}
