#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

int N, M;
int map[15][15];

int get_area_size(int size)
{
    return size * 4 + 1;
}

int check_range(int row, int col)
{
    return 0 <= row && row < N && 0 <= col && col < M;
}

int check_range(pair<int, int> pos)
{
    return check_range(pos.first, pos.second);
}

int solve(int row, int col, int cnt)
{
    if (row == N)
    {
        return cnt == 2 ? 1 : 0;
    }

    if (col == M)
    {
        return solve(row + 1, 0, cnt);
    }

    if (cnt == 2)
    {
        return 1;
    }

    int ret = solve(row, col + 1, cnt);
    int size = 0;
    while (true)
    {
        pair<int, int> left = {row, col - size};
        pair<int, int> top = {row - size, col};
        pair<int, int> right = {row, col + size};
        pair<int, int> bottom = {row + size, col};

        if (check_range(left) && check_range(top) && check_range(right) && check_range(bottom))
        {
            if (map[left.first][left.second] == 1 &&
                map[top.first][top.second] == 1 &&
                map[right.first][right.second] == 1 &&
                map[bottom.first][bottom.second] == 1)
            {
                map[left.first][left.second] = 0;
                map[top.first][top.second] = 0;
                map[right.first][right.second] = 0;
                map[bottom.first][bottom.second] = 0;
            }
            else
            {
                break;
            }
        }
        else
        {
            break;
        }
        size += 1;
    }
    size -= 1;

    while (size >= 0)
    {
        ret = max(ret, get_area_size(size) * solve(row, col + 1, cnt + 1));

        pair<int, int> left = {row, col - size};
        pair<int, int> top = {row - size, col};
        pair<int, int> right = {row, col + size};
        pair<int, int> bottom = {row + size, col};

        map[left.first][left.second] = 1;
        map[top.first][top.second] = 1;
        map[right.first][right.second] = 1;
        map[bottom.first][bottom.second] = 1;

        size -= 1;
    }

    return ret;
}

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    fill(&map[0][0], &map[14][15], -1);
    cin >> N >> M;

    string input;
    char ch;
    for (int row = 0; row < N; row++)
    {
        cin >> input;
        for (int col = 0; col < M; col++)
        {
            ch = input[col];

            if (ch == '#')
            {
                map[row][col] = 1;
            }
            else if (ch == '.')
            {
                map[row][col] = 0;
            }
        }
    }

    int answer = solve(0, 0, 0);
    printf("%d\n", answer);

    return 0;
}

/*
반례 모음

6 8
....#...
...##...
..#####.
...##...
....#...
........

7 7
...#...
...#...
...#...
#######
...####
...#.#.
...#...

5 8
..#..#..
..#..#..
########
..#..#..
..#..#..

3 3
.#.
###
.#.
*/
