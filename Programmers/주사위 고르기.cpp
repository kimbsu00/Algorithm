#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int max_win = 0;
vector<int> answer;

vector<int> get_sum_combination(vector<vector<int>> &dice, vector<int> &A)
{
    int last_idx = A.size() - 1;
    vector<int> a_idx(A.size(), 0);
    vector<int> a_sum;

    while (true)
    {
        if (a_idx[0] == 6)
        {
            break;
        }

        int sum = 0;
        for (int idx = 0; idx < a_idx.size(); idx++)
        {
            sum += dice[A[idx]][a_idx[idx]];
        }
        a_sum.push_back(sum);
        // printf("sum=%d\n", sum);

        int cur_idx = last_idx;
        a_idx[cur_idx] += 1;

        while (cur_idx > 0)
        {
            if (a_idx[cur_idx] == 6)
            {
                a_idx[cur_idx] = 0;
                a_idx[cur_idx - 1] += 1;
                cur_idx -= 1;
            }
            else
            {
                break;
            }
        }
    }

    return a_sum;
}

int calc(vector<vector<int>> &dice, vector<int> &A, vector<int> &B)
{
    int win_cnt = 0;

    vector<int> a_sum_combination = get_sum_combination(dice, A);
    vector<int> b_sum_combination = get_sum_combination(dice, B);

    for (int a_sum : a_sum_combination)
    {
        for (int b_sum : b_sum_combination)
        {
            if (a_sum > b_sum)
            {
                win_cnt += 1;
            }
        }
    }

    // printf("A.size()=%d\tB.size()=%d,win_cnt=%d\n", A.size(), B.size(), win_cnt);

    return win_cnt;
}

void solve(vector<vector<int>> &dice, int idx, vector<int> A, vector<int> B)
{
    // printf("A.size()=%d\tB.size()=%d,idx=%d\n", A.size(), B.size(), idx);

    if (A.size() == dice.size() / 2)
    {
        for (int num = idx; num < dice.size(); num++)
        {
            B.push_back(num);
        }
        // 승리 횟수 계산
        int win_cnt = calc(dice, A, B);
        if (max_win < win_cnt)
        {
            max_win = win_cnt;
            answer = A;
        }

        return;
    }
    else if (B.size() == dice.size() / 2)
    {
        for (int num = idx; num < dice.size(); num++)
        {
            A.push_back(num);
        }
        // 승리 횟수 계산
        int win_cnt = calc(dice, A, B);
        if (max_win < win_cnt)
        {
            max_win = win_cnt;
            answer = A;
        }

        return;
    }

    if (idx == dice.size())
    {
        if (A.size() == B.size())
        {
            // 승리 횟수 계산
            int win_cnt = calc(dice, A, B);
            if (max_win < win_cnt)
            {
                max_win = win_cnt;
                answer = A;
            }
        }

        return;
    }

    A.push_back(idx);
    solve(dice, idx + 1, A, B);
    A.erase(A.begin() + (A.size() - 1));

    B.push_back(idx);
    solve(dice, idx + 1, A, B);
}

vector<int> solution(vector<vector<int>> dice)
{
    solve(dice, 0, vector<int>(), vector<int>());

    for (int idx = 0; idx < answer.size(); idx++)
    {
        answer[idx] += 1;
    }

    return answer;
}

int main(void)
{
    vector<vector<int>> dice;
    dice.push_back(vector<int>({1, 2, 3, 4, 5, 6}));
    dice.push_back(vector<int>({3, 3, 3, 3, 4, 4}));
    dice.push_back(vector<int>({1, 3, 3, 4, 4, 4}));
    dice.push_back(vector<int>({1, 1, 4, 4, 5, 5}));
    dice.push_back(vector<int>({1, 2, 3, 4, 5, 6}));
    dice.push_back(vector<int>({3, 3, 3, 3, 4, 4}));
    dice.push_back(vector<int>({1, 3, 3, 4, 4, 4}));
    dice.push_back(vector<int>({1, 1, 4, 4, 5, 5}));
    dice.push_back(vector<int>({1, 3, 3, 4, 4, 4}));
    dice.push_back(vector<int>({1, 1, 4, 4, 5, 5}));

    vector<int> answer = solution(dice);
    for (int idx = 0; idx < answer.size(); idx++)
    {
        printf("%d ", answer[idx]);
    }
    printf("\n");

    return 0;
}
