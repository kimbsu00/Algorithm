#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int N, K;
vector<int> height;

int solve()
{
    vector<int> diff;
    for (int idx = 1; idx < height.size(); idx++)
    {
        diff.push_back(height[idx] - height[idx - 1]);
    }

    sort(diff.begin(), diff.end());

    int ret = 0;
    for (int idx = 0; idx < diff.size() - (K - 1); idx++)
    {
        ret += diff[idx];
    }

    return ret;
}

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> N >> K;

    int input;
    for (int idx = 0; idx < N; idx++)
    {
        cin >> input;
        height.push_back(input);
    }

    cout << solve() << "\n";

    return 0;
}
