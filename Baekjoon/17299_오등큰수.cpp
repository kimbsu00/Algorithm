#include <iostream>

using namespace std;

int N;
int *A;
int F[1000001];

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    fill(F, F + 1000001, 0);

    cin >> N;
    A = new int[N];

    int input;
    for (int idx = 0; idx < N; idx++)
    {
        cin >> input;
        A[idx] = input;
        F[input] += 1;
    }

    pair<int, int> *answer = new pair<int, int>[N];
    answer[N - 1] = {-1, N};
    for (int idx = N - 2; idx >= 0; idx--)
    {
        int ngf = -1;
        int ngf_idx = -1;

        int next = idx + 1;
        while (true)
        {
            if (F[A[idx]] < F[A[next]])
            {
                ngf = A[next];
                ngf_idx = next;
                break;
            }

            if (answer[next].first == -1 || answer[next].second == N)
            {
                ngf = -1;
                ngf_idx = N;
                break;
            }

            next = answer[next].second;
        }

        answer[idx] = {ngf, ngf_idx};
    }

    for (int idx = 0; idx < N; idx++)
    {
        cout << answer[idx].first << " ";
    }
    cout << "\n";

    return 0;
}
