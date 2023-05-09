#include <iostream>
#include <algorithm>

using namespace std;

int N, K;
int *A, **R, **M;

int solve(int day, int sum)
{
    if (day == K)
    {
        return sum;
    }

    int ret = -1;
    int tmp = 0;
    for (int r = 0; r < N; r++)
    {
        if (A[r] > 0)
        {
            A[r] -= 1;
            tmp += R[day][r];
            for (int m = 0; m < N; m++)
            {
                if (A[m] > 0)
                {
                    A[m] -= 1;
                    tmp += M[day][m];

                    ret = max(ret, solve(day + 1, sum + tmp));

                    A[m] += 1;
                    tmp -= M[day][m];
                }
            }
            A[r] += 1;
            tmp -= R[day][r];
        }
    }

    return ret;
}

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> N >> K;

    A = new int[N];
    for (int idx = 0; idx < N; idx++)
    {
        cin >> A[idx];
    }

    R = new int *[K];
    M = new int *[K];
    for (int idx = 0; idx < K; idx++)
    {
        R[idx] = new int[N];
        M[idx] = new int[N];
    }

    for (int row = 0; row < K; row++)
    {
        for (int col = 0; col < N; col++)
        {
            cin >> R[row][col];
        }
    }

    for (int row = 0; row < K; row++)
    {
        for (int col = 0; col < N; col++)
        {
            cin >> M[row][col];
        }
    }

    cout << solve(0, 0) << "\n";

    return 0;
}
