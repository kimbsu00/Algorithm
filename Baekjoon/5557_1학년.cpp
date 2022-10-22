/*
  url: https://www.acmicpc.net/problem/5557
*/

#include <iostream>
#include <vector>

using namespace std;

int N;
vector<int> input;
long long cache[100][21];

long long solve(int idx, int sum)
{
    if (sum < 0 || sum > 20)
        return 0;

    if (idx == N - 1)
    {
        if (sum == input[N - 1])
            return 1;
        else
            return 0;
    }

    long long &ret = cache[idx][sum];
    if (ret != -1)
        return ret;

    ret = solve(idx + 1, sum + input[idx]) + solve(idx + 1, sum - input[idx]);
    return ret;
}

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> N;
    for (int i = 0; i < N; i++)
    {
        int tmp;
        cin >> tmp;
        input.push_back(tmp);
    }

    fill(&cache[0][0], &cache[99][21], -1);
    cout << solve(1, input[0]);

    return 0;
}
