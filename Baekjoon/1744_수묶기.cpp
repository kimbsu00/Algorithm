/*
  url: https://www.acmicpc.net/problem/1744
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int N;
vector<long long> positive_input;
vector<long long> negative_input;
bool zero_cnt = 0;

// 내림차순 정렬
bool compare_increase(long long &a, long long &b)
{
    return a < b;
}

// 오름차순 정렬
bool compare_decrease(long long &a, long long &b)
{
    return a > b;
}

long long solve()
{
    // 양수는 내림차순 정렬
    sort(positive_input.begin(), positive_input.end(), compare_decrease);
    // 음수는 오름차순 정렬
    sort(negative_input.begin(), negative_input.end(), compare_increase);

    long long sum = 0;
    int idx = 0;

    // 양수의 경우, 1*1 또는 숫자가 한 개 남은 경우를 제외하고는 모두 곱해서 더하는게 최대 값이 됨
    for (; idx < positive_input.size();)
    {
        if (idx == positive_input.size() - 1)
        {
            sum += positive_input[idx];
            idx += 1;
        }
        else if (positive_input[idx] == 1 || positive_input[idx + 1] == 1)
        {
            sum += positive_input[idx];
            idx += 1;
        }
        else
        {
            sum += positive_input[idx] * positive_input[idx + 1];
            idx += 2;
        }
    }

    idx = 0;
    // 음수의 경우, (절댓값이 큰 애들) == (크기가 작은 애들)끼리 곱해서 더하면 큰 양수 값이 되므로 작은 애들끼리 곱해서 더해줌
    // 그리고 숫자가 한 개 남은 경우, 
    //    i) 입력 값에 0이 있었다면, (0*음수) = 0 이므로 더하지 않는게 최대 값
    //    ii) 입력 값에 0이 없었다면, 그냥 더하면 됨
    for (; idx < negative_input.size();)
    {
        if (idx == negative_input.size() - 1)
        {
            if (zero_cnt == 0)
                sum += negative_input[idx];
            idx += 1;
        }
        else
        {
            sum += negative_input[idx] * negative_input[idx + 1];
            idx += 2;
        }
    }

    return sum;
}

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> N;

    long long input;
    for (int idx = 0; idx < N; idx++)
    {
        cin >> input;

        if (input < 0)
        {
            negative_input.push_back(input);
        }
        else if (input > 0)
        {
            positive_input.push_back(input);
        }
        else
        {
            zero_cnt += 1;
        }
    }

    cout << solve() << "\n";

    return 0;
}
