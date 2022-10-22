/*
  url: https://www.acmicpc.net/problem/6597
*/

#include <iostream>
#include <vector>
#include <string>

using namespace std;

string solve(string pre_order, string in_order)
{
    if (pre_order.empty())
        return "";

    char root = pre_order[0];
    int idx = in_order.find(root);

    string left = solve(pre_order.substr(1, idx), in_order.substr(0, idx));
    string right = solve(pre_order.substr(idx + 1), in_order.substr(idx + 1));

    return left.append(right) + root;
}

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    string pre_order; // parent, left, right
    string in_order;  // left, parent, right
    vector<string> answer;
    while (true)
    {
        cin >> pre_order >> in_order;

        if (cin.eof())
            break;

        answer.push_back(solve(pre_order, in_order));
    }

    for (int i = 0; i < answer.size(); i++)
    {
        cout << answer[i] << "\n";
    }

    return 0;
}
