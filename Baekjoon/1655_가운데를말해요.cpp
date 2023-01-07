#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int N;
/*
1. 최대 힙의 크기는 최소 힙의 크기보다 같거나 1만큼 크다.
2. 최대 힙의 최대 값은 최소 힙의 최소 값보다 작아야 한다.

이 규칙대로 데이터를 힙에 추가하면 최대 힙의 최대 값이 항상 중간 값이 된다.
*/
priority_queue<int, vector<int>, greater<int>> min_heap;
priority_queue<int, vector<int>, less<int>> max_heap;

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> N;

    int input;
    for (int idx = 0; idx < N; idx++)
    {
        cin >> input;

        if (min_heap.empty() && max_heap.empty())
        {
            max_heap.push(input);
        }
        else
        {
            if (max_heap.size() == min_heap.size() + 1)
            {
                min_heap.push(input);
            }
            else
            {
                max_heap.push(input);
            }

            int min_top = min_heap.top();
            int max_top = max_heap.top();
            if (min_top < max_top)
            {
                min_heap.pop();
                max_heap.pop();

                min_heap.push(max_top);
                max_heap.push(min_top);
            }
        }

        cout << max_heap.top() << "\n";
    }

    return 0;
}
