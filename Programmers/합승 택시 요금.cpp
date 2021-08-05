/*
url: https://programmers.co.kr/learn/courses/30/lessons/72413?language=cpp
*/

#include <string>
#include <vector>
#include <algorithm>

using namespace std;

const int INF = 12345678;
int N;
vector<vector<int>> dist;

void floyd_warshall() {
    for(int i=0; i<N; i++) {
        dist[i][i] = 0;
    }
    
    for(int k=0; k<N; k++) {
        for(int i=0; i<N; i++) {
            for(int j=0; j<N; j++) {                
                dist[i][j] = min(dist[i][j], dist[i][k]+dist[k][j]);
            }
        }
    }
}

int solution(int n, int s, int a, int b, vector<vector<int>> fares) {
    int answer = INF;    
    
    s--, a--, b--;
    N=n;
    dist = vector<vector<int>>(n, vector<int>(n, INF));
    
    for(int i=0; i<fares.size(); i++) {
        int c = fares[i][0];
        int d = fares[i][1];
        int f = fares[i][2];
        c--, d--;
        dist[c][d] = f;
        dist[d][c] = f;
    }
    floyd_warshall();
    
    for(int i=0; i<n; i++) {
        answer = min(answer, dist[s][i]+dist[i][a]+dist[i][b]);
    }
    
    return answer;
}
