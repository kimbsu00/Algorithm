/*
  url: https://www.acmicpc.net/problem/7432
*/

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <sstream>

using namespace std;

vector<string> split(string input, char delimiter)
{
    vector<string> ret;
    stringstream ss(input);
    string temp;

    while (getline(ss, temp, delimiter))
    {
        ret.push_back(temp);
    }

    return ret;
}

class Node
{
public:
    int level;
    string dir;
    map<string, Node *> children;

    Node(string p_dir) : dir(p_dir), level(0)
    {
        children = map<string, Node *>();
    }

    Node(string p_dir, int p_level) : dir(p_dir), level(p_level)
    {
        children = map<string, Node *>();
    }
};

class Trie
{
public:
    Node *root;

    Trie()
    {
        root = new Node("");
    }

    void insert(string dir)
    {
        vector<string> dir_fragment = split(dir, '\\');

        if (!dir_fragment.empty())
            _insert(root, dir_fragment, 0);
    }

    void print_dir()
    {
        auto it = root->children.begin();
        for (; it != root->children.end(); it++)
        {
            _print_dir(it->second);
        }
    }

private:
    void _insert(Node *node, vector<string> &dir_fragment, int idx)
    {
        if (idx == dir_fragment.size())
            return;

        string dir_name = dir_fragment[idx];
        auto it = node->children.find(dir_name);

        // 처음 발견한 디렉토리인 경우
        if (it == node->children.end())
        {
            Node *tmp = new Node(dir_name, node->level + 1);
            node->children.insert({dir_name, tmp});
            _insert(tmp, dir_fragment, idx + 1);
        }
        // 이전에 발견했던 디렉토리인 경우
        else
        {
            Node *tmp = it->second;
            _insert(tmp, dir_fragment, idx + 1);
        }
    }

    void _print_dir(Node *node)
    {
        for (int idx = 1; idx < node->level; idx++)
        {
            cout << " ";
        }
        cout << node->dir << "\n";

        auto it = node->children.begin();
        for (; it != node->children.end(); it++)
        {
            _print_dir(it->second);
        }
    }
};

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int N;
    cin >> N;

    Trie trie = Trie();
    for (int idx = 0; idx < N; idx++)
    {
        string dir;
        cin >> dir;
        trie.insert(dir);
    }
    trie.print_dir();

    return 0;
}
