#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;
vector<int> sequence;
int cache[500];

int LIS(int start);
//int lis(vector<int> vec, int index);

int main(void)
{
	int C;
	cin >> C;
	vector<int> answer(C);

	for (int tc = 0; tc < C; tc++)
	{
		sequence.clear();
		fill(&cache[0], &cache[500], -1);

		int N;
		cin >> N;
		
		for (int i = 0; i < N; i++)
		{
			int num;
			cin >> num;
			sequence.push_back(num);
		}

		int ret = 0;
		for (int i = 0; i < sequence.size(); i++)
			ret = max(ret, LIS(i));
		answer[tc] = ret;
	}

	for (int i = 0; i < answer.size(); i++)
		cout << answer[i] << endl;

	return 0;
}

int LIS(int start)
{
	if (cache[start] != -1) return cache[start];

	int ret = 1;
	for (int i = start + 1; i < sequence.size(); i++)
	{
		if (sequence[start] < sequence[i])
			ret = max(ret, LIS(i) + 1);
	}
	return cache[start] = ret;
}

//int lis(vector<int> vec, int index)
//{
//	if (index == sequence.size() - 1)
//	{
//		if (vec[vec.size() - 1] < sequence[index])
//			return vec.size() + 1;
//		else
//			return vec.size();
//	}
//
//	if (cache[index] != -1)
//		return cache[index];
//
//	int ret = -1;
//
//	for (int i = index + 1; i < sequence.size(); i++)
//	{
//		if (sequence[index] < sequence[i])
//		{
//			vec.push_back(sequence[i]);
//			ret = max(ret, lis(vec, i));
//			vec.pop_back();
//		}
//	}
//
//	if (ret != -1)
//		cache[index] = ret - vec.size() + 1;
//	else
//		ret = vec.size();
//
//	return ret;
//}
