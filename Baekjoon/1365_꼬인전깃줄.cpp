#include <iostream>
#include <vector>

using namespace std;

int N;
vector<int> telephone_pole;

int binary_search(int start, int end, int target, vector<int> &vec)
{
    int mid;
    while (start <= end)
    {
        mid = (start + end) / 2;

        if (vec[mid] < target)
        {
            start = mid + 1;
        }
        else if (vec[mid] > target)
        {
            end = mid - 1;
        }
        else
        {
            return mid;
        }
    }
    return start;
}

int solve()
{
    vector<int> lis(N, 0);
    lis[0] = telephone_pole[0];

    int lis_idx = 0;
    int tel_idx = 1;
    for (; tel_idx < N; tel_idx++)
    {
        if (lis[lis_idx] < telephone_pole[tel_idx])
        {
            lis_idx += 1;
            lis[lis_idx] = telephone_pole[tel_idx];
        }
        else
        {
            int idx = binary_search(0, lis_idx, telephone_pole[tel_idx], lis);
            lis[idx] = telephone_pole[tel_idx];
        }
    }

    int lis_size = lis_idx + 1;
    return N - lis_size;
}

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> N;
    telephone_pole = vector<int>(N);

    for (int idx = 0; idx < N; idx++)
    {
        cin >> telephone_pole[idx];
    }

    int answer = solve();
    printf("%d\n", answer);

    return 0;
}
