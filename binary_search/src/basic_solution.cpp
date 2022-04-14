#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    virtual int binary_search(const vector<int>& array, const int& target) = 0;
    void print_vector(const vector<int>& array) {
        for_each(array.begin(), array.end(), [](int val){
            cout << val << ' ';
        });
        cout << endl;
    }
};