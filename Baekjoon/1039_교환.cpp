#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAX = 987654321;
int N, K;

void swap(int &left, int &right)
{
    int tmp = left;
    left = right;
    right = tmp;
}

int to_int(vector<int> &number)
{
    if (number.empty())
    {
        return 0;
    }

    int ret = 0;
    int digit = 1;
    for (int idx = number.size() - 1; idx >= 0; idx--)
    {
        int num = number[idx];
        ret += num * digit;
        digit *= 10;
    }
    return ret;
}

int solve(vector<int> number, int idx, int change)
{
    if (change == 0)
    {
        return to_int(number);
    }

    if (idx + 1 >= number.size())
    {
        if (change % 2)
        {
            vector<int> num_cnt(10, 0);
            for (int idx = 0; idx < number.size(); idx++)
            {
                num_cnt[number[idx]] += 1;
            }

            for (int idx = 0; idx < 10; idx++)
            {
                if (num_cnt[idx] >= 2)
                {
                    return to_int(number);
                }
            }

            int left = number.size() - 2;
            int right = number.size() - 1;
            swap(number[left], number[right]);

            return to_int(number);
        }
        else
        {
            return to_int(number);
        }
    }

    int ret = solve(number, idx + 1, change);
    int swap_idx = idx;
    for (int next = idx + 1; next < number.size(); next++)
    {
        if (number[swap_idx] < number[next])
        {
            swap_idx = next;
            swap(number[idx], number[swap_idx]);
            ret = max(ret, solve(number, idx + 1, change - 1));
            swap(number[idx], number[swap_idx]);
        }
        else if (idx < swap_idx && (number[swap_idx] == number[next]))
        {
            swap_idx = next;
            swap(number[idx], number[swap_idx]);
            ret = max(ret, solve(number, idx + 1, change - 1));
            swap(number[idx], number[swap_idx]);
        }
    }

    return ret;
}

struct TestData
{
    int N, K, answer;
} typedef test_data;

void test()
{
    vector<test_data> test;
    test.push_back({1, 1, -1});
    test.push_back({1, 10, -1});
    test.push_back({10, 1, -1});
    test.push_back({10, 2, -1});
    test.push_back({12, 2, 12});
    test.push_back({100, 1, 100});
    test.push_back({100, 5, 100});
    test.push_back({1000000, 10, 1000000});
    test.push_back({210, 1, 201});
    test.push_back({1220, 2, 2210});
    test.push_back({135745, 5, 755431});
    test.push_back({135745, 6, 755431});
    test.push_back({135745, 7, 755431});
    test.push_back({404, 1, 440});
    test.push_back({404, 2, 440});
    test.push_back({4040, 1, 4400});
    test.push_back({4040, 2, 4400});
    test.push_back({4044, 1, 4440});
    test.push_back({4044, 2, 4440});
    test.push_back({8404, 1, 8440});
    test.push_back({8404, 2, 8440});
    test.push_back({3404, 1, 4403});
    test.push_back({3404, 2, 4430});
    test.push_back({3404, 3, 4430});
    test.push_back({199, 1, 991});
    test.push_back({8799, 2, 9987});
    test.push_back({123444, 3, 444321});
    test.push_back({213444, 3, 444321});
    test.push_back({321444, 3, 444321});
    test.push_back({123444, 4, 444321});
    test.push_back({123455, 1, 523451});
    test.push_back({123455, 2, 553421});
    test.push_back({123455, 3, 554321});
    test.push_back({123455, 4, 554321});
    test.push_back({789432, 10, 987423});
    test.push_back({421888, 3, 888421});
    test.push_back({999299, 1, 999992});
    test.push_back({999299, 2, 999992});
    test.push_back({929292, 1, 999222});
    test.push_back({929292, 2, 999222});
    test.push_back({929292, 3, 999222});
    test.push_back({123456, 1, 623451});
    test.push_back({123456, 2, 653421});
    test.push_back({123456, 3, 654321});
    test.push_back({123456, 4, 654312});
    test.push_back({123456, 5, 654321});

    int cnt = 0;
    for (test_data td : test)
    {
        N = td.N;
        K = td.K;

        int zero_cnt = 0;
        vector<int> number;
        vector<int> num_cnt(10, 0);
        while (N > 0)
        {
            int mod = N % 10;
            number.insert(number.begin(), mod);
            N /= 10;

            num_cnt[mod] += 1;
        }

        bool flag = false;
        for (int idx = 0; idx < 10; idx++)
        {
            if (num_cnt[idx] > 1)
            {
                flag = true;
                break;
            }
        }

        int answer;
        if (!flag && (num_cnt[0] + 1 == number.size()))
        {
            answer = -1;
        }
        else
        {
            answer = solve(number, 0, K);
        }

        if (answer == td.answer)
        {
            printf("SUCCESS\nN=%d\tK=%d\tanswer=%d\tmy_answer=%d\n", td.N, td.K, td.answer, answer);
        }
        else
        {
            printf("FAIL\nN=%d\tK=%d\tanswer=%d\tmy_answer=%d\n", td.N, td.K, td.answer, answer);
        }
    }
}

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    // test();

    cin >> N >> K;

    int zero_cnt = 0;
    vector<int> number;
    vector<int> num_cnt(10, 0);
    while (N > 0)
    {
        int mod = N % 10;
        number.insert(number.begin(), mod);
        N /= 10;

        num_cnt[mod] += 1;
    }

    bool flag = false;
    for (int idx = 0; idx < 10; idx++)
    {
        if (num_cnt[idx] > 1)
        {
            flag = true;
            break;
        }
    }

    int answer;
    if (!flag && (num_cnt[0] + 1 == number.size()))
    {
        answer = -1;
    }
    else
    {
        answer = solve(number, 0, K);
    }
    printf("%d\n", answer);

    return 0;
}
