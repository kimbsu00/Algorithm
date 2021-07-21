/*
url: https://programmers.co.kr/learn/courses/30/lessons/72410?language=cpp
*/

#include <string>
#include <vector>
#include <cmath>

using namespace std;

string solve(string new_id) {
    string ret;
    for(int i=0; i<new_id.size(); i++) {
        if('A'<=new_id[i] && new_id[i]<='Z')
            ret.append(1, 'a' + (new_id[i]-'A'));
        else if('a'<=new_id[i] && new_id[i]<='z')
            ret.append(1, new_id[i]);
        else if('0'<=new_id[i] && new_id[i] <='9')
            ret.append(1, new_id[i]);
        else if(new_id[i] == '-' || new_id[i] == '_' || new_id[i] == '.')
            ret.append(1, new_id[i]);
    }
    
    for(int i=ret.size()-1; i>=0; i--) {
        if(ret[i] == '.' && ret[i-1] == '.') {
            ret.erase(i, 1);
        }
    }
    
    if(ret[0] == '.') {
        ret.erase(0, 1);
    }
    if(ret[ret.size()-1] == '.') {
        ret.erase(ret.size()-1, 1);
    }
    
    if(ret == "") {
        ret = "a";
    }
    
    if(ret.size()>15) {
        ret = ret.substr(0,15);
    }
    for(int i=ret.size()-1; i>=0; i--) {
        if(ret[i] == '.') {
            ret.erase(i, 1);
        } else {
            break;
        }
    }
    
    if(ret.size()<3) {
        ret.append(3-ret.size(), ret[ret.size()-1]);
    }
    
    return ret;
}

string solution(string new_id) {
    string answer = solve(new_id);
    return answer;
}
