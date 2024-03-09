#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MIN = -2100000000;

int N, max_pull;
vector<int> input;
vector<int> prefix_sum;
int cache[50000][4];

/**
 * @param start start index of range (Inclusive)
 * @param end end index of range (Inclusive)
 */
int get_range_sum(int start, int end)
{
    if (start == 0)
    {
        return prefix_sum[end];
    }
    else
    {
        return prefix_sum[end] - prefix_sum[start - 1];
    }
}

int solve(int idx, int cnt)
{
    if (cnt == 0)
    {
        return 0;
    }

    if (idx >= N)
    {
        return 0;
    }

    int &ret = cache[idx][cnt];
    if (ret != -1)
    {
        return ret;
    }

    ret = solve(idx + 1, cnt);
    if (cnt > 0 && idx + max_pull <= N)
    {
        ret = max(ret, get_range_sum(idx, idx + max_pull - 1) + solve(idx + max_pull, cnt - 1));
    }

    return ret;
}

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    fill(&cache[0][0], &cache[49999][4], -1);
    cin >> N;

    int num;
    int sum = 0;
    for (int idx = 0; idx < N; idx++)
    {
        cin >> num;
        input.push_back(num);

        sum += num;
        prefix_sum.push_back(sum);
    }

    cin >> max_pull;

    int answer = solve(0, 3);
    printf("%d\n", answer);

    return 0;
}
