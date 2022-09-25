#include <iostream>
#include <vector>
#include <stack>
#include <string>

using namespace std;

// input 문자열의 [left, right] 범위에 해당하는 부분 문자열의 괄호 값을 반환하는 함수
int solve(string &input, int left, int right)
{
    int ret = 0;
    int m_left = -1;
    stack<char> stk;
    for (int idx = left; idx <= right; idx++)
    {
        if (input[idx] == '(')
        {
            stk.push(input[idx]);

            if (m_left == -1)
                m_left = idx;
        }
        else if (input[idx] == '[')
        {
            stk.push(input[idx]);

            if (m_left == -1)
                m_left = idx;
        }
        else if (input[idx] == ')')
        {
            if (stk.empty())
                return -1;

            char top = stk.top();
            stk.pop();
            if (top == '(')
            {
                // () 인 경우
                if (m_left + 1 == idx)
                {
                    ret += 2;
                    m_left = -1;
                }
                else
                {
                    if (stk.empty())
                    {
                        int value = solve(input, m_left + 1, idx - 1);
                        if (value == -1)
                            return -1;

                        ret += 2 * value;
                        m_left = -1;
                    }
                }
            }
            else
            {
                return -1;
            }
        }
        else if (input[idx] == ']')
        {
            if (stk.empty())
                return -1;

            char top = stk.top();
            stk.pop();
            if (top == '[')
            {
                // [] 인 경우
                if (m_left + 1 == idx)
                {
                    ret += 3;
                    m_left = -1;
                }
                else
                {
                    if (stk.empty())
                    {
                        int value = solve(input, m_left + 1, idx - 1);
                        if (value == -1)
                            return -1;

                        ret += 3 * value;
                        m_left = -1;
                    }
                }
            }
            else
            {
                return -1;
            }
        }
    }

    if (!stk.empty())
        ret = -1;

    return ret;
}

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    string input;
    cin >> input;

    int answer = solve(input, 0, input.length() - 1);
    cout << ((answer == -1) ? 0 : answer);

    return 0;
}
