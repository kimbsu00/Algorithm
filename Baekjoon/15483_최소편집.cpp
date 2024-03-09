#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

const int MAX = 2100000000;
string A, B;
int cache[1000][1000];

int solve(int a_idx, int b_idx, int diff)
{
    if (a_idx >= A.size() || b_idx >= B.size())
    {
        return abs(diff);
    }

    char a = A[a_idx];
    char b = B[b_idx];

    int &ret = cache[a_idx][b_idx];
    if (ret != -1)
    {
        return ret;
    }
    ret = MAX;

    if (a == b)
    {
        // 서로 문자가 같은 경우
        ret = min(ret, solve(a_idx + 1, b_idx + 1, diff));
    }
    else
    {
        // A 문자 한 개 변경
        ret = min(ret, 1 + solve(a_idx + 1, b_idx + 1, diff));
    }

    // A에 문자 한 개 추가
    ret = min(ret, 1 + solve(a_idx, b_idx + 1, diff + 1));
    // A에서 문자 한 개 제거
    ret = min(ret, 1 + solve(a_idx + 1, b_idx, diff - 1));

    return ret;
}

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    fill(&cache[0][0], &cache[999][1000], -1);
    cin >> A >> B;

    if (A == B)
    {
        printf("0\n");
    }
    else
    {
        int diff = ((int)A.size()) - ((int)B.size());
        int answer = solve(0, 0, diff);
        printf("%d\n", answer);
    }

    return 0;
}
