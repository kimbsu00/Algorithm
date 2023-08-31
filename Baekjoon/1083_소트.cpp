#include <iostream>
#include <vector>

using namespace std;

int N, S;

void solve(vector<int> &input, int cnt)
{
    int left = 0;
    while (cnt > 0)
    {
        if (left == input.size())
        {
            break;
        }

        int max_idx = left;
        int max_value = input[left];
        for (int idx = left; (idx < input.size()) && (idx - left <= cnt); idx++)
        {
            if (max_value < input[idx])
            {
                max_value = input[idx];
                max_idx = idx;
            }
        }

        if (left == max_idx)
        {
            left += 1;
        }
        else
        {
            input.erase(input.begin() + max_idx);
            input.insert(input.begin() + left, max_value);

            cnt -= (max_idx - left);
        }
    }
}

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> N;

    vector<int> input = vector<int>(N);
    for (int idx = 0; idx < N; idx++)
    {
        cin >> input[idx];
    }

    cin >> S;

    solve(input, S);

    for (int ans : input)
    {
        cout << ans << " ";
    }
    cout << "\n";

    return 0;
}
