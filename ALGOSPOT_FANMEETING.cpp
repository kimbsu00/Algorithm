#include<iostream>
#include<string>
#include<vector>

using namespace std;

bool NOR(vector<char>& member, vector<char>& fan, const int& index);

int main(void)
{
	int tc;
	cin >> tc;
	vector<int> answer(tc, 0);

	for (int i = 0; i < tc; i++)
	{
		string str1, str2;
		cin >> str1 >> str2;

		vector<char> member(str1.size());		// 멤버들을 저장할 벡터
		vector<char> fan(str2.size());			// 팬들을 저장할 벡터
								// 남자는 0, 여자는 1으로 저장 -> NOR 연산을 위함

		for (int n = 0; n < str1.size(); n++)
		{
			if (str1.at(n) == 'F')
				member[n] = 1;
			else
				member[n] = 0;
		}
		for (int n = 0; n < str2.size(); n++)
		{
			if (str2.at(n) == 'F')
				fan[n] = 1;
			else
				fan[n] = 0;
		}

		int start = 0;
		while (true)
		{
			// 모든 멤버들이 포옹을 하는 경우
			if (NOR(member, fan, start++))
				answer[i]++;
				
			if (start + str1.size() > str2.size())
				break;
		}
	}

	for (int i = 0; i < answer.size(); i++)
		cout << answer[i] << endl;

	return 0;
}

bool NOR(vector<char>& member, vector<char>& fan, const int& index)
{
	int ret = 0;

	for (int i = 0; i < member.size(); i++)
	{
		// NOR 연산 수행 -> member 와 fan 모두 남자인 경우, 즉 모두 0 인 경우에만 1 이 더해진다.
		ret += !(member[i] | fan[i + index]);
	}

	if (ret == 0)
		return true;
	else
		return false;
}

/*
bool NAND(int& member, vector<char>& fan, const int& size, const int& start)
{
	int num = 0;
	for (int i = 0; i < size; i++)
		if (fan[i + start])
			num += pow(2, i);
	int ret = !(member | num);
	if (fan[size - 1 + start] == 0)
		ret = 1;
	if (ret == 0)
		return true;
	else
		return false;
}
*/
