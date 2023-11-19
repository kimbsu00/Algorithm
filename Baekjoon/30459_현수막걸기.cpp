#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int N, M, R;
vector<int> stick_pos;
vector<int> width;
vector<int> height;

int solve(int left, int right, int p_width)
{
    int ret = -1;

    while (left <= right)
    {
        int mid = (left + right) / 2;
        int size = p_width * height[mid];

        if (size <= R)
        {
            ret = max(ret, size);
            left = mid + 1;
        }
        else
        {
            right = mid - 1;
        }
    }

    return ret;
}

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> N >> M >> R;
    R *= 2;

    int input;
    for (int idx = 0; idx < N; idx++)
    {
        cin >> input;
        stick_pos.push_back(input);
    }

    for (int idx = 0; idx < N; idx++)
    {
        for (int idx2 = idx + 1; idx2 < N; idx2++)
        {
            int tmp = abs(stick_pos[idx2] - stick_pos[idx]);
            width.push_back(tmp);
        }
    }
    sort(width.begin(), width.end(), less<int>());
    width.erase(unique(width.begin(), width.end()), width.end());

    for (int idx = 0; idx < M; idx++)
    {
        cin >> input;
        height.push_back(input);
    }
    sort(height.begin(), height.end(), less<int>());

    int answer = -1;
    for (int idx = 0; idx < width.size(); idx++)
    {
        answer = max(answer, solve(0, M - 1, width[idx]));
    }

    if (answer == -1)
    {
        printf("-1\n");
    }
    else
    {
        printf("%.1f\n", (answer / 2.0));
    }

    return 0;
}
