#include <iostream>
#include <cmath>

using namespace std;

int N;
int input[50];

void solve()
{
    // 숫자 1개면 무조건 A
    if (N == 1)
    {
        printf("A\n");
    }
    // 숫자 2개인 경우에는
    else if (N == 2)
    {
        // 서로 같은 경우에만 유추 가능
        if (input[0] == input[1])
        {
            printf("%d\n", input[0]);
        }
        // 서로 다르면 정답 없음
        else
        {
            printf("A\n");
        }
    }
    // 3개 이상인 경우에는
    else
    {
        // 1번과 2번이 서로 같은 경우
        if (input[0] == input[1])
        {
            // 모든 숫자가 같은지 확인
            for (int idx = 1; idx < N - 1; idx++)
            {
                // 다른 숫자가 하나라도 있다면 유추 불가능
                if (input[idx] != input[idx + 1])
                {
                    printf("B\n");
                    return;
                }
            }
            // 모두 같으면 같은 숫자 출력
            printf("%d\n", input[0]);
        }
        // 1번과 2번이 서로 다른 경우
        else
        {
            bool is_all_equal = true;
            for (int idx = 1; idx < N - 1; idx++)
            {
                if (input[idx] != input[idx + 1])
                {
                    is_all_equal = false;
                    break;
                }
            }

            // 2 ~ N번 숫자가 모두 같은 경우 -> a는 0이고 b가 2번 숫자인 경우
            if (is_all_equal)
            {
                printf("%d\n", input[N - 1]);
            }
            // 다른 숫자가 있는 경우
            else
            {
                pair<int, int> pos1 = {input[0], input[1]};
                pair<int, int> pos2 = {input[1], input[2]};

                int dx = pos1.first - pos2.first;
                int dy = pos1.second - pos2.second;

                // a가 정수가 아닌 경우
                if (abs(dx) > abs(dy))
                {
                    printf("B\n");
                }
                // a가 정수인 경우
                else
                {
                    int a = dy / dx;
                    int b = input[1] - input[0] * a;

                    // n*a + b 형태인지 확인
                    for (int idx = 1; idx < N - 1; idx++)
                    {
                        int calc = input[idx] * a + b;
                        // 아니면 정답을 유츄 할 수 없음
                        if (calc != input[idx + 1])
                        {
                            printf("B\n");
                            return;
                        }
                    }
                    // 맞으면 정답 계산해서 출력
                    int answer = input[N - 1] * a + b;
                    printf("%d\n", answer);
                }
            }
        }
    }
}

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> N;
    for (int idx = 0; idx < N; idx++)
    {
        cin >> input[idx];
    }

    solve();

    return 0;
}
