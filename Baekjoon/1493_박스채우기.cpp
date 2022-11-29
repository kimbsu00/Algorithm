/*
  url: https://www.acmicpc.net/problem/1493
*/

#include <iostream>
#include <algorithm>

using namespace std;

class Cube
{
public:
    long long length;
    long long count;
    long long size;

    Cube() : length(0), count(0), size(0) {}

    Cube(long long p_length, long long p_count) : length(p_length), count(p_count), size(p_length * p_length * p_length) {}
};

long long length, width, height;
int N;
Cube cube[20];

bool compare(const Cube &a, const Cube &b)
{
    return a.size > b.size;
}

int solve(long long p_length, long long p_width, long long p_height)
{
    if (p_length == 0 || p_width == 0 || p_height == 0)
        return 0;

    int ret = 0;

    for (int idx = 0; idx < N; idx++)
    {
        while (cube[idx].count > 0)
        {
            if (cube[idx].length <= p_length && cube[idx].length <= p_width && cube[idx].length <= p_height)
            {
                // idx 번째 큐브 1개로 채우고
                cube[idx].count -= 1;
                p_height -= cube[idx].length;
                ret += 1;

                // 남은 영역에 대하여 재귀 호출
                long long m_length = p_length - cube[idx].length;
                long long m_width = p_width - cube[idx].length;
                long long m_height = cube[idx].length;

                int a = solve(m_length, p_width, m_height);
                int b = solve(cube[idx].length, m_width, m_height);

                if (a == -1 || b == -1)
                    return -1;

                ret += a + b;
            }
            else
            {
                break;
            }
        }
    }

    if (p_height == 0)
        return ret;
    else
        return -1;
}

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> length >> width >> height >> N;

    long long m_length, m_count;
    for (int idx = 0; idx < N; idx++)
    {
        cin >> m_length >> m_count;
        cube[idx] = Cube(1L << m_length, m_count);
    }

    sort(cube, cube + N, compare);

    cout << solve(length, width, height) << "\n";

    return 0;
}
