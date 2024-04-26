#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int N;
vector<int> input;
int cache[205];

int solve(int idx)
{
    int &ret = cache[idx];
    if (ret != -1)
    {
        return ret;
    }
    ret = 1;

    int cur = input[idx];
    for (int next = idx + 1; next < N; next++)
    {
        if (cur < input[next])
        {
            ret = max(ret, 1 + solve(next));
        }
    }

    return ret;
}

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    fill(&cache[0], &cache[205], -1);

    cin >> N;
    input = vector<int>(N);

    for (int idx = 0; idx < N; idx++)
    {
        cin >> input[idx];
    }

    int answer = 0;
    for (int idx = 0; idx < N; idx++)
    {
        int ret = solve(idx);
        answer = max(answer, ret);
        // printf("input[%d]=%d\tret=%d\n", idx, input[idx], ret);
    }

    printf("%d\n", N - answer);

    return 0;
}
