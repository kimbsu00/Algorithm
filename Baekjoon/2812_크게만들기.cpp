#include <iostream>
#include <string>
#include <stack>

using namespace std;

int N, K;
string input;

string solve(string &str)
{
    stack<pair<int, char>> stk;

    int pop_cnt = 0;
    for (int idx = 0; idx < str.size(); idx++)
    {
        // 충분히 많은 숫자를 지운 경우에는 반복문 탈출
        if (pop_cnt == K)
            break;

        char ch = str[idx];

        while (!stk.empty() && (pop_cnt < K))
        {
            pair<int, char> top = stk.top();

            // 높은 자리수에는 큰 수가 위치해야 하므로
            if (top.second < ch)
            {
                stk.pop();
                str[top.first] = -1;

                pop_cnt += 1;
            }
            else
            {
                break;
            }
        }
        stk.push({idx, ch});
    }

    string ret = "";
    for (int idx = 0; idx < str.size(); idx++)
    {
        if (str[idx] != -1)
        {
            ret += str[idx];
        }
    }

    /*
    stack의 top과 ch 값이 계속 같은 경우에는 pop_cnt가 K보다 작게 되는데,
    뒤에 숫자 몇 개를 버려주면 정답이 된다.

    이유?
    pop_cnt가 K보다 작다는 말은, 반복문이 종료될 때에 pop된 숫자가 없다는 말과 같음
    따라서 뒤에 위치한 연속된 숫자가 동일한 숫자이자, 가장 작은 숫자라는 말이 되기 때문에 뒤에 숫자 몇 개를 버리면 정답이 된다.
    */
    if (pop_cnt < K)
    {
        int diff = K - pop_cnt;
        ret = ret.substr(0, ret.size() - diff);
    }

    return ret;
}

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> N >> K >> input;

    cout << solve(input) << "\n";

    return 0;
}
