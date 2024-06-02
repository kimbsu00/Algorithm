#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct APT
{
    int pos, students;
} typedef apt;

struct APT_Increment
{
    bool operator()(const apt &left, const apt &right)
    {
        return left.pos > right.pos;
    }
};

struct APT_Decrement
{
    bool operator()(const apt &left, const apt &right)
    {
        return left.pos < right.pos;
    }
};

int N, K, S;
priority_queue<apt, vector<apt>, APT_Increment> left_apt;
priority_queue<apt, vector<apt>, APT_Decrement> right_apt;

bool compare(const apt &left, const apt &right)
{
    return left.pos < right.pos;
}

int solve()
{
    int ret = 0;

    while (!left_apt.empty() || !right_apt.empty())
    {
        int sum = 0;
        // 종료
        if (!left_apt.empty() && !right_apt.empty())
        {
            apt left = left_apt.top();
            apt right = right_apt.top();

            int left_dist = S - left.pos;
            int right_dist = right.pos - S;

            if (left_dist >= right_dist)
            {
                while (!left_apt.empty() && sum < K)
                {
                    left = left_apt.top();
                    left_apt.pop();

                    int enable = K - sum;
                    if (enable >= left.students)
                    {
                        sum += left.students;
                    }
                    else
                    {
                        sum += enable;
                        left.students -= enable;
                        left_apt.push(left);
                        break;
                    }
                }
                ret += left_dist;
            }
            else
            {
                while (!right_apt.empty() && sum < K)
                {
                    right = right_apt.top();
                    right_apt.pop();

                    int enable = K - sum;
                    if (enable >= right.students)
                    {
                        sum += right.students;
                    }
                    else
                    {
                        sum += enable;
                        right.students -= enable;
                        right_apt.push(right);
                        break;
                    }
                }
                ret += right_dist;
            }
        }
        // 왼쪽 아파트만 남은 경우
        else if (!left_apt.empty())
        {
            apt left = left_apt.top();

            int left_dist = S - left.pos;
            while (!left_apt.empty() && sum < K)
            {
                left = left_apt.top();
                left_apt.pop();

                int enable = K - sum;
                if (enable >= left.students)
                {
                    sum += left.students;
                }
                else
                {
                    sum += enable;
                    left.students -= enable;
                    left_apt.push(left);
                    break;
                }
            }
            ret += left_dist;
        }
        // 오른쪽 아파트만 남은 경우
        else if (!right_apt.empty())
        {
            apt right = right_apt.top();

            int right_dist = right.pos - S;
            while (!right_apt.empty() && sum < K)
            {
                right = right_apt.top();
                right_apt.pop();

                int enable = K - sum;
                if (enable >= right.students)
                {
                    sum += right.students;
                }
                else
                {
                    sum += enable;
                    right.students -= enable;
                    right_apt.push(right);
                    break;
                }
            }
            ret += right_dist;
        }
    }

    return ret * 2;
}

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> N >> K >> S;

    int pos, students;
    for (int idx = 0; idx < N; idx++)
    {
        cin >> pos >> students;

        if (pos < S)
        {
            left_apt.push({pos, students});
        }
        else if (pos > S)
        {
            right_apt.push({pos, students});
        }
    }

    int answer = solve();
    printf("%d\n", answer);

    return 0;
}
