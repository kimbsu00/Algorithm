#include <iostream>
#include <string>
#include <vector>
#include <stack>

using namespace std;

struct Node
{
    int num;
    Node *next;
    Node *prev;
} typedef node;

class LinkedList
{
private:
    int init_cnt;
    node *selected_node;
    node *head;
    node *tail;
    stack<node *> undo;

public:
    LinkedList()
    {
        init_cnt = 0;
        selected_node = nullptr;
        head = new node;
        tail = new node;

        head->num = -1;
        head->next = tail;
        head->prev = nullptr;

        tail->num = -1;
        tail->next = nullptr;
        tail->prev = head;
    }

    LinkedList(int init_cnt, int init_focus) : init_cnt(init_cnt)
    {
        head = new node;
        tail = new node;

        head->num = -1;
        head->next = tail;
        head->prev = nullptr;

        tail->num = -1;
        tail->next = nullptr;
        tail->prev = head;

        int idx = 0;
        node *prev_node = head;

        while (idx < init_cnt)
        {
            node *cur_node = new node;
            cur_node->num = idx;
            cur_node->prev = prev_node;
            cur_node->next = tail;

            prev_node->next = cur_node;
            tail->prev = cur_node;
            prev_node = cur_node;

            if (idx == init_focus)
            {
                selected_node = cur_node;
            }

            idx += 1;
        }
    }

    void command(string cmd)
    {
        if (cmd == "C")
        {
            node *prev_node = selected_node->prev;
            node *next_node = selected_node->next;
            undo.push(selected_node);

            if (prev_node != nullptr)
            {
                prev_node->next = next_node;
            }
            if (next_node != nullptr)
            {
                next_node->prev = prev_node;
            }

            if (next_node == tail)
            {
                selected_node = prev_node;
            }
            else
            {
                selected_node = next_node;
            }
        }
        else if (cmd == "Z")
        {
            if (!undo.empty())
            {
                node *top = undo.top();
                undo.pop();

                node *prev_node = top->prev;
                node *next_node = top->next;
                prev_node->next = top;
                next_node->prev = top;
            }
        }
        else
        {
            int delta = stoi(cmd.substr(2));
            cmd = cmd[0];

            if (cmd == "U")
            {
                while (delta > 0 && selected_node->prev != head)
                {
                    selected_node = selected_node->prev;
                    delta -= 1;
                }
            }
            else if (cmd == "D")
            {
                while (delta > 0 && selected_node->next != tail)
                {
                    selected_node = selected_node->next;
                    delta -= 1;
                }
            }
        }
    }

    string answer()
    {
        string ret = "";
        for (int idx = 0; idx < init_cnt; idx++)
        {
            ret += "O";
        }

        while (!undo.empty())
        {
            node *top = undo.top();
            undo.pop();

            ret[top->num] = 'X';
        }
        return ret;
    }
} typedef linked_list;

string solution(int n, int k, vector<string> cmd)
{
    linked_list ll(n, k);
    for (string cmd_str : cmd)
    {
        ll.command(cmd_str);
    }

    string answer = ll.answer();
    return answer;
}

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n = 8;
    int k = 2;
    vector<string> cmd;
    cmd.push_back("D 2");
    cmd.push_back("C");
    cmd.push_back("U 3");
    cmd.push_back("C");
    cmd.push_back("D 4");
    cmd.push_back("C");
    cmd.push_back("U 2");
    cmd.push_back("Z");
    cmd.push_back("Z");

    cmd.push_back("U 1");
    cmd.push_back("C");
    string answer = solution(n, k, cmd);
    printf("%s\n", answer.c_str());

    return 0;
}
