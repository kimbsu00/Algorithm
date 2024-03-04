#include <iostream>
#include <vector>
#include <string>

using namespace std;

int N;
vector<char> input;

bool compare(int left_idx, int right_idx)
{
    bool ret = true;
    while (left_idx < right_idx)
    {
        char left = input[left_idx];
        char right = input[right_idx];

        if (left < right)
        {
            ret = true;
            break;
        }
        else if (left > right)
        {
            ret = false;
            break;
        }
        else
        {
            left_idx += 1;
            right_idx -= 1;
        }
    }
    return ret;
}

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> N;

    char ch;
    for (int idx = 0; idx < N; idx++)
    {
        cin >> ch;
        input.push_back(ch);
    }

    int left_idx = 0;
    int right_idx = input.size() - 1;
    int length = 0;

    while (length < input.size())
    {
        if (compare(left_idx, right_idx))
        {
            printf("%c", input[left_idx]);
            left_idx += 1;
        }
        else
        {
            printf("%c", input[right_idx]);
            right_idx -= 1;
        }
        length += 1;

        if (length > 0 && length % 80 == 0)
        {
            printf("\n");
        }
    }

    return 0;
}
/*
반례 모음

8
A C C D B C C B

161
A A A A A A A A A A A A A A A A A A A A A A A A A A A A A A A A A A A A A A A A A A A A A A A A A A A A A A A A A A A A A A A A A A A A A A A A A A A A A A A A A A A A A A A A A A A A A A A A A A A A A A A A A A A A A A A A A A A A A A A A A A A A A A A A A A A A A A A A A A A A A A A A A A A A A A A A A A A A A A A A B
*/
