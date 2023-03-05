#include <string>
#include <vector>

using namespace std;

const int discount[4] = {10, 20, 30, 40};

pair<int, int> solve(vector<vector<int>>& users, vector<int>& emoticons, int emo_idx) {
    int apply_cnt = 0;
    int earn = 0;
    
    if (emo_idx >= emoticons.size()) {
        for (int user_idx=0; user_idx<users.size(); user_idx++) {
            int threshold = users[user_idx][1];
            int total_price = users[user_idx][2];
            
            if (threshold <= total_price) {
                apply_cnt += 1;
            }
            else {
                earn += total_price;
            }
        }
        
        return {apply_cnt, earn};
    }
    
    for (int idx=0; idx<4; idx++) {
        int price = emoticons[emo_idx] * (100 - discount[idx]) * 0.01;
        
        for (int user_idx=0; user_idx<users.size(); user_idx++) {
            if (users[user_idx][0] <= discount[idx]) {
                users[user_idx][2] += price;
            }
        }
        
        pair<int, int> tmp = solve(users, emoticons, emo_idx+1);
        if ((tmp.first > apply_cnt) || ((tmp.first == apply_cnt) && (tmp.second > earn))) {
            apply_cnt = tmp.first;
            earn = tmp.second;
        }
        
        for (int user_idx=0; user_idx<users.size(); user_idx++) {
            if (users[user_idx][0] <= discount[idx]) {
                users[user_idx][2] -= price;
            }
        }
    }
    
    return {apply_cnt, earn};
}

vector<int> solution(vector<vector<int>> users, vector<int> emoticons) {
    vector<int> answer;
    
    for (int idx=0; idx<users.size(); idx++) {
        users[idx].push_back(0);
    }
    
    pair<int, int> ans = solve(users, emoticons, 0);
    answer.push_back(ans.first);
    answer.push_back(ans.second);
    
    return answer;
}
