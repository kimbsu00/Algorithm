#include <iostream>
#include <string>
#include <vector>
#include <queue>

using namespace std;

long long solution(int n, vector<int> works)
{
    priority_queue<int> pq;
    for (int idx = 0; idx < works.size(); idx++)
    {
        pq.push(works[idx]);
    }

    while (n > 0 && !pq.empty())
    {
        int top = pq.top();
        pq.pop();

        if (top - 1 > 0)
        {
            pq.push(top - 1);
        }
        n -= 1;
    }

    long long answer = 0;
    while (!pq.empty())
    {
        int top = pq.top();
        pq.pop();
        answer += top * top;
    }
    return answer;
}

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    // int n = 4;
    // vector<int> works;
    // works.push_back(4);
    // works.push_back(3);
    // works.push_back(3);

    int n = 1;
    vector<int> works;
    works.push_back(2);
    works.push_back(1);
    works.push_back(2);

    // int n = 3;
    // vector<int> works;
    // works.push_back(1);
    // works.push_back(1);

    int answer = solution(n, works);
    printf("%d\n", answer);

    return 0;
}
