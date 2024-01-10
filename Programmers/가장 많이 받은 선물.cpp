#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <sstream>
#include <algorithm>

using namespace std;

map<string, int> name_to_idx;
vector<vector<int>> directed_graph;
vector<int> gift_num;

vector<string> split(string input, char delimiter)
{
    vector<string> answer;
    stringstream ss(input);
    string temp;

    while (getline(ss, temp, delimiter))
    {
        answer.push_back(temp);
    }

    return answer;
}

int solution(vector<string> friends, vector<string> gifts)
{
    int answer = 0;

    int friend_cnt = friends.size();
    for (int idx = 0; idx < friend_cnt; idx++)
    {
        name_to_idx.insert({friends[idx], idx});
    }

    gift_num = vector<int>(friend_cnt, 0);
    directed_graph = vector<vector<int>>(friend_cnt, vector<int>(friend_cnt, 0));

    for (int idx = 0; idx < gifts.size(); idx++)
    {
        vector<string> gift = split(gifts[idx], ' ');

        int idx_a = name_to_idx.find(gift[0])->second;
        int idx_b = name_to_idx.find(gift[1])->second;

        gift_num[idx_a] += 1;
        gift_num[idx_b] -= 1;
        directed_graph[idx_a][idx_b] += 1;
    }

    vector<int> next_month_gift(friend_cnt, 0);
    for (int a = 0; a < friend_cnt; a++)
    {
        for (int b = a + 1; b < friend_cnt; b++)
        {
            // 주고 받은 선물 기록이 있는 경우
            if ((directed_graph[a][b] > 0 || directed_graph[b][a] > 0) && (directed_graph[a][b] != directed_graph[b][a]))
            {
                // 선물을 더 많이 준 친구가 선물을 받음
                if (directed_graph[a][b] > directed_graph[b][a])
                {
                    next_month_gift[a] += 1;
                }
                else if (directed_graph[a][b] < directed_graph[b][a])
                {
                    next_month_gift[b] += 1;
                }
            }
            // 주고 받은 선물 기록이 없는 경우 || 주고 받은 선물의 개수가 같은 경우
            else
            {
                if (gift_num[a] > gift_num[b])
                {
                    next_month_gift[a] += 1;
                }
                else if (gift_num[a] < gift_num[b])
                {
                    next_month_gift[b] += 1;
                }
            }
        }
    }

    for (int idx = 0; idx < next_month_gift.size(); idx++)
    {
        answer = max(answer, next_month_gift[idx]);
    }

    return answer;
}

int main()
{

    return 0;
}
