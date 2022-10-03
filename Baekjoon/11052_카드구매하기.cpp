/*
  url: https://www.acmicpc.net/problem/11052
*/

#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int N;
vector<int> price;
int cache[1001]; // 카드 index개를 사는데 필요한 최대 금액

int solve()
{
    for (int i = 1; i <= N; i++)
    {
        for (int j = 1; j <= i; j++)
        {
            // i개의 카드를 산다고 가정했을 때,
            // 이전에 가지고 있던 값과 {j개 + (i-j)개}를 사는데 필요한 금액과 비교하면 됨
            cache[i] = max(cache[i], price[j] + cache[i - j]);
        }
    }

    return cache[N];
}

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    fill(&cache[0], &cache[1001], 0);
    cin >> N;

    price.push_back(0);
    for (int idx = 1; idx <= N; idx++)
    {
        int tmp;
        cin >> tmp;
        price.push_back(tmp);

        cache[idx] = tmp;
    }

    cout << solve();

    return 0;
}
