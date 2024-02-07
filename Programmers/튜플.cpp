#include <string>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

bool compare(vector<int> &left, vector<int> &right)
{
    return left.size() < right.size();
}

vector<int> solution(string s)
{
    s = s.substr(1, s.size() - 2);

    vector<vector<int>> set_list;
    vector<int> set;
    string str_num = "";
    for (int idx = 0; idx < s.size(); idx++)
    {
        char ch = s[idx];

        // append number
        if ('0' <= ch && ch <= '9')
        {
            str_num += ch;
        }
        // reset
        else if (ch == '{')
        {
            set.clear();
        }
        // string to int & add vector
        else if (ch == '}' || ch == ',')
        {
            if (!str_num.empty())
            {
                int num = stoi(str_num);
                str_num.clear();
                set.push_back(num);
            }

            if (ch == '}')
            {
                set_list.push_back(set);
            }
        }
    }
    sort(set_list.begin(), set_list.end(), compare);

    map<int, int> map;
    int size = 0;
    for (vector<int> vec : set_list)
    {
        for (int num : vec)
        {
            auto ret = map.insert({num, size});

            if (ret.second)
            {
                size += 1;
            }
        }
    }

    vector<int> answer(size, -1);
    for (auto it = map.begin(); it != map.end(); it++)
    {
        int idx = it->second;
        int num = it->first;
        answer[idx] = num;
    }

    return answer;
}
