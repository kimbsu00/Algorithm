#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAX = 1000000000;

int N, M, H;
int graph[12][32];

bool check_graph()
{
    int ret = true;
    for (int num = 1; num <= N; num++)
    {
        int pos = num;
        for (int depth = 1; depth <= H; depth++)
        {
            if (graph[pos - 1][depth])
            {
                pos -= 1;
            }
            else if (graph[pos][depth])
            {
                pos += 1;
            }
        }

        if (pos != num)
        {
            ret = false;
            break;
        }
    }
    return ret;
}

int solve(int max_cnt, int add_cnt)
{
    if (add_cnt == max_cnt)
    {
        return check_graph() ? add_cnt : MAX;
    }

    int ret = MAX;
    for (int line = 1; line <= N; line++)
    {
        for (int depth = 1; depth <= H; depth++)
        {
            if (graph[line - 1][depth] || graph[line][depth] || graph[line + 1][depth])
            {
                continue;
            }

            graph[line][depth] = 1;
            ret = min(ret, solve(max_cnt, add_cnt + 1));
            graph[line][depth] = 0;

            while (graph[line - 1][depth] == 0 && graph[line + 1][depth] == 0)
            {
                depth += 1;
            }
        }
    }

    return ret;
}

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    fill(&graph[0][0], &graph[11][32], 0);
    cin >> N >> M >> H;

    int A, B;
    for (int idx = 0; idx < M; idx++)
    {
        cin >> A >> B;

        graph[B][A] = 1;
    }

    if (M == 0)
    {
        cout << "0\n";
    }
    else
    {
        int answer = MAX;
        for (int max_cnt = 0; max_cnt < 4; max_cnt++)
        {
            answer = min(answer, solve(max_cnt, 0));
        }
        cout << (answer > 3 ? -1 : answer) << "\n";
    }

    return 0;
}
