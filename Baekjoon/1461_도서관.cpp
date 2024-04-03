#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int N, M;
vector<int> negative, positive;

int solve()
{
    int ret = 0;
    int max_value = -1;
    for (int idx = 0; idx < negative.size(); idx++)
    {
        max_value = max(max_value, -negative[idx]);

        if (idx % M == 0)
        {
            ret += 2 * (-negative[idx]);
        }
    }

    for (int idx = 0; idx < positive.size(); idx++)
    {
        max_value = max(max_value, positive[idx]);

        if (idx % M == 0)
        {
            ret += 2 * positive[idx];
        }
    }

    ret -= max_value;

    return ret;
}

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> N >> M;

    int input;
    for (int idx = 0; idx < N; idx++)
    {
        cin >> input;

        if (input < 0)
        {
            negative.push_back(input);
        }
        else if (input > 0)
        {
            positive.push_back(input);
        }
    }
    sort(negative.begin(), negative.end(), less<int>());
    sort(positive.begin(), positive.end(), greater<int>());

    int answer = solve();
    printf("%d\n", answer);

    return 0;
}
