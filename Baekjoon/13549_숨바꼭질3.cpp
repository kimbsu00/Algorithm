#include <iostream>

using namespace std;

int N, K;
int cache[100001];

int solve(int pos)
{
    if (pos < 0 || pos > 100000)
    {
        return 987654321;
    }

    if (pos == K)
    {
        return 0;
    }

    if (pos > K)
    {
        return pos - K;
    }

    int &ret = cache[pos];
    if (ret != -1)
    {
        return ret;
    }
    ret = 987654321;

    if (0 < pos && pos < K)
    {
        ret = min(ret, solve(pos * 2));
    }
    if (pos < K)
    {
        ret = min(ret, 1 + solve(pos + 1));
    }

    ret = min(ret, 1 + solve(pos - 1));

    return ret;
}

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> N >> K;

    fill(&cache[0], &cache[100001], -1);

    cout << solve(N) << "\n";

    return 0;
}
