#include <iostream>
#include <vector>
#include <algorithm>

#define ALPHABET_COUNT 26

using namespace std;

/*
알파벳 26개로 만들 수 있는 조합 -> 26bit -> int형(32bit) 정수로 표한 가능
z y x w v u t s r q p o n m l k j i h g f e d c b a
0 0 0 0 0 0 1 0 0 0 0 0 1 0 0 0 0 1 0 0 0 0 0 1 0 1
*/
const int DEFAULT_VALUE = 0b00000010000010000100000101;
int N, K;
vector<int> words;

int how_many_readable_word(int alphabets)
{
    int ret = 0;
    for (int idx = 0; idx < words.size(); idx++)
    {
        if ((words[idx] & alphabets) == words[idx])
        {
            ret += 1;
        }
    }
    return ret;
}

int solve(int cnt, int alphabets, int cur_alphabet)
{
    if (cnt <= 0)
        return how_many_readable_word(alphabets);

    if (cur_alphabet == 26)
        return 0;

    return max(solve(cnt - 1, alphabets | (1 << cur_alphabet), cur_alphabet + 1), solve(cnt, alphabets, cur_alphabet + 1));
}

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> N >> K;

    for (int idx = 0; idx < N; idx++)
    {
        string input;
        cin >> input;

        int word = 0 | DEFAULT_VALUE;
        for (int idx = 4; idx < input.size() - 4; idx++)
        {
            int shl_value = input[idx] - 'a';
            word |= (1 << shl_value);
        }

        words.push_back(word);
    }

    cout << solve(K, 0, 0) << "\n";

    return 0;
}
