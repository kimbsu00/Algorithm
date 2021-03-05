/*
  url: https://codeforces.com/problemset/problem/71/A
*/

#include<iostream>
#include<string>
#include<vector>
 
using namespace std;
 
int main(void) {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
 
    int N;
    cin >> N;
    vector<string> input = vector<string>(N);
    vector<string> answer = vector<string>(N);
    for (int i = 0; i < N; i++) {
        cin >> input[i];
 
        if (input[i].size() > 10) {
            
            answer[i] = input[i][0] + to_string(input[i].size() - 2) + input[i][input[i].size() - 1];
        }
        else {
            answer[i] = input[i];
        }
    }
 
    for (string output : answer) {
        cout << output << "\n";
    }
 
    return 0;
}
