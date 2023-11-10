#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MIN = -987654321;

struct Node
{
    int idx, time;
};

int N;
vector<int> road;
// idx에서 갈 수 있는 가장 먼 위치와 시간
vector<Node> cache;
// idx에서 뒤로 돌았을 때, 학교까지 도착하는데 필요한 최대 시간
vector<int> turn_point;

void go(int idx)
{
    cache[idx] = {idx, 0};

    int prev_pos = idx;
    int pos = idx + road[idx];
    int time = 1;
    while (pos < N)
    {
        if (cache[pos].idx != -1)
        {
            cache[idx] = {cache[pos].idx, cache[pos].time + time};
            break;
        }

        if (road[pos] == 0)
        {
            break;
        }

        prev_pos = pos;
        pos += road[pos];
        time += 1;
    }

    if (pos == N - 1)
    {
        cache[idx] = {pos, time};
    }
    else if (pos >= N)
    {
        cache[idx] = {prev_pos, time - 1};
    }
}

int back(int idx)
{
    if (turn_point[idx] != -1)
    {
        return turn_point[idx];
    }

    turn_point[idx] = MIN;

    if (cache[idx].idx == N - 1)
    {
        turn_point[idx] = cache[idx].time;
    }

    int prev = idx - road[idx];
    if (0 <= prev)
    {
        int tmp = back(prev);
        turn_point[idx] = max(turn_point[idx], tmp + 1);
    }

    return turn_point[idx];
}

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> N;

    road = vector<int>(N, 0);
    cache = vector<Node>(N, {-1, -1});
    turn_point = vector<int>(N, -1);

    for (int idx = 0; idx < N; idx++)
    {
        cin >> road[idx];
    }

    for (int idx = N - 1; idx >= 0; idx--)
    {
        if (road[idx] != 0)
        {
            go(idx);
        }
    }
    for (int idx = 0; idx < N - 1; idx++)
    {
        if (road[idx] != 0)
        {
            back(idx);
        }
    }

    int pos = 0, time = 0;
    int answer = -1;
    while (pos < N)
    {
        if (road[pos] == 0)
        {
            break;
        }

        answer = max(answer, time + turn_point[pos]);
        pos += road[pos];
        time += 1;
    }

    cout << answer << "\n";

    return 0;
}
