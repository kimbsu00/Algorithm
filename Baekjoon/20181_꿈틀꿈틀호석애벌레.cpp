#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int N, K;
vector<long long> input;
vector<long long> prefix_sum;
long long cache[100005];

long long get_range_sum(int left, int right)
{
    if (left == 0)
    {
        return prefix_sum[right];
    }
    else
    {
        return prefix_sum[right] - prefix_sum[left - 1];
    }
}

long long solve(int left, int right)
{
    if (left >= N)
    {
        return 0;
    }

    long long &ret = cache[left];
    if (ret != -1)
    {
        return ret;
    }
    ret = 0;

    long long range_sum = get_range_sum(left, right);
    if (range_sum >= K)
    {
        if (left < right)
        {
            ret = max(ret, solve(left + 1, right));
        }
        else
        {
            ret = max(ret, solve(left + 1, right + 1));
        }

        long long energy = range_sum - K;
        ret = max(ret, energy + solve(right + 1, right + 1));
    }
    else
    {
        for (right = right + 1; right < N; right++)
        {
            range_sum += input[right];

            if (range_sum >= K)
            {
                ret = max(ret, solve(left + 1, right));
                long long energy = range_sum - K;
                ret = max(ret, energy + solve(right + 1, right + 1));
                break;
            }
        }
    }

    return ret;
}

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    fill(&cache[0], &cache[100005], -1);

    cin >> N >> K;
    input = vector<long long>(N);
    prefix_sum = vector<long long>(N);

    for (int idx = 0; idx < N; idx++)
    {
        cin >> input[idx];
    }

    prefix_sum[0] = input[0];
    for (int idx = 1; idx < N; idx++)
    {
        prefix_sum[idx] += prefix_sum[idx - 1] + input[idx];
    }

    long long answer = solve(0, 0);
    printf("%lld\n", answer);

    return 0;
}
