/*
  url: https://www.acmicpc.net/problem/2040
*/

#include <iostream>
#include <algorithm>

using namespace std;

const int UNDEFINED = 987654321;

int N;
int input[3000];
int postfix_sum[3001]; // [idx, N-1] 범위의 부분 합을 저장하고 있는 배열
int cache[3000];

int get_range_sum(int left, int right)
{
    return postfix_sum[left] - postfix_sum[right + 1];
}

// cur_idx 부터 게임을 시작했을 때, 얻을 수 있는 최적의 해
int solve(int cur_idx)
{
    if (cur_idx < 0)
        return 0;

    int &ret = cache[cur_idx];
    if (ret != UNDEFINED)
        return ret;

    ret = 0;
    int diff = UNDEFINED;
    for (int idx = cur_idx; idx >= 0; idx--)
    {
        // 내 점수에서 상대방 점수를 뺀 값이므로,
        // 이 값이 작을 수록 좋은 것
        diff = min(diff, get_range_sum(idx, cur_idx) - solve(idx - 1));
    }

    return ret = diff;
}

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> N;

    for (int round = 0; round < 3; round++)
    {
        fill(&postfix_sum[0], &postfix_sum[3001], 0);
        fill(&cache[0], &cache[3000], UNDEFINED);
        for (int idx = 0; idx < N; idx++)
        {
            cin >> input[idx];
        }

        postfix_sum[N - 1] = input[N - 1];
        for (int idx = N - 2; idx >= 0; idx--)
        {
            postfix_sum[idx] = postfix_sum[idx + 1] + input[idx];
        }

        int answer = solve(N - 1);
        if (answer > 0)
            cout << "B\n";
        else if (answer < 0)
            cout << "A\n";
        else
            cout << "D\n";
    }

    return 0;
}
