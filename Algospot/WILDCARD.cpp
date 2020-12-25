/*
  url: https://algospot.com/judge/problem/read/WILDCARD
  
  "각 테스트 케이스마다 주어진 와일드카드에 매치되는 파일들의 이름을 한 줄에 하나씩 아스키 코드 순서(숫자, 대문자, 소문자 순)대로 출력한다." 라는 output 조건을 보고,
  모든 답안을 한꺼번에 정렬해서 답을 출력했는데 오답 처리가 되어서 곰곰이 생각해 본 결과, 각 테스트 케이스별로 정답을 정렬해서 출력해야 함을 깨닫고 정답 처리 받음.
  문장 독해력이 부족해서 삽질한 문제.
*/

#include<iostream>	
#include<string>	
#include<vector>
#include<algorithm>

#define TRUE 2
#define FALSE 1
#define NONE 0

using namespace std;

int solve(string wildcard, string filename);

int cache[101][101];
string wildCard;
vector<string> fileName;

int main(void) {
	int C;	
	cin >> C;
	vector<vector<string>> answer(C);

	for (int i = 0; i < C; i++) {
		cin >> wildCard;
		int N;
		cin >> N;
		
		fileName.clear();
		for (int k = 0; k < N; k++) {
			string temp;
			cin >> temp;
			fileName.push_back(temp);
		}

		vector<string> vec;
		for (int k = 0; k < N; k++) {
			fill(&cache[0][0], &cache[100][101], NONE);
			int ret = solve(wildCard, fileName[k]);
			if (ret == TRUE)
				vec.push_back(fileName[k]);
		}
		sort(vec.begin(), vec.end());
		answer[i] = vec;
	}

	for (int i = 0; i < answer.size(); i++) {
		for (int j = 0; j < answer[i].size(); j++) {
			cout << answer[i][j] << endl;
		}
	}

	return 0;
}

int solve(string wildcard, string filename) {
	if (filename.size() == 0 && wildcard.size() == 0)
		return TRUE;

	if (filename.size() == 0 && !(wildcard.at(0) == '?' || wildcard.at(0) == '*')) 
		return FALSE;
	
	if (filename.size() > 0 && wildcard.size() == 0)
		return FALSE;


	int& ret = cache[wildcard.size() - 1][filename.size() - 1];
	if (ret != NONE)
		return ret;

	if (wildcard.at(0) == '?') {
		if (filename.size() > 0) {
			ret = solve(wildcard.substr(1, wildcard.size() - 1), filename.substr(1, filename.size() - 1));
		}
		ret = max(ret, solve(wildcard.substr(1, wildcard.size() - 1), filename));
	}
	else if (wildcard.at(0) == '*') {
		if (filename.size() > 0) {
			ret = max(solve(wildcard, filename.substr(1, filename.size() - 1)), solve(wildcard.substr(1, wildcard.size() - 1), filename.substr(1, filename.size() - 1)));
		}
		ret = max(ret, solve(wildcard.substr(1, wildcard.size() - 1), filename));
	}
	else if (wildcard.at(0) == filename.at(0)) {
		ret = solve(wildcard.substr(1, wildcard.size() - 1), filename.substr(1, filename.size() - 1));
	}
	else {
		ret = FALSE;
	}

	return ret;
}
