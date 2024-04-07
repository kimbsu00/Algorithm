#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <string>

using namespace std;

struct Homework
{
    int deadline, score;

    string to_string()
    {
        return "deadline=" + std::to_string(deadline) + ", score=" + std::to_string(score);
    }
} typedef homework;

struct HomeworkCompare
{
    /**
     * score를 기준으로 오름차순 정렬
     */
    bool operator()(const homework &left, const homework &right)
    {
        return left.score > right.score;
    }
};

bool compare(const homework &left, const homework &right)
{
    return left.deadline < right.deadline;
}

int N;
vector<homework> input;

int solve()
{
    priority_queue<homework, vector<homework>, HomeworkCompare> pq;

    for (int idx = 0; idx < N; idx++)
    {
        homework &hw = input[idx];

        if (hw.deadline > pq.size())
        {
            pq.push(hw);
        }
        else
        {
            homework top = pq.top();
            if (top.score < hw.score)
            {
                pq.pop();
                pq.push(hw);
            }
        }
    }

    int ret = 0;
    while (!pq.empty())
    {
        homework top = pq.top();
        pq.pop();
        ret += top.score;
    }

    return ret;
}

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> N;
    input = vector<homework>(N);

    int d, w;
    for (int idx = 0; idx < N; idx++)
    {
        cin >> d >> w;
        input[idx] = {d, w};
    }
    sort(input.begin(), input.end(), compare);

    int answer = solve();
    printf("%d\n", answer);

    return 0;
}
