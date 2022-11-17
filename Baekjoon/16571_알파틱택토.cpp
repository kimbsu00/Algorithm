/*
  url: https://www.acmicpc.net/problem/16571
*/

#include <iostream>
#include <algorithm>

using namespace std;

int tic_tac_toe[3][3];
int row[8][3] = {
    {0, 0, 0}, // 0행
    {1, 1, 1}, // 1행
    {2, 2, 2}, // 2행
    {0, 1, 2}, // 0열
    {0, 1, 2}, // 1열
    {0, 1, 2}, // 2열
    {0, 1, 2}, // LT to RB
    {2, 1, 0}  // RT to LB
};
int col[8][3] = {
    {0, 1, 2}, // 0행
    {0, 1, 2}, // 1행
    {0, 1, 2}, // 2행
    {0, 0, 0}, // 0열
    {1, 1, 1}, // 1열
    {2, 2, 2}, // 2열
    {0, 1, 2}, // LT to RB
    {0, 1, 2}  // RT to LB
};

int get_game_winner()
{
    for (int idx = 0; idx < 8; idx++)
    {
        int a = tic_tac_toe[row[idx][0]][col[idx][0]];
        int b = tic_tac_toe[row[idx][1]][col[idx][1]];
        int c = tic_tac_toe[row[idx][2]][col[idx][2]];

        if (a != 0 && a == b && b == c)
            return a;
    }

    return 0;
}

int solve(int cur_player)
{
    // 내가 진 경우에 -1 리턴
    if (get_game_winner() == (3 - cur_player))
        return -1;

    int ret = 10;
    for (int r = 0; r < 3; r++)
    {
        for (int c = 0; c < 3; c++)
        {
            if (tic_tac_toe[r][c] == 0)
            {
                tic_tac_toe[r][c] = cur_player;
                ret = min(ret, solve(3 - cur_player));
                tic_tac_toe[r][c] = 0;
            }
        }
    }

    // 비긴 경우에는 0 리턴
    if (ret == 10 || ret == 0)
        return 0;

    // 내 결과는 상대방한테 반대이므로 - 붙여서 리턴
    return -ret;
}

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int count = 0;
    for (int row = 0; row < 3; row++)
    {
        for (int col = 0; col < 3; col++)
        {
            cin >> tic_tac_toe[row][col];

            if (tic_tac_toe[row][col] != 0)
                count += 1;
        }
    }

    int player = 1;
    if ((count % 2) == 1)
        player = 2;

    int answer = solve(player);
    if (answer > 0)
        cout << "W\n";
    else if (answer < 0)
        cout << "L\n";
    else
        cout << "D\n";

    return 0;
}
