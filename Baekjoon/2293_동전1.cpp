/*
  url: https://www.acmicpc.net/problem/2293
*/

#include <iostream>

using namespace std;

int n, k;
int coin[101];
int cache[10001]; // 선택한 동전의 가치가 idx원이 되도록 하는 경우의 수

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    fill(&cache[0], &cache[10001], 0);

    cin >> n >> k;
    for (int idx = 1; idx <= n; idx++)
    {
        cin >> coin[idx];
    }
    cache[0] = 1;

    // i번째 동전(coin[i]원)을 사용해서 
    for (int i = 1; i <= n; i++)
    {
        // 가치가 j원이 되도록 하는 경우의 수를 계산함
        for (int j = coin[i]; j <= k; j++)
        {
            cache[j] += cache[j - coin[i]];
        }
    }

    /*
    중복 처리가 어떻게 되는거지?

    {2, 5} 동전 종류로 7원을 만들 때,
    (2 + 5) 와 (5 + 2) 를 생각해보자
    (2 + 5)가 되려면 2원짜리 동전으로 7원을 만들기 전에 5원짜리 동전의 존재 여부를 알아야 됨
    (5 + 2)가 되려면 5원짜리 동전으로 7원을 만들기 전에 2원짜리 동전의 존재 여부를 알아야 됨
    여기서 모순이 발생하기 때문에 중복 처리가 됨을 확인할 수 있음
    */

    cout << cache[k];

    return 0;
}
