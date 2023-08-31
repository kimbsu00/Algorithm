#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

int N;
vector<vector<int>> graph;
vector<int> blue_team, white_team;
vector<bool> visited;

vector<string> split(string input, char delimiter)
{
    vector<string> answer;
    stringstream ss(input);
    string temp;

    while (getline(ss, temp, delimiter))
    {
        answer.push_back(temp);
    }

    return answer;
}

void dfs(int node, bool is_blue)
{
    visited[node] = true;

    if (is_blue)
    {
        blue_team.push_back(node);
    }
    else
    {
        white_team.push_back(node);
    }

    for (int next : graph[node])
    {
        if (!visited[next])
        {
            dfs(next, !is_blue);
        }
    }
}

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> N;
    graph = vector<vector<int>>(N, vector<int>());
    visited = vector<bool>(N, false);

    for (int node = 0; node < N; node++)
    {
        int cnt, hater;
        cin >> cnt;

        for (int idx = 0; idx < cnt; idx++)
        {
            cin >> hater;
            hater -= 1;

            graph[node].push_back(hater);
            graph[hater].push_back(node);
        }
    }

    for (int node = 0; node < N; node++)
    {
        if (!visited[node])
        {
            dfs(node, true);
        }
    }

    sort(blue_team.begin(), blue_team.end());
    sort(white_team.begin(), white_team.end());

    cout << blue_team.size() << "\n";
    for (int blue_member : blue_team)
    {
        cout << blue_member + 1 << " ";
    }
    cout << "\n";

    cout << white_team.size() << "\n";
    for (int white_member : white_team)
    {
        cout << white_member + 1 << " ";
    }
    cout << "\n";

    return 0;
}
