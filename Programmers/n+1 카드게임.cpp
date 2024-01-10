#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <queue>

using namespace std;

int target_num = -1;

int solve(int coin_cnt, int can_go_next, vector<int> &need_coin)
{
    priority_queue<int> pq;

    int round = 1;
    int init_cnt = need_coin.size() / 3;
    int idx = init_cnt;

    while (true)
    {
        if (idx < need_coin.size())
        {
            int left = need_coin[idx];
            int right = need_coin[idx + 1];
            idx += 2;

            if (left != -1)
                pq.push(-left);
            if (right != -1)
                pq.push(-right);
        }

        if (can_go_next > 0)
        {
            can_go_next -= 1;
        }
        else
        {
            if (!pq.empty())
            {
                int need = -pq.top();

                if (coin_cnt >= need)
                {
                    pq.pop();
                    coin_cnt -= need;
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
        }

        round += 1;
    }

    int max_round = (need_coin.size() - init_cnt) / 2 + 1;
    if (round > max_round)
    {
        round = max_round;
    }
    return round;
}

int solution(int coin, vector<int> cards)
{
    int init_cnt = cards.size() / 3;
    target_num = cards.size() + 1;

    map<int, int> idx_map;
    for (int idx = 0; idx < cards.size(); idx++)
    {
        idx_map.insert({cards[idx], idx});
    }

    vector<int> need_coin(cards.size(), -1);
    for (int idx = 0; idx < cards.size(); idx++)
    {
        int pair = target_num - cards[idx];
        int pair_idx = idx_map.find(pair)->second;

        if (idx < pair_idx)
        {
            if (idx >= init_cnt)
            {
                need_coin[pair_idx] = 2;
            }
            else if (pair_idx >= init_cnt)
            {
                need_coin[pair_idx] = 1;
            }
            else
            {
                need_coin[pair_idx] = 0;
            }
        }
    }

    int can_go_next = 0;
    for (int idx = 0; idx < init_cnt; idx++)
    {
        if (need_coin[idx] >= 0)
        {
            can_go_next += 1;
        }
    }

    int answer = solve(coin, can_go_next, need_coin);
    return answer;
}

int main(void)
{
    int coin = 4;
    vector<int> cards({3, 6, 7, 2, 1, 10, 5, 9, 8, 12, 11, 4});
    // vector<int> cards({1, 2, 3, 4, 5, 8, 6, 7, 9, 10, 11, 12});
    int answer = solution(coin, cards);
    printf("%d\n", answer);

    return 0;
}
