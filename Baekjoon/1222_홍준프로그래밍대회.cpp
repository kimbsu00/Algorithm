#include <iostream>
#include <map>
#include <algorithm>

using namespace std;

int N;
map<long long, long long> school;

long long solve()
{
    // key 값을 소수, value 값을 개수로 하는 map
    map<long long, long long> divisor_map;
    for (auto it = school.begin(); it != school.end(); it++)
    {
        long long num = it->first;
        long long cnt = it->second;

        for (long long divisor = 1; divisor * divisor <= num; divisor++)
        {
            if (num % divisor == 0)
            {
                auto insert_ret = divisor_map.insert({divisor, cnt});
                if (!insert_ret.second)
                {
                    insert_ret.first->second += cnt;
                }

                long long quotient = num / divisor;
                if (quotient != divisor)
                {
                    insert_ret = divisor_map.insert({quotient, cnt});
                    if (!insert_ret.second)
                    {
                        insert_ret.first->second += cnt;
                    }
                }
            }
        }
    }

    long long ret = N;
    for (auto it = divisor_map.begin(); it != divisor_map.end(); it++)
    {
        if (it->second > 1)
        {
            ret = max(ret, (it->first) * (it->second));
        }
    }
    return ret;
}

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> N;

    int input;
    for (int idx = 0; idx < N; idx++)
    {
        cin >> input;

        auto insert_ret = school.insert({input, 1});
        if (!insert_ret.second)
        {
            insert_ret.first->second += 1;
        }
    }

    long long answer = solve();
    printf("%lld\n", answer);

    return 0;
}
