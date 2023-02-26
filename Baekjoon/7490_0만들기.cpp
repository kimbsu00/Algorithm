#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int N;
vector<string> answer;

/*
@param sum      지금까지의 합
@param sign     더하기(1)인지 빼기(-1)인지
@param idx      몇 번째 숫자인지
@param num      sum과 연산을 수행하거나, 아니면 숫자 (idx+1)를 이어 붙이는 숫자
@param str      수식
*/
void solve(int sum, int sign, int idx, int num, string str)
{
    if (idx == N)
    {
        sum += (sign * num);
        if (sum == 0)
        {
            answer.push_back(str);
        }
        return;
    }

    // 더하기
    solve(sum + (sign * num), 1, idx + 1, idx + 1, str + "+" + to_string(idx + 1));
    // 빼기
    solve(sum + (sign * num), -1, idx + 1, idx + 1, str + "-" + to_string(idx + 1));
    // 이어 붙이기
    solve(sum, sign, idx + 1, num * 10 + (idx + 1), str + " " + to_string(idx + 1));

    return;
}

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int tc;
    cin >> tc;
    while (tc-- > 0)
    {
        cin >> N;

        answer.clear();
        solve(0, 1, 1, 1, "1");
        sort(answer.begin(), answer.end());

        for (string ans : answer)
        {
            cout << ans << "\n";
        }
        cout << "\n";
    }

    return 0;
}
