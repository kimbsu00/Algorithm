#include <iostream>
#include <vector>
#include <queue>
#include <string>

using namespace std;

enum Flag
{
    EMPTY,
    START,
    FLOWER,
    GARBAGE
};

struct Node
{
    int row, col, garbage_cnt, garbage_nearby_cnt;
} typedef node;

struct CompareNode
{
    bool operator()(const Node &left, const Node &right)
    {
        if (left.garbage_cnt == right.garbage_cnt)
        {
            return left.garbage_nearby_cnt > right.garbage_nearby_cnt;
        }
        else
        {
            return left.garbage_cnt > right.garbage_cnt;
        }
    }
};

// left, top, right, bottom
const int dr[4] = {0, -1, 0, 1};
const int dc[4] = {-1, 0, 1, 0};
const int MAX = 987654321;

int N, M;
vector<vector<int>> map;
vector<vector<int>> garbage_nearby_flag;

void print_2d_vec(vector<vector<int>> &vec)
{
    for (int row = 0; row < N; row++)
    {
        for (int col = 0; col < M; col++)
        {
            printf("%d ", vec[row][col]);
        }
        printf("\n");
    }
}

bool compare(const pair<int, int> &left, const pair<int, int> &right)
{
    if (left.first == right.first)
    {
        return left.second < right.second;
    }
    else
    {
        return left.first < right.first;
    }
}

bool check_range(int row, int col)
{
    return 0 <= row && row < N && 0 <= col && col < M;
}

int coord_to_idx(int row, int col)
{
    return row * M + col;
}

pair<int, int> solve(int start_row, int start_col, int dest_row, int dest_col)
{
    priority_queue<Node, vector<Node>, CompareNode> pq;
    pq.push({start_row, start_col, 0, 0});

    vector<pair<int, int>> dist(N * M, {MAX, MAX});
    while (!pq.empty())
    {
        node top = pq.top();
        pq.pop();

        int node_idx = coord_to_idx(top.row, top.col);
        pair<int, int> p = {top.garbage_cnt, top.garbage_nearby_cnt};
        if (compare(dist[node_idx], p))
        {
            continue;
        }

        int next_garbage_nearby_cnt = top.garbage_nearby_cnt;
        if (garbage_nearby_flag[top.row][top.col] > 0)
        {
            next_garbage_nearby_cnt += 1;
        }

        for (int idx = 0; idx < 4; idx++)
        {
            int next_row = top.row + dr[idx];
            int next_col = top.col + dc[idx];

            if (check_range(next_row, next_col))
            {
                pair<int, int> cost;
                if (map[next_row][next_col] == GARBAGE)
                {
                    cost = {top.garbage_cnt + 1, next_garbage_nearby_cnt};
                }
                else
                {
                    cost = {top.garbage_cnt, next_garbage_nearby_cnt};
                }

                int next_node_idx = coord_to_idx(next_row, next_col);
                if (compare(cost, dist[next_node_idx]))
                {
                    dist[next_node_idx] = cost;
                    pq.push({next_row, next_col, cost.first, cost.second});
                }
            }
        }
    }

    int dest_node_idx = coord_to_idx(dest_row, dest_col);
    return dist[dest_node_idx];
}

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> N >> M;
    map = vector<vector<int>>(N, vector<int>(M, EMPTY));
    garbage_nearby_flag = vector<vector<int>>(N, vector<int>(M, 0));

    string input;
    int start_row, start_col, dest_row, dest_col;
    for (int row = 0; row < N; row++)
    {
        cin >> input;
        for (int col = 0; col < M; col++)
        {
            char ch = input[col];

            // 빈칸
            if (ch == '.')
            {
                map[row][col] = EMPTY;
            }
            // 시작
            else if (ch == 'S')
            {
                map[row][col] = START;
                start_row = row;
                start_col = col;
            }
            // 도착
            else if (ch == 'F')
            {
                map[row][col] = FLOWER;
                dest_row = row;
                dest_col = col;
            }
            // 쓰레기
            else if (ch == 'g')
            {
                map[row][col] = GARBAGE;
            }
        }
    }

    for (int row = 0; row < N; row++)
    {
        for (int col = 0; col < M; col++)
        {
            if (map[row][col] == GARBAGE)
            {
                for (int idx = 0; idx < 4; idx++)
                {
                    int next_row = row + dr[idx];
                    int next_col = col + dc[idx];

                    if (check_range(next_row, next_col) && map[next_row][next_col] == EMPTY)
                    {
                        garbage_nearby_flag[next_row][next_col] = 1;
                    }
                }
            }
        }
    }

    pair<int, int> answer = solve(start_row, start_col, dest_row, dest_col);
    printf("%d %d\n", answer.first, answer.second);

    return 0;
}

/*
반례 모음

6 6
......
g..F..
......
gggggg
......
...S.g

answer: 1 2


3 3
Fgg
gSg
ggg

answer: 1 0
*/
