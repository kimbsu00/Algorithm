#include <iostream>
#include <vector>

using namespace std;

enum Direction
{
    WEST,
    NORTH,
    EAST,
    SOUTH
};

int N, M;
int **map;
int **visited;
bool graph[2500][2500];
int answer[3] = {0, -1, -1};
vector<int> room;

bool can_move_to(int block, Direction dir)
{
    int ret = -1;

    switch (dir)
    {
    case WEST:
        ret = block & (1);
        break;
    case NORTH:
        ret = block & (1 << 1);
        break;
    case EAST:
        ret = block & (1 << 2);
        break;
    case SOUTH:
        ret = block & (1 << 3);
        break;
    }

    return ret == 0;
}

void solve(int row, int col, int room_idx)
{
    visited[row][col] = room_idx;
    room[room_idx] += 1;

    if (can_move_to(map[row][col], WEST))
    {
        if (visited[row][col - 1] == -1)
        {
            solve(row, col - 1, room_idx);
        }
    }
    else if (col > 0)
    {
        int adj_room_idx = visited[row][col - 1];
        if (adj_room_idx != -1)
        {
            graph[room_idx][adj_room_idx] = true;
        }
    }

    if (can_move_to(map[row][col], NORTH))
    {
        if (visited[row - 1][col] == -1)
        {
            solve(row - 1, col, room_idx);
        }
    }
    else if (row > 0)
    {
        int adj_room_idx = visited[row - 1][col];
        if (adj_room_idx != -1)
        {
            graph[room_idx][adj_room_idx] = true;
        }
    }

    if (can_move_to(map[row][col], EAST))
    {
        if (visited[row][col + 1] == -1)
        {
            solve(row, col + 1, room_idx);
        }
    }
    else if (col < N - 1)
    {
        int adj_room_idx = visited[row][col + 1];
        if (adj_room_idx != -1)
        {
            graph[room_idx][adj_room_idx] = true;
        }
    }

    if (can_move_to(map[row][col], SOUTH))
    {
        if (visited[row + 1][col] == -1)
        {
            solve(row + 1, col, room_idx);
        }
    }
    else if (row < M - 1)
    {
        int adj_room_idx = visited[row + 1][col];
        if (adj_room_idx != -1)
        {
            graph[room_idx][adj_room_idx] = true;
        }
    }
}

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> N >> M;

    map = new int *[M];
    visited = new int *[M];
    for (int idx = 0; idx < M; idx++)
    {
        map[idx] = new int[N];
        visited[idx] = new int[N];
    }

    for (int row = 0; row < M; row++)
    {
        for (int col = 0; col < N; col++)
        {
            cin >> map[row][col];
            visited[row][col] = -1;
        }
    }

    fill(&graph[0][0], &graph[2499][2500], false);

    for (int row = 0; row < M; row++)
    {
        for (int col = 0; col < N; col++)
        {
            if (visited[row][col] == -1)
            {
                room.push_back(0);
                solve(row, col, room.size() - 1);
            }
        }
    }

    answer[0] = room.size();
    for (int idx = 0; idx < room.size(); idx++)
    {
        answer[1] = max(answer[1], room[idx]);
        for (int other = 0; other < room.size(); other++)
        {
            if (idx != other && graph[idx][other])
            {
                answer[2] = max(answer[2], room[idx] + room[other]);
            }
        }
    }

    cout << answer[0] << "\n"
         << answer[1] << "\n"
         << answer[2] << "\n";

    return 0;
}
