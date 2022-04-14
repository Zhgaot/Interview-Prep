#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#define VECTOR_ERASE_ERR 0
#define VECTOR_ERASE_NTRUE 0
#define VECTOR_ERASE_TRUE 1

using namespace std;

/* 打印vector数组 */
void print_vector(const vector<int>& v) {
    for_each(v.begin(), v.end(), [](const int& e){
        cout << e << " ";
    }); cout << endl;
}

/* 希望删除值为target的所有元素(target可能在vector中重复) */
void vector_erase(vector<int> v, const int& target) {
#if VECTOR_ERASE_ERR
    /**
     * 下面操作会由于迭代器失效, 导致迭代器后移操作危险
     * 若删除vector中的一个迭代器, 则被删除的迭代器会成为野指针, 对野指针的++后移操作危险
    */
    for (vector<int>::iterator it = v.begin(); it != end(); ++it) {
        if (*it == target) {
            v.erase(it);
        }
    }
#endif

#if VECTOR_ERASE_NTRUE
    /**
     * 下面操作会由于迭代器失效, 导致无法删除连续的重复元素, 但并不危险
     * 由于vector底层为数组结构, 删除其中一个元素后, 后序元素均会前移
     * erase将返回新的一个指向原位置但其实指向被删除元素后一个元素的位置(由于元素前移)
    */
    for (vector<int>::iterator it = v.begin(); it != end(); ++it) {
        if (*it == target) {
            it = v,erase(it);  // [1,2,3,4,5,->6,7,8,9,10] 迭代器指向后一个target元素
        }
    }  // 最终: [1,2,3,4,5,6,7,8,9,10] 没有将target(6)元素全部删除
#endif

#if VECTOR_ERASE_TRUE
    /**
     * 下面操作不会由于迭代器失效, 导致操作危险或删除不完全情况
    */
    for (vector<int>::iterator it = v.begin(); it != v.end();) {
        if (*it == target) {
            it = v.erase(it);
        } else {
            ++it;
        }
    }
#endif

    print_vector(v);
}

/* 希望在值为target的元素后插入一个标识值 */
void vector_insert(vector<int> v, const int& target) {
    const int insert_flag = 100;
    for (vector<int>::iterator it = v.begin(); it != v.end(); ++it) {
        if (*it == target) {
            v.insert(it, insert_flag);
            break;  // "Segmentation fault" if not break
        }
    }
    print_vector(v);
}

void vector_resize(vector<int> v, const int& target) {
    v.reserve(20);
    for (vector<int>::iterator it = v.begin(); it != v.end(); ++it) {
        if (*it == target) {
            // v.resize(target * 100);
            v.push_back(1);
        }
        cout << *it << " ";
    }
    print_vector(v);
}

int main() {
    /* 创建一个vector, 其中有一个值重复 */
    const int num = 10;
    const int target = 6;
    cout << "target: " << target << endl;
    vector<int> v;
    for (int i = 1; i <= num; ++i) {
        if (i == target) {
            v.push_back(i);
            v.push_back(i);
        } else {
            v.push_back(i);
        }
    }  // v = [1,2,3,4,5,6,6,7,8,9,10]
    cout << "Initial array : ";
    print_vector(v);

    cout << "vector_erase  : ";
    vector_erase(v, target);

    cout << "vector_insert : ";
    vector_insert(v, target);

    vector_resize(v, target);
}
