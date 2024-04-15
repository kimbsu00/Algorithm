#include <iostream>
#include <queue>
#include <algorithm>

using namespace std;

struct Node
{
    int cnt, copy, time;
} typedef node;

const int MAX = 1000000;
int S;
bool visited[2005][2005];

int solve()
{
    fill(&visited[0][0], &visited[2004][2005], false);

    queue<Node> q;
    q.push({1, 1, 1});

    int ret = MAX;
    while (!q.empty())
    {
        node front = q.front();
        q.pop();

        if (front.cnt == S)
        {
            ret = min(ret, front.time);
            continue;
        }

        if (front.cnt > S)
        {
            ret = min(ret, front.cnt - S + front.time);
            continue;
        }

        if (visited[front.cnt][front.copy])
        {
            continue;
        }
        visited[front.cnt][front.copy] = true;

        if (front.cnt > 2)
        {
            // 1개 제거
            q.push({front.cnt - 1, front.copy, front.time + 1});
        }
        // 붙여넣기
        q.push({front.cnt + front.copy, front.copy, front.time + 1});
        // 복사
        q.push({front.cnt, front.cnt, front.time + 1});
    }

    return ret;
}

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> S;

    int answer = solve();
    printf("%d\n", answer);

    return 0;
}
