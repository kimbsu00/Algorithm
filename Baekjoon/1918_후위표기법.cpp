#include <iostream>
#include <string>
#include <stack>

using namespace std;

string solve(string infix)
{
    string ret = "";
    int idx = 0;

    stack<char> stk;
    while (idx < infix.size())
    {
        char ch = infix[idx];

        if (ch == '(')
        {
            stk.push(ch);
        }
        else if (ch == ')')
        {
            while (true)
            {
                char top = stk.top();
                stk.pop();

                if (top == '(')
                {
                    break;
                }
                else
                {
                    ret += top;
                }
            }
        }
        else if (ch == '+' || ch == '-')
        {
            while (!stk.empty())
            {
                char top = stk.top();

                if (top == '(')
                {
                    break;
                }
                else
                {
                    stk.pop();
                    ret += top;
                }
            }
            stk.push(ch);
        }
        else if (ch == '*' || ch == '/')
        {
            while (!stk.empty())
            {
                char top = stk.top();

                if (top == '*' || top == '/')
                {
                    stk.pop();
                    ret += top;
                }
                else
                {
                    break;
                }
            }
            stk.push(ch);
        }
        else
        {
            ret += ch;
        }

        idx += 1;
    }

    while (!stk.empty())
    {
        ret += stk.top();
        stk.pop();
    }

    return ret;
}

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    string infix;
    cin >> infix;

    string answer = solve(infix);
    cout << answer << "\n";

    return 0;
}
