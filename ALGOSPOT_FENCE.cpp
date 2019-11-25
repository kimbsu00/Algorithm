/*
2019년 09월 05일 작성
정답 코드
*/

#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

int get_left(int index, vector<int>& height)
{
	int ret = -1;
	for (int i = index - 1; i >= 0; i--)
	{
		if (height[index] > height[i])
		{
			ret = i;
			break;
		}
	}
	if (ret != -1)
		return ret;
	
	return 0;
}

int get_right(int index, vector<int>& height)
{
	int ret = height.size();
	for (int i = index + 1; i < height.size(); i++)
	{
		if (height[index] > height[i])
		{
			ret = i;
			break;
		}
	}
	if (ret != height.size())
		return ret;
	
	return height.size() - 1;
}

int max_size(vector<int>& height)
{
	vector<int> size(height.size(), -1);
	for (int i = 0; i < height.size(); i++)
	{
		size[i] = (get_right(i, height) - get_left(i, height) - 1) * height[i];
	}

	return *max_element(size.begin(), size.end());
}

int main(void)
{
	int c;
	cin >> c;
	vector<int> answer(c, -1);

	for (int tc = 0; tc < c; tc++)
	{
		int n;
		cin >> n;
		// n개의 울타리 높이를 입력받음
		// 맨 왼쪽과 맨 오른쪽에는 높이를 -1로 설정하여 더 이상 울타리가 존재하지 않음을 표시
		vector<int> height(n + 2, -1);
		height[0] = -1;
		height[n + 1] = -1;
		for (int i = 1; i < n + 1; i++)
			cin >> height[i];

		answer[tc] = max_size(height);
	}
	
	for (int i = 0; i < answer.size(); i++)
		cout << answer[i] << endl;

	return 0;
}
