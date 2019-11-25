// fail code #1

#include<iostream>
#include<vector>
#include<string>

#define GAMESIZE 5

using namespace std;

vector<vector<char>> boggle;
vector<vector<char>> word;
bool cache[5][5][8];
// index2 는 word 에서 어떤 문자를 보고 있는지를, index1 은 word 에서 보고 있는 문자열에서 어떤 문자를 보고 있는지를
bool find(const int& row, const int& col, const int& index1, const int& index2);

int main(void)
{
	int C;
	cin >> C;

	for (int tc = 0; tc < C; tc++)
	{
		// vector and cache clear
		boggle.clear();
		fill(&cache[0][0][0], &cache[4][4][8], false);

		// input boggle board
		for (int i = 0; i < GAMESIZE; i++)
		{
			string str;
			cin >> str;
			vector<char> vec(str.size());
			for (int j = 0; j < str.size(); j++)
				vec[j] = str.at(j);
			boggle.push_back(vec);
		}

		// input word
		int num;
		cin >> num;
		for (int i = 0; i < num; i++)
		{
			string str;
			cin >> str;
			vector<char> vec(str.size());
			for (int j = 0; j < str.size(); j++)
				vec[j] = str.at(j);
			word.push_back(vec);
		}
			
		for (int i = 0; i < num; i++)
		{
			fill(&cache[0][0][0], &cache[4][4][8], false);

			bool isExist = false;
			for (int row = 0; row < GAMESIZE; row++)
			{
				for (int col = 0; col < GAMESIZE; col++)
				{
					if (find(row, col, 0, i))
						isExist = true;
				}
			}
			for (int k = 0; k < word[i].size(); k++)
				cout << word[i][k];
			if (isExist)
				cout << " YES" << endl;
			else
				cout << " NO" << endl;
		}
	}

	return 0;
}

bool find(const int& row, const int& col, const int& index1, const int& index2)
{
	// boggle 판 밖으로 나간 경우 return false
	if (row < 0 || row >= GAMESIZE || col < 0 || col >= GAMESIZE)
		return false;

	// 문자를 끝까지 다 비교한 경우 return true;
	if (index1 == word[index2].size())
		return true;

	// 비교하는 문자가 같지 않은 경우 return false
	if (boggle[row][col] != word[index2][index1])
		return false;

	for (int i = 0; i < 8; i++)
	{
		if (cache[row][col][i])
			return true;
	}

	bool ret = false;
	// top
	if (find(row - 1, col, index1 + 1, index2))
	{	
		cache[row][col][0] = ret = true;
	}
	// top-right
	else if (find(row - 1, col + 1, index1 + 1, index2))
	{
		cache[row][col][1] = ret = true;
	}
	// right
	else if (find(row, col + 1, index1 + 1, index2))
	{
		cache[row][col][2] = ret = true;
	}
	// bottom-right
	else if (find(row + 1, col + 1, index1 + 1, index2))
	{
		cache[row][col][3] = ret = true;
	}
	// bottom
	else if (find(row + 1, col, index1 + 1, index2))
	{
		cache[row][col][4] = ret = true;
	}
	// bottom-left
	else if (find(row + 1, col - 1, index1 + 1, index2))
	{
		cache[row][col][5] = ret = true;
	}
	// left
	else if (find(row, col - 1, index1 + 1, index2))
	{
		cache[row][col][6] = ret = true;
	}
	// top-left
	else if (find(row - 1, col - 1, index1 + 1, index2))
	{
		cache[row][col][7] = ret = true;
	}

	return ret;
}


// fail code #2
#include<iostream>
#include<vector>
#include<string>

#define GAMESIZE 5

using namespace std;

vector<vector<char>> boggle;
vector<vector<char>> word;
bool cache[5][5][8][10];
// index2 는 word 에서 어떤 문자를 보고 있는지를, index1 은 word 에서 보고 있는 문자열에서 어떤 문자를 보고 있는지를
bool find(const int& row, const int& col, const int& index1, const int& index2);

int main(void)
{
	int C;
	cin >> C;

	for (int tc = 0; tc < C; tc++)
	{
		// vector and cache clear
		boggle.clear();
		fill(&cache[0][0][0][0], &cache[4][4][7][10], false);

		// input boggle board
		for (int i = 0; i < GAMESIZE; i++)
		{
			string str;
			cin >> str;
			vector<char> vec(str.size());
			for (int j = 0; j < str.size(); j++)
				vec[j] = str.at(j);
			boggle.push_back(vec);
		}

		// input word
		int num;
		cin >> num;
		for (int i = 0; i < num; i++)
		{
			string str;
			cin >> str;
			vector<char> vec(str.size());
			for (int j = 0; j < str.size(); j++)
				vec[j] = str.at(j);
			word.push_back(vec);
		}

		for (int i = 0; i < num; i++)
		{
			fill(&cache[0][0][0][0], &cache[4][4][7][10], false);

			bool isExist = false;
			for (int row = 0; row < GAMESIZE; row++)
			{
				for (int col = 0; col < GAMESIZE; col++)
				{
					if (find(row, col, 0, i))
						isExist = true;
				}
			}
			for (int k = 0; k < word[i].size(); k++)
				cout << word[i][k];
			if (isExist)
				cout << " YES" << endl;
			else
				cout << " NO" << endl;
		}
	}

	return 0;
}

bool find(const int& row, const int& col, const int& index1, const int& index2)
{
	// boggle 판 밖으로 나간 경우 return false
	if (row < 0 || row >= GAMESIZE || col < 0 || col >= GAMESIZE)
		return false;

	// 문자를 끝까지 다 비교한 경우 return true;
	if (index1 == word[index2].size())
		return true;

	// 비교하는 문자가 같지 않은 경우 return false
	if (boggle[row][col] != word[index2][index1])
		return false;

	for (int i = 0; i < 8; i++)
	{
		if (cache[row][col][i][index1])
			return true;
	}

	bool ret = false;
	// top
	if (find(row - 1, col, index1 + 1, index2))
	{
		cache[row][col][0][index1] = ret = true;
	}
	// top-right
	else if (find(row - 1, col + 1, index1 + 1, index2))
	{
		cache[row][col][1][index1] = ret = true;
	}
	// right
	else if (find(row, col + 1, index1 + 1, index2))
	{
		cache[row][col][2][index1] = ret = true;
	}
	// bottom-right
	else if (find(row + 1, col + 1, index1 + 1, index2))
	{
		cache[row][col][3][index1] = ret = true;
	}
	// bottom
	else if (find(row + 1, col, index1 + 1, index2))
	{
		cache[row][col][4][index1] = ret = true;
	}
	// bottom-left
	else if (find(row + 1, col - 1, index1 + 1, index2))
	{
		cache[row][col][5][index1] = ret = true;
	}
	// left
	else if (find(row, col - 1, index1 + 1, index2))
	{
		cache[row][col][6][index1] = ret = true;
	}
	// top-left
	else if (find(row - 1, col - 1, index1 + 1, index2))
	{
		cache[row][col][7][index1] = ret = true;
	}

	return ret;
}
