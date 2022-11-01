/*
  url: https://www.acmicpc.net/problem/1107
*/

#include <iostream>
#include <algorithm>

using namespace std;

const int DEFAULT_CHANNEL = 100;
int N, M;
bool num_usable[10];

bool check_usable_number(int num)
{
    if (num < 0)
        return false;

    if (num == 0)
        return num_usable[0];

    bool ret = true;
    while (num > 0)
    {
        int tmp = num % 10;
        if (!num_usable[tmp])
        {
            ret = false;
            break;
        }

        num /= 10;
    }
    return ret;
}

int get_number_length(int num)
{
    if (num < 0)
        return 5000000;

    if (num == 0)
        return 1;

    int ret = 0;
    while (num > 0)
    {
        num /= 10;
        ret += 1;
    }
    return ret;
}

int solve()
{
    int ret = 987654321;
    int diff = 1;
    while (ret == 987654321)
    {
        int left = N - diff;
        int right = N + diff;

        if (check_usable_number(left))
        {
            ret = min(ret, get_number_length(left) + diff);
        }
        if (check_usable_number(right))
        {
            ret = min(ret, get_number_length(right) + diff);
        }
        if (left == DEFAULT_CHANNEL || right == DEFAULT_CHANNEL)
        {
            ret = min(ret, diff);
        }

        diff += 1;
    }
    ret = min(ret, abs(N - DEFAULT_CHANNEL));

    return ret;
}

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    fill(&num_usable[0], &num_usable[10], true);
    cin >> N >> M;
    for (int idx = 0; idx < M; idx++)
    {
        int num;
        cin >> num;
        num_usable[num] = false;
    }

    if (N == DEFAULT_CHANNEL)
    {
        cout << "0\n";
    }
    else
    {
        int answer = solve();
        if (check_usable_number(N))
            answer = min(answer, get_number_length(N));

        cout << answer << "\n";
    }

    return 0;
}
