#include <iostream>
#include <string>
#include <vector>
#include <bitset>

using namespace std;

int N, K;
vector<unsigned int> input;
long long cache[2048];

void print_binary(unsigned int number)
{
    if (number >> 1)
    {
        print_binary(number >> 1);
    }
    putc((number & 1) ? '1' : '0', stdout);
}

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    fill(&cache[0], &cache[2048], -1);
    cin >> N >> K;

    string str;
    for (int idx = 0; idx < N; idx++)
    {
        cin >> str;

        unsigned int num = 0;
        int cnt = 0;
        for (char ch : str)
        {
            int idx = ch - '0';
            num = num | (1 << idx);
        }

        if (cache[num] == -1)
        {
            input.push_back(num);
            cache[num] = 1;
        }
        else
        {
            cache[num] += 1;
        }
    }

    long long answer = 0;
    for (int idx = 0; idx < input.size(); idx++)
    {
        unsigned int left = input[idx];

        for (int idx2 = idx + 1; idx2 < input.size(); idx2++)
        {
            unsigned int right = input[idx2];

            unsigned int result = left | right;
            int result_bit_cnt = bitset<10>(result).count();

            if (result_bit_cnt == K)
            {
                answer += cache[left] * cache[right];
            }
        }

        int bit_cnt = bitset<10>(left).count();
        if ((bit_cnt == K) && (cache[left] > 1))
        {
            answer += (cache[left] * (cache[left] - 1)) / 2;
        }
    }

    cout << answer << "\n";

    return 0;
}
