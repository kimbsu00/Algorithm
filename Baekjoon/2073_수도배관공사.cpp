#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

struct Pipe
{
    int length, size;
} typedef pipe;

const int MAX = INT_MAX;

int D, P;
vector<pipe> pipes;
int cache[100005];

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    fill(&cache[0], &cache[100005], 0);

    cin >> D >> P;

    int length, size;
    for (int idx = 0; idx < P; idx++)
    {
        cin >> length >> size;
        pipes.push_back({length, size});
    }

    cache[0] = MAX;
    for (pipe p : pipes)
    {
        int copy_cache[100005];
        copy(cache, cache + 100005, copy_cache);

        for (int idx = p.length; idx <= D; idx++)
        {
            if (copy_cache[idx - p.length])
            {
                cache[idx] = max(cache[idx], min(copy_cache[idx - p.length], p.size));
            }
        }
    }
    printf("%d\n", cache[D]);

    return 0;
}
