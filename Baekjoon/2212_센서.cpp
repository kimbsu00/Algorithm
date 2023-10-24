#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int N, K;
vector<int> sensor;

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> N >> K;

    int input;
    vector<int> tmp;
    for (int idx = 0; idx < N; idx++)
    {
        cin >> input;
        tmp.push_back(input);
    }

    sort(tmp.begin(), tmp.end(), less<int>());

    int prev_sensor = -1;
    for (int idx = 0; idx < N; idx++)
    {
        if (prev_sensor != tmp[idx])
        {
            sensor.push_back(tmp[idx]);
            prev_sensor = tmp[idx];
        }
    }

    vector<int> dist;
    for (int idx = 0; idx < sensor.size() - 1; idx++)
    {
        dist.push_back(sensor[idx + 1] - sensor[idx]);
    }

    sort(dist.begin(), dist.end(), less<int>());

    int answer = 0;
    if (dist.size() > K)
    {
        for (int idx = 0; idx < dist.size() - K + 1; idx++)
        {
            answer += dist[idx];
        }
    }

    cout << answer << "\n";

    return 0;
}
