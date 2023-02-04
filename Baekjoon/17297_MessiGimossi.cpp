#include <iostream>
#include <string>

using namespace std;

const string messi = "Messi";
const string messiGimossi = "Messi Gimossi";

int M, N;
int *cache;

int get_length(int n)
{
    if (n == 1)
        return 5;
    else if (n == 2)
        return 13;

    int &ret = cache[n];
    if (ret != -1)
        return ret;

    return ret = get_length(n - 1) + 1 + get_length(n - 2);
}

char solve(int n, int pos)
{
    if (n == 1)
    {
        return messi.at(pos);
    }
    else if (n == 2)
    {
        return messiGimossi.at(pos);
    }

    int prefix_length = get_length(n - 1);

    if (pos < prefix_length)
        return solve(n - 1, pos);
    else if (pos == prefix_length)
        return ' ';
    else
        return solve(n - 2, pos - prefix_length - 1);
}

int calculate_N(int M)
{
    if (M <= 5)
        return 1;
    else if (M <= 13)
        return 2;

    int tmp[2] = {5, 13};
    int cur_length = tmp[1] + 1 + tmp[0];

    int ret = 3;
    while (cur_length <= M)
    {
        tmp[0] = tmp[1];
        tmp[1] = cur_length;
        cur_length = tmp[1] + 1 + tmp[0];
        ret += 1;
    }

    return ret;
}

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> M;

    N = calculate_N(M);

    cache = new int[N + 1];
    fill(cache, cache + N + 1, -1);

    char answer = solve(N, M - 1);
    if (answer == ' ')
        cout << "Messi Messi Gimossi\n";
    else
        cout << answer << "\n";

    return 0;
}
