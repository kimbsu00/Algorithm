#include <iostream>

using namespace std;

int N, r, c;

int solve(int width, int row, int col)
{
    if (width <= 2)
    {
        if (row == 0)
        {
            if (col == 0)
            {
                return 0;
            }
            else
            {
                return 1;
            }
        }
        else
        {
            if (col == 0)
            {
                return 2;
            }
            else
            {
                return 3;
            }
        }
    }

    int half_width = width / 2;
    int size = half_width * half_width;
    if (row < half_width)
    {
        // Left Top
        if (col < half_width)
        {
            return solve(half_width, row, col);
        }
        // Right Top
        else
        {
            int bias = size * 1;
            return bias + solve(half_width, row, col - half_width);
        }
    }
    else
    {
        // Left Bottom
        if (col < half_width)
        {
            int bias = size * 2;
            return bias + solve(half_width, row - half_width, col);
        }
        // Right Bottom
        else
        {
            int bias = size * 3;
            return bias + solve(half_width, row - half_width, col - half_width);
        }
    }
}

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> N >> r >> c;

    int width = 1 << N;
    int answer = solve(width, r, c);
    cout << answer << "\n";

    return 0;
}
