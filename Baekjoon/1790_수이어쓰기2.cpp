#include <iostream>
#include <string>

using namespace std;

int N, K;

/**
 * 한 자리 숫자는 1~9 -> 9개
 * 두 자리 숫자는 10~99 -> 90개
 * 세 자리 숫자는 100~999 -> 900개
 * 네 자리 숫자는 1000~9999 -> 9000개
 * ...
 */
int solve()
{
    int min = 1, max = 9;
    long long left = 1, right = 9;
    int length = 1;

    while (true)
    {
        if (left <= K && K <= right)
        {
            break;
        }
        else
        {
            min = max + 1;
            max = min * 10 - 1;
            length += 1;

            long long num_cnt = max - min + 1;
            left = right + 1;
            right += num_cnt * length;
        }
    }

    int ret = -1;
    while (left <= right && min <= N)
    {
        string str = to_string(min);

        if (left + length > K)
        {
            int idx = K - left;
            ret = str[idx] - '0';
            break;
        }
        min += 1;
        left += length;
    }

    return ret;
}

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> N >> K;

    int answer = solve();
    printf("%d\n", answer);

    return 0;
}
