#include <string>
#include <vector>

using namespace std;

string solution(int n, int m, int x, int y, int r, int c, int k) {
    int move_left = 0;
    int move_up = 0;
    int move_right = 0;
    int move_down = 0;
    
    // move to down
    if (x < r) {
        move_down = r - x;
        
        // move to right
        if (y < c) {
            move_right = c - y;
        }
        // move to left
        else {
            move_left = y - c;
        }
    }
    // move to up
    else {
        move_up = x - r;
        
        // move to right
        if (y < c) {
            move_right = c - y;
        }
        // move to left
        else {
            move_left = y - c;
        }
    }
    
    int remain_cnt = k - (move_left + move_up + move_right + move_down);
    
    string answer = "";
    if (remain_cnt < 0) {
        answer = "impossible";
    }
    else if (remain_cnt%2 == 1) {
        answer = "impossible";
    }
    else {
        while (k-- > 0) {
            // down
            if ((x+1 <= n) && (move_down > 0 || remain_cnt > 0)) {
                x += 1;
                answer += 'd';
                
                if (move_down > 0) {
                    move_down -= 1;
                } else {
                    move_up += 1;
                    remain_cnt -= 2;
                }
            }
            // left
            else if ((y-1 > 0) && (move_left > 0 || remain_cnt > 0)) {
                y -= 1;
                answer += 'l';
                
                if (move_left > 0) {
                    move_left -= 1;
                } 
                else {
                    move_right += 1;
                    remain_cnt -=2;
                }
            }
            // right
            else if ((y+1 <= m) && (move_right > 0 || remain_cnt > 0)) {
                y += 1;
                answer += 'r';
                
                if (move_right > 0) {
                    move_right -= 1;
                }
                else {
                    move_left += 1;
                    remain_cnt -= 2;
                }
            }
            // up
            else if ((x-1 > 0) && (move_up > 0 || remain_cnt > 0)) {
                x -= 1;
                answer += 'u';
                
                if (move_up > 0) {
                    move_up -= 1;
                }
                else {
                    move_down += 1;
                    remain_cnt -= 2;
                }
            }
        }
    }
    
    return answer;
}
