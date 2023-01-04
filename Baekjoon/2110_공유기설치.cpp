#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int N, C;
vector<int> house;

bool compare(const int &a, const int &b)
{
    return a < b;
}

int solve()
{
    int ret = 0;

    // 집과 집 사이 거리의 최소값
    int left = 1;
    // 집과 집 사이 거리의 최대값
    int right = house[N - 1] - house[0];

    while (left <= right)
    {
        int mid = (left + right) / 2;

        // 맨 왼쪽에 있는 집에 공유기 한 개 설치하고 시작
        int cnt = 1;
        int prev_house = house[0];

        // [0, N] 범위의 집에 대하여, mid 주기로 공유기를 설치할 때, 설치 가능한 공유기의 수 == cnt 가 됨
        for (int idx = 1; idx < house.size(); idx++)
        {
            if (house[idx] - prev_house >= mid)
            {
                cnt += 1;
                prev_house = house[idx];
            }
        }

        // mid 주기로 공유기를 설치했을 때, C개 이상의 공유기를 설치 가능한 경우 -> 공유기 설치 주기를 늘려서 다시 테스트
        if (cnt >= C)
        {
            ret = max(ret, mid);
            left = mid + 1;
        }
        // mid 주기로 공유기를 설치했을 때, C개 미만의 공유기밖에 설치 못한 경우 -> 공유기 설치 주기를 줄여서 다시 테스트
        else
        {
            right = mid - 1;
        }
    }

    return ret;
}

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> N >> C;

    int x;
    int left_house = 1234567890;
    int right_house = -1;
    for (int idx = 0; idx < N; idx++)
    {
        cin >> x;
        house.push_back(x);
    }
    sort(house.begin(), house.end(), compare);

    cout << solve() << "\n";

    return 0;
}
