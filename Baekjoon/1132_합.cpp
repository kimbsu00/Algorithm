#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>
#include <bitset>

using namespace std;

struct Node
{
    char ch;
    long long multiple;
    bool unable_zero;
    long long num;
} node;

int N;
vector<Node> vec;

string int_2_binary(int num)
{
    string binaryString = bitset<32>(num).to_string();

    // Remove leading zeros
    size_t pos = binaryString.find('1');
    if (pos != string::npos)
    {
        return binaryString.substr(pos);
    }

    // If all bits are zero, return "0"
    return "0";
}

bool compare(const Node &left, const Node &right)
{
    return left.multiple > right.multiple;
}

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> N;
    for (int idx = 0; idx < 10; idx++)
    {
        char ch = 'A' + idx;
        vec.push_back({ch, 0, false, -1});
    }

    string input;
    int flag = 0;
    while (N--)
    {
        cin >> input;

        int size = input.size();
        for (int idx = 0; idx < size; idx++)
        {
            char ch = input[size - idx - 1];
            int ch_idx = ch - 'A';
            long long multiple = powl(10L, idx);

            flag = flag | (1 << ch_idx);

            vec[ch_idx].multiple += multiple;
            vec[ch_idx].unable_zero |= (idx == size - 1);
        }
    }

    sort(vec.begin(), vec.end(), compare);

    if (flag >= ((1 << 10) - 1))
    {
        for (auto it = vec.rbegin(); it != vec.rend(); it++)
        {
            if (it->multiple > 0 && !(it->unable_zero))
            {
                it->num = 0;
                break;
            }
        }
    }

    long long answer = 0;
    long long num = 9;
    for (auto it = vec.begin(); it != vec.end(); it++)
    {
        if (it->num == -1)
        {
            it->num = num;
            num -= 1;
            answer += it->multiple * it->num;
        }
    }

    printf("%lld\n", answer);

    return 0;
}
