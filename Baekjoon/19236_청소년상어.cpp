#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;

struct Fish
{
    int idx, row, col, dir, alive;
};

/**
 * 0 -> Top
 * 1 -> Left Top
 * 2 -> Left
 * 3 -> Left Bottom
 * 4 -> Bottom
 * 5 -> Right Bottom
 * 6 -> Right
 * 7 -> Right Top
 */
const int dr[8] = {-1, -1, 0, 1, 1, 1, 0, -1};
const int dc[8] = {0, -1, -1, -1, 0, 1, 1, 1};

void print_map(vector<vector<int>> &map, Fish *fish, Fish &shark)
{
    for (int row = 0; row < map.size(); row++)
    {
        for (int col = 0; col < map[row].size(); col++)
        {
            if (map[row][col] >= 0)
            {
                printf("%d / %d\t", map[row][col], fish[map[row][col]].dir);
            }
            else if (map[row][col] == -1)
            {
                printf("%d / %d\t", map[row][col], shark.dir);
            }
            else
            {
                printf("\t");
            }
        }
        printf("\n");
    }

    printf("\n\n");
}

bool check_range(int row, int col)
{
    return (0 <= row) && (row < 4) && (0 <= col) && (col < 4);
}

void move_fish(Fish *fish, vector<vector<int>> &map)
{
    for (int idx = 0; idx < 16; idx++)
    {
        Fish &cur_fish = fish[idx];

        if (cur_fish.alive)
        {
            int cnt = 0;
            int dir = cur_fish.dir;
            int next_row = cur_fish.row + dr[dir];
            int next_col = cur_fish.col + dc[dir];

            while ((!check_range(next_row, next_col) || map[next_row][next_col] == -1) && cnt < 8)
            {
                dir = (dir + 1) % 8;
                next_row = cur_fish.row + dr[dir];
                next_col = cur_fish.col + dc[dir];

                cnt += 1;
            }

            if (cnt < 8)
            {
                cur_fish.dir = dir;

                int next_fish_idx = map[next_row][next_col];
                if (next_fish_idx >= 0)
                {
                    Fish &next_fish = fish[next_fish_idx];

                    map[cur_fish.row][cur_fish.col] = next_fish.idx;
                    next_fish.row = cur_fish.row;
                    next_fish.col = cur_fish.col;
                }
                else
                {
                    map[cur_fish.row][cur_fish.col] = -100;
                }

                map[next_row][next_col] = cur_fish.idx;
                cur_fish.row = next_row;
                cur_fish.col = next_col;
            }
        }
    }
}

int solve(Fish shark, Fish fish[16], vector<vector<int>> map, int sum)
{
    // printf("Before move_fish\n");
    // print_map(map, fish, shark);
    move_fish(fish, map);
    // printf("After move_fish\n");
    // print_map(map, fish, shark);
    // getchar();

    int dir = shark.dir;
    int range = 1;
    int next_row = shark.row + dr[dir] * range;
    int next_col = shark.col + dc[dir] * range;

    int origin_row = shark.row;
    int origin_col = shark.col;

    int ret = sum;
    while (check_range(next_row, next_col))
    {
        if (map[next_row][next_col] >= 0)
        {
            Fish &eat_fish = fish[map[next_row][next_col]];
            eat_fish.alive = false;

            map[origin_row][origin_col] = -100;
            map[next_row][next_col] = -1;

            shark.row = eat_fish.row;
            shark.col = eat_fish.col;
            shark.dir = eat_fish.dir;

            Fish copy_fish[16];
            for (int idx = 0; idx < 16; idx++)
            {
                copy_fish[idx] = Fish({fish[idx].idx, fish[idx].row, fish[idx].col, fish[idx].dir, fish[idx].alive});
            }

            ret = max(ret, solve(shark, copy_fish, map, sum + eat_fish.idx + 1));
            // printf("ret=%d\n", ret);

            shark.row = origin_row;
            shark.col = origin_col;
            shark.dir = dir;

            eat_fish.alive = true;
            map[origin_row][origin_col] = -1;
            map[next_row][next_col] = eat_fish.idx;

            // print_map(map, fish, shark);
        }

        next_row = shark.row + dr[dir] * range;
        next_col = shark.col + dc[dir] * range;
        range += 1;
    }

    return ret;
}

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    vector<vector<int>> map(4, vector<int>(4, 0));
    Fish fish[16];
    int a, b;
    for (int row = 0; row < 4; row++)
    {
        for (int col = 0; col < 4; col++)
        {
            cin >> a >> b;
            a -= 1;
            b -= 1;

            Fish new_fish({a, row, col, b, true});
            map[row][col] = a;
            fish[a] = new_fish;
        }
    }

    Fish &appetizer = fish[map[0][0]];
    appetizer.alive = false;
    map[0][0] = -1;
    Fish shark({-1, 0, 0, appetizer.dir, true});

    // print_map(map, fish, shark);
    int answer = solve(shark, fish, map, appetizer.idx + 1);
    printf("%d\n", answer);

    return 0;
}
