/*
url: https://programmers.co.kr/learn/courses/30/lessons/72412
*/

#include <string>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;

vector<int> application[4][3][3][3];

vector<string> split(string input, char delimiter) {
    vector<string> answer;
    stringstream ss(input);
    string temp;
 
    while (getline(ss, temp, delimiter)) {
        answer.push_back(temp);
    }
 
    return answer;
}

bool compare(const int& a, const int& b) {
    return a<b;
}

vector<int> solution(vector<string> info, vector<string> query) {
    vector<int> answer;
    
    for(int i=0; i<info.size(); i++) {
        vector<string> temp = split(info[i], ' ');
        
        int score = stoi(temp[4]);
        int a[2];
        int b[2];
        int c[2];
        int d[2];
        /*
        cpp = 0
        java = 1
        python = 2
        - = 3
        */
        if(temp[0] == "cpp") {
            a[0]=0, a[1]=3;
        } else if(temp[0] == "java") {
            a[0]=1, a[1]=3;
        } else {
            a[0]=2, a[1]=3;
        }
        
        /*
        backend = 0
        frontend = 1
        - = 2
        */
        if(temp[1] == "backend") {
            b[0]=0, b[1]=2;
        } else {
            b[0]=1, b[1]=2;
        }
        
        /*
        junior = 0
        senior = 1
        - = 2
        */
        if(temp[2] == "junior") {
            c[0]=0, c[1]=2;
        } else {
            c[0]=1, c[1]=2;
        }
        
        /*
        chicken = 0
        pizza = 1
        - = 2
        */
        if(temp[3] == "chicken") {
            d[0]=0, d[1]=2;
        } else {
            d[0]=1, d[1]=2;
        }
        
        // info[i]가 포함될 수 있는 모든 집합에 score를 추가한다.
        for(int A=0; A<2; A++) {
            for(int B=0; B<2; B++) {
                for(int C=0; C<2; C++) {
                    for(int D=0; D<2; D++) {
                        application[a[A]][b[B]][c[C]][d[D]].push_back(score);
                    }
                }
            }
        }
    }
    
    // 모든 집합을 점수를 기준으로 오름차순 정렬한다.
    for(int A=0; A<4; A++) {
        for(int B=0; B<3; B++) {
            for(int C=0; C<3; C++) {
                for(int D=0; D<3; D++) {
                    sort(application[A][B][C][D].begin(), application[A][B][C][D].end(), compare);
                }
            }
        }
    }
    
    for(int i=0; i<query.size(); i++) {
        vector<string> temp = split(query[i], ' ');
        
        int score = stoi(temp[7]);
        int a,b,c,d;
        // query[i]에서 개발언어 조건을 확인한다.
        if(temp[0] == "cpp") {
            a=0;
        } else if(temp[0] == "java") {
            a=1;
        } else if(temp[0] == "python") {
            a=2;
        } else {
            a=3;
        }
        // query[i]에서 직군 조건을 확인한다.
        if(temp[2] == "backend") {
            b=0;
        } else if(temp[2] == "frontend") {
            b=1;
        } else {
            b=2;
        }
        // query[i]에서 경력 조건을 확인한다.
        if(temp[4] == "junior") {
            c=0;
        } else if(temp[4] == "senior") {
            c=1;
        } else {
            c=2;
        }
        // query[i]에서 소울푸드 조건을 확인한다.
        if(temp[6] == "chicken") {
            d=0;
        } else if(temp[6] == "pizza") {
            d=1;
        } else {
            d=2;
        }
        
        /*
        조건에 해당하는 집합에서 lower_bound 함수를 사용해서
        score 이상인 원소들 중에서 가장 작은 원소의 인덱스를 계산한다.
        http://www.cplusplus.com/reference/algorithm/lower_bound/
        */
        int index = lower_bound(application[a][b][c][d].begin(),application[a][b][c][d].end(),score)-application[a][b][c][d].begin();
        int size = application[a][b][c][d].size();
        // (집합의 size - index)가 정답이 된다.
        answer.push_back(size-index);
    }
    
    return answer;
}
