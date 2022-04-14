// #include <iostream>
// #include <vector>
// #include <algorithm>
#include "src/basic_solution.cpp"

using namespace std;

class RightBinarySearch : public Solution {
public:
    virtual int binary_search(const vector<int>& array, const int& target) {
        if (array.size() == 0)
            return -1;
        int left = 0, right = array.size() - 1;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (array[mid] == target)
                left = mid + 1;
            else if (array[mid] < target)
                left = mid + 1;
            else if (array[mid] > target)
                right = mid - 1;
        }
        if (right < 0 || array[left - 1] != target)
            return -1;
        else
            return left - 1;
    }
};

void test_case() {
    vector<int> array {0,1,2,5,6,6,6,6,6,6,8,9,12,15,18,20,23,35,56,58,66,72,83,95,100};
    int target = 6;  // -10, 101 also can try...
    RightBinarySearch solution;
    int index = solution.binary_search(array, target);
    solution.Solution::print_vector(array);
    cout << "target = " << target << endl;
    cout << "index  = " << index << endl;  // 9
}

int main() {
    test_case();
}
