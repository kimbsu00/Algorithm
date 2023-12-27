#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int N;
vector<int> input;

bool solve(int left, int right, const int &num_idx, const int &target_idx)
{
    if (left > right)
    {
        return false;
    }

    int mid = (left + right) / 2;
    int value = input[mid];

    int num = input[num_idx];
    int target = input[target_idx];
    int sum = value + num;

    if (mid == num_idx || mid == target_idx)
    {
        return solve(left, mid - 1, num_idx, target_idx) || solve(mid + 1, right, num_idx, target_idx);
    }
    else if (sum < target)
    {
        return solve(mid + 1, right, num_idx, target_idx);
    }
    else if (sum > target)
    {
        return solve(left, mid - 1, num_idx, target_idx);
    }
    else if (sum == target)
    {
        // printf("target=%d\tnum=%d\tvalue=%d\n", target, num, value);
        return true;
    }

    return false;
}

int solve(int target_idx)
{
    int target = input[target_idx];

    for (int idx = 0; idx < input.size(); idx++)
    {
        if (idx != target_idx)
        {
            int num = input[idx];

            if (solve(idx + 1, input.size() - 1, idx, target_idx))
            {
                return 1;
            }
        }
    }

    return 0;
}

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> N;
    int num;
    for (int idx = 0; idx < N; idx++)
    {
        cin >> num;
        input.push_back(num);
    }

    sort(input.begin(), input.end());

    int answer = 0;
    for (int idx = 0; idx < input.size(); idx++)
    {
        answer += solve(idx);
    }
    printf("%d\n", answer);

    return 0;
}
