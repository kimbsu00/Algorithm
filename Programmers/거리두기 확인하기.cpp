/*
url: https://programmers.co.kr/learn/courses/30/lessons/81302?language=cpp
*/

#include <string>
#include <vector>

using namespace std;

int solve(vector<string>& place);
bool check(int x, int y, vector<string>& place);

vector<int> solution(vector<vector<string>> places) {
    vector<int> answer;
    
    // 전처리 작업
    // 5*5 사이즈의 대기실을 7*7 사이즈로 변경함.
    for(int i=0; i<5; i++) {
        for(int j=0; j<5; j++) {
            places[i][j].append("00");
        }
        places[i].push_back("0000000");
        places[i].push_back("0000000");
    }
    for(int i=0; i<5; i++) {
        answer.push_back(solve(places[i]));
    }
    
    return answer;
}

// 대기실 place가 거리두기를 지키고 있다면 1, 그렇지 않다면 2를 리턴함.
int solve(vector<string>& place) {
    int ret = 1;
    
    for(int x=0; x<5; x++) {
        for(int y=0; y<5; y++) {
            if(place[x][y] == 'P') {
                if(!check(x, y, place)) {
                    ret = 0;
                    return ret;
                }
            }
        }
    }
    return ret;
}

// place(x, y)에 대하여, 거리두기를 지키고 있다면 true, 그렇지 않다면 false를 리턴함.
bool check(int x, int y, vector<string>& place) {
    if(place[x+1][y] == 'P' || place[x][y+1] == 'P')
        return false;
    
    if(place[x+2][y] == 'P' && place[x+1][y] != 'X')
        return false;
    
    if(place[x][y+2] == 'P' && place[x][y+1] != 'X')
        return false;
    
    if(place[x+1][y+1] == 'P' && !(place[x+1][y] == 'X' && place[x][y+1] == 'X'))
        return false;
    
    if(place[x+1][y-1] == 'P' && !(place[x+1][y] == 'X' && place[x][y-1] == 'X'))
        return false;
    
    return true;
}
