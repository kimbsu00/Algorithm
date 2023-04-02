#include <iostream>

using namespace std;

int N, M, K;
int cache[101][101];

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> N >> M >> K;

    fill(&cache[0][0], &cache[100][101], 0);

    for (int idx = 1; idx <= 100; idx++)
    {
        cache[idx][0] = 1;
        cache[0][idx] = 1;
    }

    for (int a = 1; a <= N; a++)
    {
        for (int z = 1; z <= M; z++)
        {
            /*
            a개의 A와 z개의 Z로 만들 수 있는 글자 =
            (a-1)개의 A와 z개의 Z로 만들 수 있는 글자 앞에 a를 붙이는 경우
            a개의 A와 (z-1)개의 Z로 만들 수 있는 글자 앞에 z를 붙이는 경우
            */
            cache[a][z] = cache[a - 1][z] + cache[a][z - 1];

            if (cache[a][z] > 1000000000)
                cache[a][z] = 1000000000;
        }
    }

    if (cache[N][M] < K)
    {
        cout << -1 << "\n";
    }
    else
    {
        int a_cnt = N;
        int z_cnt = M;

        for (int idx = 0; idx < N + M; idx++)
        {
            int tmp = cache[a_cnt - 1][z_cnt];

            if (a_cnt == 0)
            {
                cout << 'z';
                z_cnt -= 1;
            }
            else if (z_cnt == 0)
            {
                cout << 'a';
                a_cnt -= 1;
            }
            else if (K <= tmp)
            {
                cout << 'a';
                a_cnt -= 1;
            }
            else
            {
                K -= tmp;
                cout << 'z';
                z_cnt -= 1;
            }
        }
    }

    return 0;
}
