#include <vector>
#include <string>
#include <map>

using namespace std;

map<string, int> name_map;
vector<int> parent;

void solve(int node, int dividend, vector<int> &answer)
{
    if (node == -1)
    {
        return;
    }

    int for_parent = dividend * 0.1;
    int mine = dividend - for_parent;
    answer[node] += mine;
    solve(parent[node], for_parent, answer);
}

/**
 * @param enroll    판매원의 이름
 * @param referral  판매원을 다단계 조직에 참여시킨 다른 판매원의 이름 -> referral[idx]는 enroll[idx]의 parent
 * @param seller    판매량 집계 데이터의 판매원 이름
 * @param amount    판매량 집계 데이터의 판매 수량 -> amount[idx]는 seller[idx]가 판매한 수량
 */
vector<int> solution(vector<string> enroll, vector<string> referral, vector<string> seller, vector<int> amount)
{
    parent.resize(enroll.size(), -1);
    for (int idx = 0; idx < enroll.size(); idx++)
    {
        string name = enroll[idx];
        name_map.insert({name, idx});
    }

    for (int idx = 0; idx < referral.size(); idx++)
    {
        string parent_name = referral[idx];
        string child_name = enroll[idx];

        if (parent_name != "-")
        {
            int parent_idx = name_map[parent_name];
            int child_idx = name_map[child_name];
            parent[child_idx] = parent_idx;
        }
    }

    vector<int> answer(enroll.size(), 0);
    for (int idx = 0; idx < seller.size(); idx++)
    {
        string name = seller[idx];
        int name_idx = name_map[name];
        int cnt = amount[idx];

        solve(name_idx, cnt * 100, answer);
    }
    return answer;
}
