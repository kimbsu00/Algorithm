#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const long long MOD = 1000000007;

int N;
vector<long long> input;
vector<long long> m_pow;

long long solve()
{
    long long ret = 0;
    for (int idx = 0; idx < N; idx++)
    {
        int plus = m_pow[idx];
        int minus = m_pow[N - idx - 1];
        ret += (plus - minus) * input[idx];
        ret %= MOD;
    }
    return ret;
}

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> N;
    input = vector<long long>(N, 0);
    m_pow = vector<long long>(N, 1);

    for (int idx = 0; idx < N; idx++)
    {
        cin >> input[idx];
        if (idx > 0)
        {
            m_pow[idx] = (m_pow[idx - 1] * 2) % MOD;
        }
    }
    sort(input.begin(), input.end(), less<int>());

    long long answer = solve();
    printf("%lld\n", answer);

    return 0;
}
