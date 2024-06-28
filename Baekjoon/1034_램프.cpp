#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>

using namespace std;

int N, M, K;
vector<string> input;
map<string, int> mp;

int main(void)
{
    cin >> N >> M;
    input = vector<string>(N);

    for (int row = 0; row < N; row++)
    {
        cin >> input[row];
        mp[input[row]] += 1;
    }

    cin >> K;

    int answer = 0;
    for (int row = 0; row < N; row++)
    {
        int zero_cnt = 0;
        for (int col = 0; col < M; col++)
        {
            if (input[row][col] == '0')
            {
                zero_cnt += 1;
            }
        }

        bool is_zero_cnt_odd = zero_cnt % 2;
        bool is_k_odd = K % 2;
        if (zero_cnt <= K && is_zero_cnt_odd == is_k_odd)
        {
            answer = max(answer, mp[input[row]]);
        }
    }

    printf("%d\n", answer);
}
