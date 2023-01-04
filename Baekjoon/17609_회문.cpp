#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int solve(string &input, int left, int right, int rm_cnt)
{
    // 유사 회문도 아닌 경우
    if (rm_cnt > 1)
        return rm_cnt;

    // 문자열 비교가 끝난 경우
    if (left >= right)
        return rm_cnt;

    int ret = min(solve(input, left + 1, right, rm_cnt + 1), solve(input, left, right - 1, rm_cnt + 1));
    if (input[left] == input[right])
    {
        ret = solve(input, left + 1, right - 1, rm_cnt);
    }

    return ret;
}

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T;
    cin >> T;

    int *answer = new int[T];
    for (int idx = 0; idx < T; idx++)
    {
        string input;
        cin >> input;
        answer[idx] = solve(input, 0, input.size() - 1, 0);
    }

    for (int idx = 0; idx < T; idx++)
    {
        cout << answer[idx] << "\n";
    }

    return 0;
}
