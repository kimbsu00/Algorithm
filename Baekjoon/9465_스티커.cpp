/*
  url: https://www.acmicpc.net/problem/9465
*/

#include <iostream>
#include <vector>

using namespace std;

int T, n;
int cache[2][100000];

int solve(int **sticker)
{
    fill(&cache[0][0], &cache[1][100000], 0);

    cache[0][0] = sticker[0][0];
    cache[1][0] = sticker[1][0];

    if (n == 1)
        return max(cache[0][0], cache[1][0]);

    cache[0][1] = sticker[1][0] + sticker[0][1];
    cache[1][1] = sticker[0][0] + sticker[1][1];

    /*
    [0][i] 번째의 스티커를 제거하는 경우,
    [1][i-1] 또는 [1][i-2] 번째 스티커를 제거한 경우가 최대값이 됨
    */
    for (int i = 2; i < n; i++)
    {
        cache[0][i] = sticker[0][i] + max(cache[1][i - 1], cache[1][i - 2]);
        cache[1][i] = sticker[1][i] + max(cache[0][i - 1], cache[0][i - 2]);
    }

    int ret = max(cache[0][n - 1], cache[1][n - 1]);

    return ret;
}

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> T;

    vector<int> answer;
    while (T-- > 0)
    {
        cin >> n;

        int **sticker = new int *[2];
        sticker[0] = new int[n];
        sticker[1] = new int[n];

        for (int i = 0; i < 2; i++)
        {
            for (int j = 0; j < n; j++)
            {
                cin >> sticker[i][j];
            }
        }

        answer.push_back(solve(sticker));
    }

    for (int i = 0; i < answer.size(); i++)
    {
        cout << answer[i] << "\n";
    }

    return 0;
}
