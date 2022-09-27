/*
  url: https://www.acmicpc.net/problem/15686
*/

#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int N, M;
vector<pair<int, int>> home;
vector<pair<int, int>> bhc;

/*
idx                 치킨집(bhc) 인덱스
open_bhc_cnt        폐업시키지 않을 치킨집 수
dist                각 집의 치킨 거리
*/
int solve(int idx, int open_bhc_cnt, vector<int> dist)
{
    int ret = 0;
    // M개의 폐업시키지 않을 치킨집을 선택한 경우 or 기저조건
    if (open_bhc_cnt == M || idx == bhc.size())
    {
        for (int i = 0; i < dist.size(); i++)
            ret += dist[i];
        return ret;
    }

    // idx번 째 치킨집을 폐업하는 경우
    int a = solve(idx + 1, open_bhc_cnt, dist);
    for (int i = 0; i < home.size(); i++)
    {
        int m_dist = abs(home[i].first - bhc[idx].first) + abs(home[i].second - bhc[idx].second);
        dist[i] = min(dist[i], m_dist);
    }
    // idx번 째 치킨집을 폐업시키지 않는 경우
    int b = solve(idx + 1, open_bhc_cnt + 1, dist);

    return min(a, b);
}

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> N >> M;

    int input;
    for (int r = 0; r < N; r++)
    {
        for (int c = 0; c < N; c++)
        {
            cin >> input;

            switch (input)
            {
            // 집
            case 1:
                home.push_back(make_pair(r, c));
                break;
            // 치킨집
            case 2:
                bhc.push_back(make_pair(r, c));
                break;
            }
        }
    }

    vector<int> dist(home.size(), 1000000);
    cout << solve(0, 0, dist);

    return 0;
}
