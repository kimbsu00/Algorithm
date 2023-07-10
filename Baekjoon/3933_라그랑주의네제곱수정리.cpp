#include <iostream>
#include <vector>

using namespace std;

/**
 * 10 -> 1024
 * 11 -> 2048
 * 12 -> 4096
 * 13 -> 8192
 * 14 -> 16384
 * 15 -> 32768
 * 16 -> 65536
 */
int dp[32769][5];

vector<int> solve(vector<int> input)
{
    for (int num = 1; num * num < 32769; num++)
    {
        int numnum = num * num;
        dp[numnum][1] = 1;

        for (int idx = numnum; idx < 32769; idx++)
        {
            dp[idx][2] += dp[idx - numnum][1];
            dp[idx][3] += dp[idx - numnum][2];
            dp[idx][4] += dp[idx - numnum][3];
        }
    }

    vector<int> ret;
    for (int num : input)
    {
        ret.push_back(dp[num][1] + dp[num][2] + dp[num][3] + dp[num][4]);
    }

    return ret;
}

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    fill(&dp[0][0], &dp[32768][5], 0);

    vector<int> input;
    int num;
    while (true)
    {
        cin >> num;

        if (num == 0)
        {
            break;
        }

        input.push_back(num);
    }

    vector<int> answer = solve(input);
    for (int ans : answer)
    {
        cout << ans << "\n";
    }

    return 0;
}
