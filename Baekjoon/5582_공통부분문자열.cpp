/*
  url: https://www.acmicpc.net/problem/5582
*/

#include <iostream>
#include <vector>
#include <string>
#include <cmath>

using namespace std;

string input1, input2;
int cache[4001][4001];

int solve()
{
    int ret = 0;

    for (int i = 0; i < input1.length(); i++)
    {
        for (int j = 0; j < input2.length(); j++)
        {
            if (input1[i] == input2[j])
            {
                cache[i][j] = 1;
                
                if (i > 0 && j > 0)
                    cache[i][j] = max(cache[i][j], cache[i - 1][j - 1] + 1);
            }

            ret = max(ret, cache[i][j]);
        }
    }

    return ret;
}

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> input1 >> input2;

    fill(&cache[0][0], &cache[4000][4001], -1);
    cout << solve();

    return 0;
}
