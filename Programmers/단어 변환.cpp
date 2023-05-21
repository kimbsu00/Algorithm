#include <string>
#include <vector>

using namespace std;

vector<vector<int>> graph;
vector<bool> visited;

bool can_change(string& a, string& b) {
    int diff_cnt = 0;
    for (int idx=0; idx<a.length(); idx++) {
        if (a[idx] != b[idx]) {
            diff_cnt += 1;
        }
        
        if (diff_cnt > 1) {
            break;
        }
    }
    
    return (diff_cnt == 1);
}

void make_graph(vector<string>& words) {
    for (int idx=0; idx<words.size(); idx++) {
        for(int idx2=idx+1; idx2<words.size(); idx2++) {
            if (can_change(words[idx], words[idx2])) {
                graph[idx].push_back(idx2);
                graph[idx2].push_back(idx);
            }
        }
    }
}

bool check_input(string& target, vector<string>& words) {
    bool ret = false;
    
    for (int idx=0; idx<words.size(); idx++) {
        if (target == words[idx]) {
            ret = true;
            break;
        }
    }
    
    return ret;
}

int solve(int node, int sum, string& target, vector<string>& words) {
    if (words[node] == target) {
        return sum;
    }
    
    int ret = 987654321;
    visited[node] = true;
    for (int next: graph[node]) {
        if(!visited[next]) {
            ret = min(ret, solve(next, sum+1, target, words));
        }
    }
    visited[node] = false;
    
    return ret;
}

int solution(string begin, string target, vector<string> words) {
    if (!check_input(target, words)) {
        return 0;
    }
    
    graph = vector<vector<int>>(words.size(), vector<int>());
    visited = vector<bool>(words.size(), false);
    make_graph(words);
    
    int answer = 987654321;
    for (int idx=0; idx<words.size(); idx++) {
        string word = words[idx];
        
        if (can_change(begin, word)) {
            answer = min(answer, solve(idx, 1, target, words));
        }
    }
    
    return answer;
}
