#include <iostream>
#include <string>

using namespace std;

bool is_palindrome(string &p_str, int left, int right)
{
    bool ret = true;

    int length = right - left;
    int middle = left + length / 2;
    for (int idx = left; idx < middle; idx++)
    {
        if (p_str[idx] != p_str[right - idx - 1])
        {
            ret = false;
            break;
        }
    }

    return ret;
}

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    string input;
    cin >> input;

    bool flag = true;
    for (int idx = 1; idx < input.size(); idx++)
    {
        if (input[0] != input[idx])
        {
            flag = false;
            break;
        }
    }

    // 문자열이 모두 같은 글자로 이루어진 경우
    if (flag)
    {
        cout << -1 << "\n";
    }
    // 그렇지 않은 경우
    else
    {
        for (int idx = 0; idx < input.size() - 1; idx++)
        {
            int length = input.size() - idx;

            for (int left = 0; left <= idx; left++)
            {
                if (!is_palindrome(input, left, left + length))
                {
                    cout << length << "\n";
                    return 0;
                }
            }
        }

        cout << -1 << "\n";
    }

    return 0;
}
