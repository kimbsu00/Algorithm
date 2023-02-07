#include <iostream>

using namespace std;

int W, H;
int *block;

int find_left_max(int pos)
{
    int ret = 0;
    for (int idx = pos - 1; idx >= 0; idx--)
    {
        if (ret < block[idx])
            ret = block[idx];
    }
    return ret;
}

int find_right_max(int pos)
{
    int ret = 0;
    for (int idx = pos + 1; idx < W; idx++)
    {
        if (ret < block[idx])
            ret = block[idx];
    }
    return ret;
}

int solve()
{
    int ret = 0;
    for (int idx = 1; idx < W - 1; idx++)
    {
        int left_max = find_left_max(idx);
        int right_max = find_right_max(idx);

        int cur_height = block[idx];
        if (cur_height < left_max && cur_height < right_max)
        {
            if (left_max < right_max)
            {
                ret += (left_max - cur_height);
            }
            else
            {
                ret += (right_max - cur_height);
            }
        }
    }
    return ret;
}

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> H >> W;
    block = new int[W];

    for (int idx = 0; idx < W; idx++)
    {
        cin >> block[idx];
    }

    cout << solve() << "\n";

    return 0;
}
