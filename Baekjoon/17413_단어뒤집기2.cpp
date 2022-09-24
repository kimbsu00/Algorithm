/*
  url: https://www.acmicpc.net/problem/17413
*/

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <stack>

using namespace std;

vector<string> split(string input, char delimiter)
{
    vector<string> ret;
    stringstream ss(input);
    string temp;

    while (getline(ss, temp, delimiter))
    {
        ret.push_back(temp);
    }

    return ret;
}

string get_stack_string(stack<char>& stk)
{
    string ret = "";
    while (!stk.empty())
    {
        ret += stk.top();
        stk.pop();
    }
    return ret;
}

string solve(string input)
{
    string ret = "";
    bool is_tag = false;
    stack<char> stk;

    for (int idx = 0; idx < input.length(); idx++)
    {
        char ch = input[idx];

        if (ch == '<')
        {
            ret.append(get_stack_string(stk));
            is_tag = true;
            ret += ch;
        }
        else if (ch == '>')
        {

            is_tag = false;
            ret += ch;
        }
        else
        {
            if (is_tag)
            {
                ret += ch;
            }
            else
            {
                if (ch == ' ')
                {
                    if (stk.empty())
                    {
                        ret += ch;
                    }
                    else
                    {
                        ret.append(get_stack_string(stk));
                        ret += ch;
                    }
                }
                else
                {
                    stk.push(ch);
                }
            }
        }
    }
    ret.append(get_stack_string(stk));

    return ret;
}

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    string input;
    getline(cin, input);

    cout << solve(input);

    return 0;
}
