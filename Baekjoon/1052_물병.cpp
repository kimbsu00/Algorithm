#include <iostream>

using namespace std;

int N, K;

int solve()
{
    int ret = 0;

    while (true)
    {
        int bottle = N + ret;
        int cnt = 0;

        while (bottle > 0)
        {
            int is_odd = bottle % 2;
            bottle /= 2;

            if (is_odd)
            {
                cnt += 1;
            }
        }

        if (cnt <= K)
        {
            break;
        }

        ret += 1;
    }

    return ret;
}

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> N >> K;

    cout << solve() << "\n";

    return 0;
}
