#include<iostream>
#include<vector>
#include<string>

using namespace std;

int FANMEETING();
bool NOR(int index);

/* 
	int 형이 아니고  char 형 변수를 사용하는 이유?
	->	NOR() 함수에서 비트연산자 | 를 사용하는데,
		int 형 변수보다 char 형 변수에 대해 비트연산을 수행하는 것이 속도가 더 빠르기 때문.
		실제로 char 를 int 로 변경해서 제출하면 시간초과로 오답처리 됨.
*/
vector<char> member;
vector<char> fan;

int main(void) {
	int C;
	cin >> C;
	vector<int> answer(C);

	for (int i = 0; i < C; i++) {
		member.clear();
		fan.clear();

		string temp1;
		string temp2;
		cin >> temp1 >> temp2;

		// 남자는 0 으로, 여자는 1 로 저장한다.
		for (int k = 0; k < temp1.size(); k++) {
			if (temp1[k] == 'M')
				member.push_back(0);
			else if (temp1[k] == 'F')
				member.push_back(1);
		}
		for (int k = 0; k < temp2.size(); k++) {
			if (temp2[k] == 'M')
				fan.push_back(0);
			else if (temp2[k] == 'F')
				fan.push_back(1);
		}

		answer[i] = FANMEETING();
	}

	for (int i = 0; i < C; i++)
		cout << answer[i] << endl;
	
	return 0;
}

int FANMEETING() {
	int ret = 0;
	int index = 0;

	while (true) {
		if (NOR(index++))		ret++;
		if (index + member.size() > fan.size())		break;
	}

	return ret;
}

bool NOR(int index) {
	int ret = 0;

	// 모든 멤버들이 포옹을 하는 경우는 멤버와 팬을 NOR 연산 했을 때, 전부 0이 되는 경우이다.
	for (int i = 0; i < member.size(); i++) {
		ret += !(member[i] | fan[i + index]);
	}
	
	if (ret == 0)
		return true;
	else
		return false;
}
