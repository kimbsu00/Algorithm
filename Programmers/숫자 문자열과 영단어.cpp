/*
url: https://programmers.co.kr/learn/courses/30/lessons/81301?language=cpp
*/

#include <string>
#include <cmath>
#include <vector>

using namespace std;

vector<int> solve(string& s) {
    vector<int> ret;
    for(int i=0; i<s.size(); i++) {
        switch(s[i]) {
            case 'z':
                ret.push_back(0);
                i+=3;
                break;
            case 'o':
                ret.push_back(1);
                i+=2;
                break;
            case 't':
                if(s[i+1] == 'w') {
                    ret.push_back(2);
                    i+=2;
                } else {
                    ret.push_back(3);
                    i+=4;
                }
                break;
            case 'f':
                if(s[i+1] == 'o') {
                    ret.push_back(4);
                } else {
                    ret.push_back(5);
                }
                i+=3;
                break;
            case 's':
                if(s[i+1] == 'i') {
                    ret.push_back(6);
                    i+=2;
                } else {
                    ret.push_back(7);
                    i+=4;
                }
                break;
            case 'e':
                ret.push_back(8);
                i+=4;
                break;
            case 'n':
                ret.push_back(9);
                i+=3;
                break;
            case '0':
                ret.push_back(0);
                break;
            case '1':
                ret.push_back(1);
                break;
            case '2':
                ret.push_back(2);
                break;
            case '3':
                ret.push_back(3);
                break;
            case '4':
                ret.push_back(4);
                break;
            case '5':
                ret.push_back(5);
                break;
            case '6':
                ret.push_back(6);
                break;
            case '7':
                ret.push_back(7);
                break;
            case '8':
                ret.push_back(8);
                break;
            case '9':
                ret.push_back(9);
                break;
            default:
                break;
        }
    }
    return ret;
}

int makeDecimalNumber(vector<int>& numbers) {
    int ret = 0;
    for(int i=0; i<numbers.size(); i++) {
        ret += numbers[i]*pow(10,(numbers.size()-i-1));
    }
    return ret;
}

int solution(string s) {
    int answer = 0;
    
    vector<int> numbers = solve(s);
    answer = makeDecimalNumber(numbers);
    
    return answer;
}
