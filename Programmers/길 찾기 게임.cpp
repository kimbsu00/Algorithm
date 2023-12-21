#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

struct Node
{
    int x, y, idx;
};

int binary_tree[16384][2];

void solve(Node parent, vector<Node> node_list)
{
    vector<Node> left_subtree, right_subtree;
    Node left_child = Node({-1, -1, -1});
    Node right_child = Node({-1, -1, -1});
    for (Node node : node_list)
    {
        if (node.x == parent.x)
        {
            // do nothing
        }
        else if (node.x < parent.x)
        {
            if (node.y > left_child.y)
            {
                left_child = node;
            }
            left_subtree.push_back(node);
        }
        else if (node.x > parent.x)
        {
            if (node.y > right_child.y)
            {
                right_child = node;
            }
            right_subtree.push_back(node);
        }
    }

    if (left_child.idx != -1)
    {
        binary_tree[parent.idx][0] = left_child.idx;

        if (!left_subtree.empty())
        {
            solve(left_child, left_subtree);
        }
    }
    if (right_child.idx != -1)
    {
        binary_tree[parent.idx][1] = right_child.idx;

        if (!right_subtree.empty())
        {
            solve(right_child, right_subtree);
        }
    }
}

vector<int> preorder(int node)
{
    vector<int> ret(1, node + 1);

    if (binary_tree[node][0] != -1)
    {
        vector<int> left_subtree = preorder(binary_tree[node][0]);
        ret.insert(ret.end(), left_subtree.begin(), left_subtree.end());
    }
    if (binary_tree[node][1] != -1)
    {
        vector<int> right_subtree = preorder(binary_tree[node][1]);
        ret.insert(ret.end(), right_subtree.begin(), right_subtree.end());
    }

    return ret;
}

vector<int> postorder(int node)
{
    vector<int> ret;

    if (binary_tree[node][0] != -1)
    {
        vector<int> left_subtree = postorder(binary_tree[node][0]);
        ret.insert(ret.end(), left_subtree.begin(), left_subtree.end());
    }
    if (binary_tree[node][1] != -1)
    {
        vector<int> right_subtree = postorder(binary_tree[node][1]);
        ret.insert(ret.end(), right_subtree.begin(), right_subtree.end());
    }

    ret.push_back(node + 1);

    return ret;
}

vector<vector<int>> solution(vector<vector<int>> nodeinfo)
{
    fill(&binary_tree[0][0], &binary_tree[16383][2], -1);

    Node root = Node({-1, -1, -1});
    vector<Node> node_list;
    for (int idx = 0; idx < nodeinfo.size(); idx++)
    {
        vector<int> node = nodeinfo[idx];

        if (root.y < node[1])
        {
            root = Node({node[0], node[1], idx});
        }
        node_list.push_back(Node({node[0], node[1], idx}));
    }
    solve(root, node_list);

    vector<vector<int>> answer;
    answer.push_back(preorder(root.idx));
    answer.push_back(postorder(root.idx));
    return answer;
}
