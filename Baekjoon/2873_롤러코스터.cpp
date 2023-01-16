#include <iostream>
#include <string>

using namespace std;

int R, C;
int **map;
int min_value = 10000;
int min_row = -1, min_col = -1;

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> R >> C;

    map = new int *[R];
    for (int idx = 0; idx < R; idx++)
    {
        map[idx] = new int[C];
    }

    for (int row = 0; row < R; row++)
    {
        for (int col = 0; col < C; col++)
        {
            cin >> map[row][col];

            /*
            (row + col) 값이 홀수이어야만 하는 이유를 어떻게 증명하지?
            */
            if (((row + col) % 2 == 1) && (min_value > map[row][col]))
            {
                min_value = map[row][col];
                min_row = row;
                min_col = col;
            }
        }
    }

    string answer = "";
    /*
    홀수 행인 경우,
    모든 칸을 지나가는 경우가 가장 큰 기쁨을 주는 롤러코스터가 됨
    */
    if (R % 2 == 1)
    {
        for (int row = 0; row < R; row++)
        {
            // 왼쪽으로
            if (row % 2 == 1)
            {
                for (int col = 0; col < C - 1; col++)
                {
                    answer += 'L';
                }
            }
            // 오른쪽으로
            else
            {
                for (int col = 0; col < C - 1; col++)
                {
                    answer += 'R';
                }
            }

            if (row < R - 1)
            {
                answer += 'D';
            }
        }
    }
    /*
    홀수 열인 경우,
    모든 칸을 지나가는 경우가 가장 큰 기쁨을 주는 롤러코스터가 됨
    */
    else if (C % 2 == 1)
    {
        for (int col = 0; col < C; col++)
        {
            // 위로
            if (col % 2 == 1)
            {
                for (int row = 0; row < R - 1; row++)
                {
                    answer += 'U';
                }
            }
            // 아래로
            else
            {
                for (int row = 0; row < R - 1; row++)
                {
                    answer += 'D';
                }
            }

            if (col < C - 1)
            {
                answer += 'R';
            }
        }
    }
    /*
    행과 열 모두 홀수가 아닌 경우 == 행과 열 모두 짝수인 경우
    가장 작은 하나의 칸 만을 지나가지 않는 경우가 가장 큰 기쁨을 주는 롤러코스터가 됨
    */
    else
    {
        for (int row = 0; row < min_row - 1; row += 2)
        {
            for (int col = 0; col < C - 1; col++)
            {
                answer += 'R';
            }
            answer += 'D';
            for (int col = 0; col < C - 1; col++)
            {
                answer += 'L';
            }
            answer += 'D';
        }

        for (int col = 0; col < min_col; col++)
        {
            if (col % 2 == 0)
            {
                answer += "DR";
            }
            else
            {
                answer += "UR";
            }
        }

        for (int col = min_col; col < C - 1; col++)
        {
            if (col % 2 == 0)
            {
                answer += "RD";
            }
            else
            {
                answer += "RU";
            }
        }

        for (int row = min_row + 1; row < R - 1; row += 2)
        {
            answer += 'D';
            for (int col = 0; col < C - 1; col++)
            {
                answer += 'L';
            }
            answer += 'D';
            for (int col = 0; col < C - 1; col++)
            {
                answer += 'R';
            }
        }
    }

    cout << answer << "\n";

    return 0;
}
