/*
url: https://programmers.co.kr/learn/courses/30/lessons/72411?language=cpp
*/

#include <string>
#include <vector>
#include <algorithm>

using namespace std;

/*
setMenu[index] == 포함된 단품 메뉴의 개수가 index인 코스 요리들의 집합
pair<string,int> == <코스요리,주문횟수>
*/
vector<pair<string,int>> setMenu[11];

// order로 만들 수 있는 모든 메뉴조합을 setMenu에 저장하는 함수
void solve(string menu, string& order, int index) {
    if(index == order.size()) {
        // 코스 요리에 포함된 단품 요리의 개수가 2개 미만인 경우는 바로 종료함.
        if(menu.size() < 2)            return;
        
        // num은 코스 요리 menu에 포함된 단품 메뉴의 개수를 의미함.
        int num = menu.size();
        bool flag = false;
        // 이전에 추가된 적 있는 코스 요리인지 확인해보고
        for(int i=0; i<setMenu[num].size(); i++) {
            // 이전에 추가된 적 있는 코스 요리라면,
            if(setMenu[num][i].first == menu) {
                flag = true;
                // 주문 횟수만 +1 해주면 된다.
                setMenu[num][i].second++;
                break;
            }
        }
        // 이전에 추가된 적 없는 코스 요리라면,
        if(!flag) {
            // 새로 추가하면 된다.
            setMenu[num].push_back({menu, 1});
        }
        return;
    }
    
    // 코스요리에 index번째 요리를 추가하지 않는 경우에 대한 재귀호출
    solve(menu, order, index+1);
    // 코스요리에 index번째 요리를 추가하는 경우에 대한 재귀호출
    solve(menu.append(1, order[index]), order, index+1);
    return;
}

bool compare(const pair<string,int>& a, const pair<string,int>& b) {
    return a.second>b.second;
}

vector<string> solution(vector<string> orders, vector<int> course) {
    vector<string> answer;
    
    // 전처리 작업으로 정렬해준다.
    // 조합을 구할 예정이므로, 메뉴의 순서는 상관이 없다.
    for(int i=0; i<orders.size(); i++) {
        sort(orders[i].begin(), orders[i].end());
    }
    
    // orders[i]로 만들 수 있는 모든 메뉴 조합을 만든다.
    for(int i=0;i<orders.size(); i++) {
        solve("", orders[i], 0);
    }
    
    for(int i=0; i<course.size(); i++) {
        int num = course[i];
        // 주문 횟수에 대하여 내림차순 정렬해준다.
        sort(setMenu[num].begin(), setMenu[num].end(), compare);
        
        for(int j=0; j<setMenu[num].size(); j++) {
            // 주문 횟수가 2회 미만이면 중단한다.
            if(setMenu[num][j].second < 2)          break;
            
            // 주문 횟수가 제일 많은 코스 요리는 바로 추가해주고
            if(j==0) {
                answer.push_back(setMenu[num][j].first);
            } 
            // 그 다음부터는 이전 코스 요리와 주문 횟수가 같은 경우에 대해서만 추가해주면 된다.
            else {
                if(setMenu[num][j].second < setMenu[num][j-1].second)         break;
                answer.push_back(setMenu[num][j].first);
            }
        }
    }
    // 마지막으로 오름차순 정렬만 하면 끝.
    sort(answer.begin(), answer.end());
    
    return answer;
}
