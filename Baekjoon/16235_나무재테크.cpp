#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// T, LT, L, LB, B, RB, R, RT
const int dr[8] = {-1, -1, 0, 1, 1, 1, 0, -1};
const int dc[8] = {0, -1, -1, -1, 0, 1, 1, 1};

int N, M, K;
int s2d2[10][10];
int energy[10][10];
vector<int> map[10][10];

bool compare(pair<int, pair<int, int>> &left, pair<int, pair<int, int>> &right)
{
    return left.first > right.first;
}

void spring_and_summer(int row, int col)
{
    int dead_energy = 0;

    // Spring
    int tree_cnt = map[row][col].size();
    for (int idx = tree_cnt - 1; idx >= 0; idx--)
    {
        int age = map[row][col][idx];

        if (energy[row][col] >= age)
        {
            energy[row][col] -= age;
            map[row][col][idx] += 1;
        }
        else
        {
            dead_energy += (int)(age / 2);
            map[row][col].erase(map[row][col].begin() + idx);
        }
    }

    // Summer
    if (row != -1 && col != -1)
    {
        energy[row][col] += dead_energy;
    }
}

void autumn(int row, int col)
{
    for (int age : map[row][col])
    {
        if (age % 5 == 0)
        {
            for (int idx = 0; idx < 8; idx++)
            {
                int new_row = row + dr[idx];
                int new_col = col + dc[idx];

                if (0 <= new_row && new_row < N && 0 <= new_col && new_col < N)
                {
                    map[new_row][new_col].push_back(1);
                }
            }
        }
    }
}

void winter()
{
    for (int row = 0; row < N; row++)
    {
        for (int col = 0; col < N; col++)
        {
            energy[row][col] += s2d2[row][col];
        }
    }
}

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    fill(&energy[0][0], &energy[9][10], 5);

    cin >> N >> M >> K;

    for (int row = 0; row < N; row++)
    {
        for (int col = 0; col < N; col++)
        {
            cin >> s2d2[row][col];
        }
    }

    int row, col, age;
    for (int idx = 0; idx < M; idx++)
    {
        cin >> row >> col >> age;
        row -= 1;
        col -= 1;

        map[row][col].push_back(age);
    }

    for (int row = 0; row < N; row++)
    {
        for (int col = 0; col < N; col++)
        {
            sort(map[row][col].begin(), map[row][col].end(), greater<int>());
        }
    }

    while (K--)
    {
        for (int row = 0; row < N; row++)
        {
            for (int col = 0; col < N; col++)
            {
                spring_and_summer(row, col);
            }
        }
        for (int row = 0; row < N; row++)
        {
            for (int col = 0; col < N; col++)
            {
                autumn(row, col);
            }
        }
        winter();
    }

    int answer = 0;
    for (int row = 0; row < N; row++)
    {
        for (int col = 0; col < N; col++)
        {
            answer += map[row][col].size();
        }
    }
    printf("%d\n", answer);

    return 0;
}
