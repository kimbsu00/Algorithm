/*
  url: https://algospot.com/judge/problem/read/ENDIANS
  
  10진수를 2진수로 바꾸고 저장하는 방법에서 약간의 혼동이 왔던 문제.
  305,419,896 라는 10진수를 2진수로 바꾸면 
  (MSB) 00010010 00110100 01010110 01111000 (LSB) 이 되는데 아래 코드에서 이 2진수를 vector<int> bits 에
  00011110 01101010 00101100 01001000 으로 저장해서 bits 로 부터 원래 값을 읽어내려면 이를 뒤집어 주는 작업이 필요함을 간과함.
*/

#include<iostream>
#include<vector>

using namespace std;

unsigned int ENDIANS(unsigned int& input);

int main(void) {
	int C;
	cin >> C;
	vector<unsigned int> answer(C);

	for (int i = 0; i < C; i++) {
		unsigned int input;
		cin >> input;
		answer[i] = ENDIANS(input);
	}

	for (int i = 0; i < C; i++) 
		cout << answer[i] << endl;
	
	return 0;
}

unsigned int ENDIANS(unsigned int& input) {
	vector<int> bits(32, 0);

	unsigned int check = (1 << 32) - 1;
	if (input >= check)		return input;

	int shift = 0;
	while ((1<<shift) <= input) {
		if ((input & (1 << shift)) != 0)
			bits[shift] = 1;
		else
			bits[shift] = 0;
		shift++;
	}

	vector<int> converted;
	for (int i = 0; i < 4; i++) {
		for (int k = 7; k >= 0; k--) {
			converted.push_back(bits[i * 8 + k]);
		}
	}

	unsigned int ret = 0;
	for (int i = 0; i < converted.size(); i++) {
		if (converted[i])
			ret |= (1 << 31 - i);
	}

	return ret;
}
