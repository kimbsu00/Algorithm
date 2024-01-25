#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAX = 1987654321;
int T, K;
vector<int> chapter;
vector<int> prefix_sum;
// [left, right] 범위의 챕터를 합칠 때 필요한 비용
int cache[500][500];

int get_range_sum(int left, int right)
{
    if (left <= 0)
    {
        return prefix_sum[right];
    }
    else
    {
        return prefix_sum[right] - prefix_sum[left - 1];
    }
}

// [left, right] 범위의 챕터를 합치는데 필요한 비용을 반환함
int solve(int left, int right)
{
    if (cache[left][right] != MAX)
    {
        return cache[left][right];
    }

    if (left == right)
    {
        return cache[left][right] = 0;
    }
    else
    {
        for (int idx = left; idx < right; idx++)
        {
            int a = solve(left, idx);
            int b = solve(idx + 1, right);

            cache[left][right] = min(cache[left][right], a + b);
        }

        return cache[left][right] += get_range_sum(left, right);
    }
}

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> T;

    vector<int> answer;
    for (int tc = 0; tc < T; tc++)
    {
        cin >> K;

        fill(&cache[0][0], &cache[499][500], MAX);
        chapter = vector<int>(K, 0);
        prefix_sum = vector<int>(K, 0);

        int sum = 0;
        for (int idx = 0; idx < K; idx++)
        {
            cin >> chapter[idx];
            sum += chapter[idx];
            prefix_sum[idx] = sum;
        }

        answer.push_back(solve(0, K - 1));
    }

    for (int ans : answer)
    {
        printf("%d\n", ans);
    }

    return 0;
}
