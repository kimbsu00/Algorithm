/*
  url: https://www.acmicpc.net/problem/9660
*/

#include <iostream>

using namespace std;

long long N;

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> N;

    /*
    1 -> (1)        승리
    2 -> (1, 1)     패배
    3 -> (3)        승리
    4 -> (4)        승리
    5 -> (3, 2)     승리
    6 -> (4, 2)     승리
    7 -> (1, 6)     패배
         (3, 4)     패배
         (4, 3)     패배
    8 -> (1, 7)     승리 -> 승리
         (3, 5)     패배
         (4, 4)     패배
    9 -> (1, 8)     패배
         (3, 6)     패배
         (4, 5)     패배
    10 -> (1, 9)    승리 -> 승리
          (3, 7)    승리
          (4, 6)    패배
    ...
    */
    int mod = N % 7;
    if (mod == 0 || mod == 2)
    {
        cout << "CY\n";
    }
    else
    {
        cout << "SK\n";
    }

    return 0;
}
