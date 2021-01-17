/*
  url: https://algospot.com/judge/problem/read/CLOCKSYNC
  
  완전탐색으로 구현하지 않았음.
  문제에 나와있는 스위치 - 시계 표를 시계 - 스위치 표로 바꿔서 해결함.
*/

#include<iostream>
#include<vector>

using namespace std;

int CLOCKSYNC();
void ClickSwitch(int index, int count);
void SetData();

// index 번째 스위치와 연결 되어있는 시계들의 번호를 저장하는 배열
vector<vector<int>>fromSwitch;
// index 번째 시계와 연결되어 있는 스위치들의 번호를 저장하는 배열
vector<vector<int>> fromClock(16);
// input 으로 들어오는 시계들의 초기 상태를 저장하는 배열
vector<int> Clock;

int main(void) {
	int C;
	cin >> C;
	vector<int> answer(C);

	SetData();

	for (int i = 0; i < C; i++) {
		Clock.clear();

		for (int k = 0; k < 16; k++) {
			int temp;
			cin >> temp;
			Clock.push_back((temp / 3) % 4);
		}

		answer[i] = CLOCKSYNC();
	}

	for (int i = 0; i < C; i++)
		cout << answer[i] << endl;

	return 0;
}

int CLOCKSYNC() {
	if (Clock[8] != Clock[12])
		return -1;
	if (Clock[14] != Clock[15])
		return -1;

	vector<int> count(10, 0);
	// 4번 스위치 클릭 횟수 설정
	Clock[8] != 0 ? count[4] = 4 - Clock[8] : count[4] = 0;
	ClickSwitch(4, count[4]);

	// 1번 스위치 클릭 횟수 설정
	Clock[11] != 0 ? count[1] = 4 - Clock[11] : count[1] = 0;
	ClickSwitch(1, count[1]);
	if (Clock[9] != Clock[13])		return -1;

	// 9번 스위치 클릭 횟수 설정
	Clock[9] != 0 ? count[9] = 4 - Clock[9] : count[9] = 0;
	ClickSwitch(9, count[9]);

	// 2번 스위치 클릭 횟수 설정 
	Clock[10] != 0 ? count[2] = 4 - Clock[10] : count[2] = 0;
	ClickSwitch(2, count[2]);

	// 3번 스위치 클릭 횟수 설정
	Clock[6] != 0 ? count[3] = 4 - Clock[6] : count[3] = 0;
	ClickSwitch(3, count[3]);
	
	// 7번 스위치 클릭 횟수 설정
	Clock[7] != 0 ? count[7] = 4 - Clock[7] : count[7] = 0;
	ClickSwitch(7, count[7]);
	if (Clock[4] != Clock[5])			return -1;

	// 8번 스위치 클릭 횟수 설정
	Clock[4] != 0 ? count[8] = 4 - Clock[4] : count[8] = 0;
	ClickSwitch(8, count[8]);

	// 6번 스위치 클릭 횟수 설정
	Clock[3] != 0 ? count[6] = 4 - Clock[3] : count[6] = 0;
	ClickSwitch(6, count[6]);

	// 5번 스위치 클릭 횟수 설정
	Clock[14] != 0 ? count[5] = 4 - Clock[14] : count[5] = 0;
	ClickSwitch(5, count[5]);
	if (!(Clock[0] == Clock[1] && Clock[0] == Clock[2]))		return -1;

	// 0번 스위치 클릭 횟수 설정
	Clock[0] != 0 ? count[0] = 4 - Clock[0] : count[0] = 0;
	ClickSwitch(0, count[0]);

	int ret = 0;
	for (int i = 0; i < count.size(); i++)
		ret += count[i];

	return ret;
}

void ClickSwitch(int index, int count) {
	for (int i = 0; i < fromSwitch[index].size(); i++) {
		Clock[fromSwitch[index][i]] += count;
		Clock[fromSwitch[index][i]] %= 4;
	}
}

void SetData() {
	vector<int> zero;
	zero.push_back(0);
	zero.push_back(1);
	zero.push_back(2);
	fromSwitch.push_back(zero);

	vector<int> one;
	one.push_back(3);
	one.push_back(7);
	one.push_back(9);
	one.push_back(11);
	fromSwitch.push_back(one);

	vector<int>two;
	two.push_back(4);
	two.push_back(10);
	two.push_back(14);
	two.push_back(15);
	fromSwitch.push_back(two);

	vector<int> three;
	three.push_back(0);
	three.push_back(4);
	three.push_back(5);
	three.push_back(6);
	three.push_back(7);
	fromSwitch.push_back(three);

	vector<int> four;
	four.push_back(6);
	four.push_back(7);
	four.push_back(8);
	four.push_back(10);
	four.push_back(12);
	fromSwitch.push_back(four);

	vector<int> five;
	five.push_back(0);
	five.push_back(2);
	five.push_back(14);
	five.push_back(15);
	fromSwitch.push_back(five);

	vector<int> six;
	six.push_back(3);
	six.push_back(14);
	six.push_back(15);
	fromSwitch.push_back(six);

	vector<int> seven;
	seven.push_back(4);
	seven.push_back(5);
	seven.push_back(7);
	seven.push_back(14);
	seven.push_back(15);
	fromSwitch.push_back(seven);

	vector<int> eight;
	eight.push_back(1);
	eight.push_back(2);
	eight.push_back(3);
	eight.push_back(4);
	eight.push_back(5);
	fromSwitch.push_back(eight);

	vector<int> nine;
	nine.push_back(3);
	nine.push_back(4);
	nine.push_back(5);
	nine.push_back(9);
	nine.push_back(13);
	fromSwitch.push_back(nine);

	for (int i = 0; i < fromSwitch.size(); i++) {
		for (int j = 0; j < fromSwitch[i].size(); j++) {
			fromClock[fromSwitch[i][j]].push_back(i);
		}
	}
}
