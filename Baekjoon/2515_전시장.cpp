#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Picture
{
    int height, cost;
} typedef picture;

int N, S;
vector<picture> pictures;
int cache[300005];

bool compare(const picture &left, const picture &right)
{
    return left.height < right.height;
}

int solve(int idx)
{
    if (idx == N)
    {
        return 0;
    }

    int &ret = cache[idx];
    if (ret != -1)
    {
        return ret;
    }

    int cur_height = pictures[idx].height;
    int cur_cost = pictures[idx].cost;

    picture pic = {cur_height + S, 0};
    // pic보다 높이가 작지 않은 사진들 중, 높이가 가장 낮은 사진을 반환
    auto lb_picture = lower_bound(pictures.begin(), pictures.end(), pic, compare);
    int lb_picture_idx = lb_picture - pictures.begin();

    // idx번 째 그림을 선택하지 않은 경우
    ret = max(ret, solve(idx + 1));

    // idx번 째 그림을 선택한 경우
    ret = max(ret, cur_cost + solve(lb_picture_idx));

    return ret;
}

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    fill(&cache[0], &cache[300005], -1);

    cin >> N >> S;
    pictures = vector<picture>(N);

    int height, cost;
    for (int idx = 0; idx < N; idx++)
    {
        cin >> height >> cost;
        pictures[idx] = {height, cost};
    }
    // 그림 높이에 대하여 오름차순 정렬
    sort(pictures.begin(), pictures.end(), compare);

    int answer = solve(0);
    printf("%d\n", answer);

    return 0;
}
