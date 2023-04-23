#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

long long get_greatest_common_divisor(long long a, long long b)
{
    if (a > b)
    {
        return b ? get_greatest_common_divisor(b, a % b) : a;
    }
    else
    {
        return a ? get_greatest_common_divisor(a, b % a) : b;
    }
}

vector<long long> solve(vector<long long> &input)
{
    long long gdc = input[0];
    for (int idx = 1; idx < input.size(); idx++)
    {
        gdc = get_greatest_common_divisor(gdc, input[idx]);
    }

    vector<long long> ret;
    for (long long num = 1; num * num <= gdc; num++)
    {
        if (num * num == gdc)
        {
            ret.push_back(num);
        }
        else if (gdc % num == 0)
        {
            if (num != 1)
            {
                ret.push_back(num);
            }
            ret.push_back(gdc / num);
        }
    }

    sort(ret.begin(), ret.end());

    return ret;
}

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int N;
    vector<long long> input;
    long long left, right;

    cin >> N >> left;

    for (int idx = 1; idx < N; idx++)
    {
        cin >> right;

        input.push_back(abs(left - right));
        left = right;
    }

    vector<long long> answer = solve(input);
    for (long long ans : answer)
    {
        cout << ans << " ";
    }
    cout << "\n";

    return 0;
}
