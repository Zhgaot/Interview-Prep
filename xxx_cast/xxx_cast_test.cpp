#include <iostream>
#include <typeinfo>

using namespace std;

class Father {
public:
    virtual void call() {cout << "This is Father..." << endl;}
};
class Son : public Father {
public:
    Son() : Son_data(100) {}
    virtual void call() {cout << "This is Son..." << endl;}  // 子类重写父类虚函数
public:
    int Son_data;
};

/**
 * static_cast为静态转换，在编译期就进行转换，能完成大部分强转工作
*/
void static_cast_test() {
    cout << "=============== static_cast TEST ===============" << endl;

    /* 基本数据类型之间的转换 */
    int val = 10;
    char c = static_cast<char>(val);
    cout << typeid(c).name() << endl;  // type: c(char)
    double d = static_cast<double>(val);
    cout << typeid(d).name() << endl;  // type: d(double)

    /* 用于void*和其他指针类型之间的转换，但不能用于两个无关指针类型的转换 */
    int* p = new int(100);
    void* p_v = static_cast<void*>(p);      // OK: int* => void*
    char* p_c = static_cast<char*>(p_v);    // OK: void* => char*
    // double* p_d = static_cast<double*>(p);  // error: invalid static_cast

    /* 用于类间的上行转换，也可用于下行转换但是不具备动态类型检查，因此下行转换不安全 */
    Son* p_Son = new Son;
    Father* p_Father = static_cast<Father*>(p_Son);  // 上行转换：子类指针转换为父类指针
    // 父类的指针指向子类的对象，若子类重写父类虚函数，将发生多态
    p_Father->call();  // 发生多态：This is Son...

    cout << "=============== static_cast TEST ===============\n" << endl;
}

/**
 * dynamic_cast常用于类间的上行转换及下行转换，在运行期才进行转换而非编译期
 * 1. 上行转换与static_cast基本相同，但父类必须有虚函数
 * 2. 下行转换存在动态类型检查，在运行期间进行类型转换
 * 3. 普通类型的指针无法转换
*/
void dynamic_cast_test() {
    cout << "=============== dynamic_cast TEST ===============" << endl;

    /* 上行转换 */
    Son* p_Son1 = new Son;
    Father* p_Father1 = dynamic_cast<Father*>(p_Son1);
    p_Father1->call();  // 发生多态：This is Son...

    /* 下行转换(失败) */
    Father* p_Father2 = new Father;
    Son* p_Son2 = dynamic_cast<Son*>(p_Father2);
    // cout << p_Son2->Son_data << endl;  // error: Segmentation fault

    /* 下行转换(成功) */
    Father* p_Father3 = new Son;
    Son* p_Son3 = dynamic_cast<Son*>(p_Father3);
    cout << p_Son3->Son_data << endl;

    cout << "=============== dynamic_cast TEST ==============\n" << endl;
}

/**
 * const_cast仅用于去除指针或引用的常性，且能够去除底层的常性
*/
void const_cast_test() {
    cout << "=============== const_cast TEST ===============" << endl;

    /* 不可用于非指针类型 */
    const int i = 10;
    // int j = const_cast<int>(i);  // error: invalid use...which is not a pointer...

    /* 去除指针的常性 */
    const int val = 100;
    const int* c_p = &val;  // 常量指针：可改变指针的指向，但不可改变指针指向的值
    int* p = const_cast<int*>(c_p);  // 去除常量指针的常性
    *p = 200;
    // val作为const常量，在编译期在使用它的地方直接做了替换，因此val=100
    // p指向了val的地址，并修改了val的内存数据，因此*p=200
    cout << "&val = " << &val << ", val  = " << val  << endl;  // 100
    cout << "c_p  = " << c_p  << ", *c_p = " << *c_p << endl;  // 200
    cout << "p    = " << p    << ", *p   = " << *p   << endl;  // 200

    /* 去除指针的常性 */
    int init = 100;
    const int val2 = init;
    const int* c_p2 = &val2;
    int* p2 = const_cast<int*>(c_p2);
    *p2 = 200;
    cout << "&val2 = " << &val2 << ", val2  = " << val2  << endl;  // 200
    cout << "c_p2  = " << c_p2  << ", *c_p2 = " << *c_p2 << endl;  // 200
    cout << "p2    = " << p2    << ", *p2   = " << *p2   << endl;  // 200

    /* 去除指针的常性 */
    int a = 10;
    const int* const cpa = &a;
    int* pa = const_cast<int*>(cpa);
    *pa = 100;
    cout << *pa << endl;  // 100
    int b = 1000;
    pa = &b;
    cout << *pa << endl;  // 1000
    
    cout << "=============== const_cast TEST ===============\n" << endl;
}

/**
 * reinterpret_cast是对比特位的简单拷贝并重新解释，在编译期进行类型转换
*/
void reinterpret_cast_test() {
    cout << "=============== reinterpret_cast TEST ===============" << endl;
    
    /* 两个无关指针类型的转换 */
    int* p_i = new int;
    char* p_c = reinterpret_cast<char*>(p_i);  // static_cast无法完成

    /* 基础类型指针与类对象指针之间的转换 */
    Son son;
    cout << "son.Son_data = " << son.Son_data << endl;
    Son* p_son = &son;
    int* p = reinterpret_cast<int*>(p_son);
    cout << "*p = " << *p << endl;

    /* 将地址值转换成足够长的整型 */
    Father* p_Father = new Father;
    long long addr = reinterpret_cast<long long>(p_Father);
    cout << "p_Father = " << p_Father << endl;
    cout << "addr  = " << addr  << endl;

    cout << "=============== reinterpret_cast TEST ==============\n" << endl;
}

int main() {
    // static_cast_test();
    // dynamic_cast_test();
    // const_cast_test();
    reinterpret_cast_test();
    return 0;
}
