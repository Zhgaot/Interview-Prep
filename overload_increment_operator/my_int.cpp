#include <iostream>

using namespace std;

/**
 * @brief
 * - 实现一个仿int的数据类型
 * - 内部重载了前置++与后置++运算符
 * - 另有作为友元的全局函数帮助实现cout输出
*/
class Int {
    friend ostream& operator<<(ostream& out, const Int& out_Int);
public:
    Int() : data_(0) {}
    Int(const int& out_int) : data_(out_int) {}
    Int& operator++() {
        /* 前置递增 */
        ++(this->data_);
        return *this;
    }
    Int operator++(int) {
        /* 后置递增 */
        Int temp_obj = *this;
        ++(this->data_);
        return temp_obj;
    }
private:
    int data_;
};

ostream& operator<<(ostream& out, const Int& out_Int) {
    out << out_Int.data_;
    return out;
}

void test() {
    Int i1;
    cout << ++(++i1) << endl;  // 2

    // error: 非常量引用的初始值必须为左值
    // Int& i2 = i1++;
    const Int& i2 = i1++;
    cout << i2 << endl;
    cout << i1 << endl;
}

int main() {
    test();
    return 0;
}
