#include <iostream>
#include <stack>

using namespace std;

int N;
int *answer;
stack<pair<int, int>> stk;

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> N;
    answer = new int[N];
    fill(answer, answer + N, -1);

    int input;
    for (int idx = 0; idx < N; idx++)
    {
        cin >> input;

        while (!stk.empty())
        {
            // stack의 top과 input을 비교함
            pair<int, int> top = stk.top();

            // top < input 인 경우, top의 오큰수는 input이 됨
            if (top.second < input)
            {
                answer[top.first] = input;
                stk.pop();
            }
            // top >= input 인 경우, break
            else
            {
                break;
            }
        }
        stk.push({idx, input});
    }

    for (int idx = 0; idx < N; idx++)
    {
        cout << answer[idx] << " ";
    }

    return 0;
}
