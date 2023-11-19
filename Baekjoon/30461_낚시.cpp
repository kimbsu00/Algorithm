#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int N, M, Q;
int map[2000][2000];
int prefix_sum[2000][2000];

void make_prefix_sum()
{
    for (int col = 0; col < M; col++)
    {
        int sum = map[0][col];
        prefix_sum[col][0] = sum;
        for (int row = 1; row < N; row++)
        {
            sum += map[row][col];
            prefix_sum[col][row] = sum;
            if (col > 0)
            {
                prefix_sum[col][row] += prefix_sum[col - 1][row - 1];
            }
        }
    }
}

int solve(int w, int p)
{
    return prefix_sum[p][w];
}

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> N >> M >> Q;

    fill(&map[0][0], &map[1999][2000], -1);
    for (int row = 0; row < N; row++)
    {
        for (int col = 0; col < M; col++)
        {
            cin >> map[row][col];
        }
    }
    make_prefix_sum();

    vector<int> answer;
    int W, P;
    for (int idx = 0; idx < Q; idx++)
    {
        cin >> W >> P;
        answer.push_back(solve(W - 1, P - 1));
    }

    for (int ans : answer)
    {
        cout << ans << "\n";
    }

    return 0;
}
