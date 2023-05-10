#include <string>
#include <vector>

using namespace std;

int cache[500][500];

int solve(vector<vector<int>>& triangle, int row, int idx) {
    if (row == triangle.size() - 1) {
        return triangle[row][idx];
    }
    
    if (idx < 0 || idx > row) {
        return 0;
    }
    
    int& ret = cache[row][idx];
    if (ret != -1) {
        return ret; 
    }
    
    int cur_value = triangle[row][idx];
    ret = cur_value + max(solve(triangle, row+1, idx), solve(triangle, row+1, idx+1));
    return ret;
}

int solution(vector<vector<int>> triangle) {
    fill(&cache[0][0], &cache[499][500], 0);
    
    cache[0][0] = triangle[0][0];
    for (int row=1; row<triangle.size(); row++) {
        for (int col=0; col<triangle[row].size(); col++) {
            if (col == 0) {
                cache[row][col] = cache[row-1][col] + triangle[row][col];
            }
            else if (col == triangle[row].size()-1) {
                cache[row][col] = cache[row-1][col-1] + triangle[row][col];
            }
            else {
                cache[row][col] = max(cache[row-1][col], cache[row-1][col-1]) + triangle[row][col];
            }
        }
    }
    
    int ret = -1;
    int row = triangle.size()-1;
    for(int idx=0; idx<triangle[row].size(); idx++) {
        ret = max(ret, cache[row][idx]);
    }
    
    return ret;
}
