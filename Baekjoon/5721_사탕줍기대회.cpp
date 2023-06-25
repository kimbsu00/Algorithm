#include <iostream>
#include <vector>

using namespace std;

int M, N;
int row[100000], col[100000];

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    vector<int> answer;
    while (true)
    {
        cin >> M >> N;

        if (M == 0 && N == 0)
        {
            break;
        }

        for (int r = 0; r < M; r++)
        {
            for (int c = 0; c < N; c++)
            {
                cin >> row[c];
                if (c == 0)
                {
                    // do nothing
                }
                else if (c == 1)
                {
                    row[c] = max(row[c], row[c - 1]);
                }
                else
                {
                    row[c] = max(row[c - 1], row[c - 2] + row[c]);
                }
            }

            col[r] = row[N - 1];
        }

        for (int r = 1; r < M; r++)
        {
            if (r == 1)
            {
                col[r] = max(col[r], col[r - 1]);
            }
            else
            {
                col[r] = max(col[r - 1], col[r - 2] + col[r]);
            }
        }

        answer.push_back(col[M - 1]);
    }

    for (int ans : answer)
    {
        cout << ans << "\n";
    }

    return 0;
}
