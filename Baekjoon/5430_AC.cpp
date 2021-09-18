/*
  url: https://www.acmicpc.net/problem/5430
*/

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
​
using namespace std;
​
vector<string> split(string input, char delimiter) {
    vector<string> answer;
    stringstream ss(input);
    string temp;
​
    while (getline(ss, temp, delimiter)) {
        answer.push_back(temp);
    }
​
    return answer;
}
​
vector<int> solve(string& p, vector<int>& nums) {
    vector<int> ret;
    int left = 0;
    int right = nums.size();
​
    /*
    * true -> 앞에서 숫자를 하나 버린다.
    * false -> 뒤에서 숫자를 하나 버린다.
    */
    bool flag = true;
    for (int i = 0; i < p.size(); i++) {
        if (p[i] == 'R') {
            flag = !flag;
        }
        else if (p[i] == 'D') {
            if (flag) {
                left++;
            }
            else {
                right--;
            }
​
            if (left > right) {
                ret.push_back(-1);
                return ret;
            }
        }
    }
​
    if (!nums.empty()) {
        if (flag) {
            for (int i = left; i < right; i++) {
                ret.push_back(nums[i]);
            }
        }
        else {
            for (int i = right - 1; i >= left; i--) {
                ret.push_back(nums[i]);
            }
        }
    }
    return ret;
}
​
int main(void) {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
​
    int T;
    cin >> T;
    for (int i = 0; i < T; i++) {
        string p, list;
        int n;
        cin >> p >> n >> list;
​
        list = list.substr(1, list.size() - 2);
        vector<string> num = split(list, ',');
        vector<int> nums;
        for (int j = 0; j < num.size(); j++) {
            nums.push_back(stoi(num[j]));
        }
​
        vector<int> ans = solve(p, nums);
        if (!ans.empty() && ans[0] == -1) {
            cout << "error\n";
        }
        else if(!ans.empty()) {
            cout << "[";
            for (int j = 0; j < ans.size() - 1; j++) {
                cout << ans[j] << ",";
            }
            cout << ans[ans.size() - 1] << "]\n";
        }
        else {
            cout << "[]\n";
        }
    }
​
	return 0;
}
