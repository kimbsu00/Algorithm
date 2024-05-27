#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

string cache[45][45];

string max(const string &left, const string &right)
{
    if (left.size() > right.size())
    {
        return left;
    }
    else
    {
        return right;
    }
}

string solve(string &A, string &B, int a_idx, int b_idx)
{
    if (a_idx >= A.size())
    {
        return "";
    }

    if (b_idx >= B.size())
    {
        return "";
    }

    string &ret = cache[a_idx][b_idx];
    if (ret != "\0")
    {
        return ret;
    }
    ret = "";
    char a_ch = A[a_idx];
    char b_ch = B[b_idx];
    if (a_ch == b_ch)
    {
        ret = max(ret, string(1, a_ch) + solve(A, B, a_idx + 1, b_idx + 1));
    }

    ret = max(ret, solve(A, B, a_idx + 1, b_idx));

    for (int idx = b_idx; idx < B.size(); idx++)
    {
        b_ch = B[idx];
        if (a_ch == b_ch)
        {
            ret = max(ret, string(1, a_ch) + solve(A, B, a_idx + 1, idx + 1));
            break;
        }
    }

    return ret;
}

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    fill(&cache[0][0], &cache[44][45], "\0");

    string A, B;
    cin >> A >> B;

    string answer = solve(A, B, 0, 0);
    printf("%s\n", answer.c_str());

    return 0;
}
