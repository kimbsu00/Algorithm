#include <iostream>
#include <string>
#include <stack>
#include <regex>

using namespace std;

// solve 함수는 메모리 초과가 난다~
string solve(string &input)
{
    if (input.length() < 2)
    {
        return "NOISE";
    }

    string str = "";
    stack<int> stk;
    int idx = 0;
    for (; idx < input.length();)
    {
        if (input[idx] == '1')
        {
            if (stk.empty())
            {
                stk.push(idx);
                str.append("1");
                idx += 1;
            }
            else
            {
                int prev = stk.top();
                int diff = idx - prev;

                // "01" 제거
                if (diff == 2)
                {
                    str.erase(str.end() - 1);
                    idx += 1;
                }
                // "100~1~" 제거
                else
                {
                    stk.pop();
                    str.erase(str.end() - diff, str.end());
                    while (input[idx] == '1')
                    {
                        idx++;
                    }
                }
            }
        }
        else
        {
            str.append("0");
            idx += 1;
        }
    }

    if (str == "01" || str.empty())
    {
        return "SUBMARINE";
    }
    else
    {
        return "NOISE";
    }
}

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    string input;
    cin >> input;

    regex submarine("(100+1+|01)+");
    bool answer = regex_match(input, submarine);

    cout << (answer ? "SUBMARINE" : "NOISE") << "\n";

    return 0;
}
