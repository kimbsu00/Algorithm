#include <iostream>

using namespace std;

int cogwheel[4][8];
int left_idx[4];
int right_idx[4];
int K;

void print_cogwheel()
{
    for (int idx = 0; idx < 4; idx++)
    {
        printf("left_idx=%d, right_idx=%d\n", left_idx[idx], right_idx[idx]);
        for (int cnt = 0; cnt < 8; cnt++)
        {
            printf("%d ", cogwheel[idx][cnt]);
        }
        printf("\n\n");
    }
}

void rotate(int cogwheel_idx, int dir, int from)
{
    int cur_left = left_idx[cogwheel_idx];
    int cur_right = right_idx[cogwheel_idx];

    // 오른쪽의 톱니바퀴의 영향으로 돌아가는 경우
    if (cogwheel_idx < from)
    {
        if (cogwheel_idx != 0)
        {
            int prev_left = left_idx[cogwheel_idx - 1];
            int prev_right = right_idx[cogwheel_idx - 1];

            if (cogwheel[cogwheel_idx][cur_left] != cogwheel[cogwheel_idx - 1][prev_right])
            {
                rotate(cogwheel_idx - 1, dir * (-1), cogwheel_idx);
            }
        }
    }
    // 왼쪽의 톱니바퀴의 영향으로 돌아가는 경우
    else if (cogwheel_idx > from)
    {
        if (cogwheel_idx != 3)
        {
            int next_left = left_idx[cogwheel_idx + 1];
            int next_right = right_idx[cogwheel_idx + 1];

            if (cogwheel[cogwheel_idx][cur_right] != cogwheel[cogwheel_idx + 1][next_left])
            {
                rotate(cogwheel_idx + 1, dir * (-1), cogwheel_idx);
            }
        }
    }
    else
    {
        // 왼쪽에 더 돌릴 톱니바퀴가 있으면 더 돌려버려 ~,~
        if (cogwheel_idx != 0)
        {
            int prev_left = left_idx[cogwheel_idx - 1];
            int prev_right = right_idx[cogwheel_idx - 1];

            if (cogwheel[cogwheel_idx][cur_left] != cogwheel[cogwheel_idx - 1][prev_right])
            {
                rotate(cogwheel_idx - 1, dir * (-1), cogwheel_idx);
            }
        }
        // 오른쪽도 똑같이 ~,~
        if (cogwheel_idx != 3)
        {
            int next_left = left_idx[cogwheel_idx + 1];
            int next_right = right_idx[cogwheel_idx + 1];

            if (cogwheel[cogwheel_idx][cur_right] != cogwheel[cogwheel_idx + 1][next_left])
            {
                rotate(cogwheel_idx + 1, dir * (-1), cogwheel_idx);
            }
        }
    }

    // 시계 방향
    if (dir == 1)
    {
        left_idx[cogwheel_idx] = cur_left - 1;
        if (left_idx[cogwheel_idx] < 0)
        {
            left_idx[cogwheel_idx] = 7;
        }
        right_idx[cogwheel_idx] = cur_right - 1;
        if (right_idx[cogwheel_idx] < 0)
        {
            right_idx[cogwheel_idx] = 7;
        }
    }
    // 반시계 방향
    else if (dir == -1)
    {
        left_idx[cogwheel_idx] = (cur_left + 1) % 8;
        right_idx[cogwheel_idx] = (cur_right + 1) % 8;
    }
}

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    fill(&left_idx[0], &left_idx[4], 6);
    fill(&right_idx[0], &right_idx[4], 2);

    for (int idx = 0; idx < 4; idx++)
    {
        for (int cnt = 0; cnt < 8; cnt++)
        {
            cogwheel[idx][cnt] = getchar() - '0';
        }
        getchar();
    }

    scanf("%d", &K);

    int idx,
        dir;
    for (int k = 0; k < K; k++)
    {
        scanf("%d %d", &idx, &dir);
        idx -= 1;

        rotate(idx, dir, idx);
        // print_cogwheel();
    }

    int answer = 0;
    for (int idx = 0; idx < 4; idx++)
    {
        int cur_left = left_idx[idx];
        int twelve_idx = (cur_left + 2) % 8;
        int value = cogwheel[idx][twelve_idx] * (1 << idx);
        answer += value;
    }

    printf("%d\n", answer);

    return 0;
}
