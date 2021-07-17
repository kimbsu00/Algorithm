/*
url: https://programmers.co.kr/learn/courses/30/lessons/81303?language=cpp
*/

#include <string>
#include <vector>
#include <stack>

using namespace std;

class Node {
public:
    int data;
    Node* prev;
    Node* next;
    
    Node(int data) {
        this->data = data;
        prev = nullptr;
        next = nullptr;
    }
};

stack<Node*> stk;

// head와 tail에 데이터를 저장하지 않는 LinkedList
class LinkedList {
public:
    Node* head;
    Node* tail;
    
    void insert(int data) {
        Node* node = new Node(data);
        
        Node* prev = tail->prev;
        prev->next = node;
        node->prev = prev;
        
        tail->prev = node;
        node->next = this->tail;
    }
    
    Node* remove(Node* node) {
        // LinkedList에서 node를 제거하고
        Node* prev = node->prev;
        Node* next = node->next;
        
        prev->next = next;
        next->prev = prev;
        
        // stack에 push 한다.
        stk.push(node);
        
        // node가 가장 마지막 행인 경우에는, node의 이전 행을 리턴하고
        if(node->next == this->tail) 
            return node->prev;
        // 가장 마지막 행이 아니라면, node의 다음 행을 리턴한다.
        else 
            return node->next;
    }
    
    void restore() {
        // stack에서 노드 한개를 꺼내서
        Node* node = stk.top();
        stk.pop();
        
        // 다시 연결해주면 된다.
        Node* prev = node->prev;
        Node* next = node->next;
        
        prev->next = node;
        next->prev = node;
    }
};

LinkedList list;

void solve(Node* selected, vector<string>& cmd) {
    for(int i=0; i<cmd.size(); i++) {
        if(cmd[i][0] == 'U') {
            // 이동해야 하는 크기를 구하고
            string s_num = cmd[i].substr(2);
            int num = stoi(s_num);
            // 위로 이동한다.
            while(num > 0) {
                selected = selected->prev;
                num--;
            }
        } 
        else if(cmd[i][0] == 'D') {
            // 이동해야 하는 크기를 구하고
            string s_num = cmd[i].substr(2);
            int num = stoi(s_num);
            // 아래로 이동한다.
            while(num > 0) {
                selected = selected->next;
                num--;
            }            
        }
        else if(cmd[i][0] == 'C') {
            selected = list.remove(selected);
        }
        else if(cmd[i][0] == 'Z') {
            list.restore();
        }
    }
}

string solution(int n, int k, vector<string> cmd) {
    string answer = "";
    
    // LinkedList 초기화
    list.head = new Node(-1);
    list.tail = new Node(-1);
    list.head->next = list.tail;
    list.tail->prev = list.head;
    
    Node* selected;
    for(int i=0; i<n; i++) {
        answer.append("O");
        list.insert(i);
        
        if(i==k)    selected = list.tail->prev;
    }
    
    solve(selected, cmd);
    while(!stk.empty()) {
        Node* node = stk.top();
        stk.pop();
        answer[node->data] = 'X';
    }
    
    return answer;
}
