#include <iostream>
#include <string>
#include <algorithm>
#include <cmath>

using namespace std;

int N;
int alpha_size[26] = {
    0,
};

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> N;

    for (int idx = 0; idx < N; idx++)
    {
        string input;
        cin >> input;

        for (int idx2 = 0; idx2 < input.size(); idx2++)
        {
            char ch = input[idx2];
            int pos = ch - 'A';

            alpha_size[pos] += pow(10, input.size() - idx2 - 1);
        }
    }

    sort(alpha_size, alpha_size + 26, greater<int>());

    int sum = 0;
    for (int idx = 0; idx < 10; idx++)
    {
        sum += alpha_size[idx] * (9 - idx);
    }

    cout << sum << "\n";

    return 0;
}
