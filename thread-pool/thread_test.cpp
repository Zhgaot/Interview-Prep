#include <iostream>
#include <random>
#include <utility>
#include "thread_pool.hpp"

using namespace TP;

std::random_device rd; // 真实随机数产生器

std::mt19937 mt(rd()); //生成计算随机数mt

std::uniform_int_distribution<int> dist(-1000, 1000); //生成-1000到1000之间的离散均匀分布数

auto rnd = std::bind(dist, mt);

/* 设置线程睡眠时间 */
void simulate_hard_computation() {
    std::this_thread::sleep_for(std::chrono::milliseconds(2000 + rnd()));
}

/* 添加两个数字的简单函数并打印结果而没有返回值 */
// 普通函数
void multiply(const int a, const int b) {
    simulate_hard_computation();
    const int res = a * b;
    std::cout << a << " * " << b << " = " << res << std::endl;
}
// 仿函数
class MultiplyOperator {
public:
    void operator()(const int a, const int b) {
        simulate_hard_computation();
        const int res = a * b;
        std::cout << a << " * " << b << " = " << res << std::endl;
    }
};
// 成员函数
class MultiplyMebFunc {
public:
    MultiplyMebFunc(const int a, const int b) : a_(a), b_(b) {}
    void MultiplyMebFunc_func(bool c) {
        simulate_hard_computation();
        const int res = a_ * b_;
        std::cout << a_ << " * " << b_ << " = " << res << std::endl;
    }
private:
    int a_;
    int b_;
};

/* 添加并输出结果 */
void multiply_output(int &out, const int a, const int b)
{
    simulate_hard_computation();
    out = a * b;
    std::cout << a << " * " << b << " = " << out << std::endl;
}

/* 结果返回 */
int multiply_return(const int a, const int b)
{
    simulate_hard_computation();
    const int res = a * b;
    std::cout << a << " * " << b << " = " << res << std::endl;
    return res;
}

void example()
{
    // 创建3个线程的线程池
    ThreadPool pool(3);

    // 初始化线程池
    pool.init();

    // 提交乘法操作，总共10个
    for (int i = 1; i <= 2; ++i)
        for (int j = 1; j <= 5; ++j)
        {   
            pool.submit(multiply, i, j);
        }
    // 提交乘法操作，总共15个
    for (int i = 3; i <= 5; ++i)
        for (int j = 1; j <= 5; ++j)
        {   
            MultiplyOperator m;
            pool.submit(m, i, j);
        }
    // 提交乘法操作，总共15个
    for (int i = 6; i <= 8; ++i)
        for (int j = 1; j <= 5; ++j)
        {   
            MultiplyMebFunc* m = new MultiplyMebFunc(i, j);
            std::function<void(bool)> submit_func = std::bind(&MultiplyMebFunc::MultiplyMebFunc_func, m, std::placeholders::_1);
            pool.submit(submit_func, true);
        }

    // 使用ref传递的输出参数提交函数
    int output_ref;
    auto future1 = pool.submit(multiply_output, std::ref(output_ref), 5, 6);

    // 等待乘法输出完成
    future1.wait();
    std::cout << "Last operation result is equals to " << output_ref << std::endl;

    // 使用return参数提交函数
    auto future2 = pool.submit(multiply_return, 5, 3);

    // 等待乘法输出完成
    int res = future2.get();
    std::cout << "Last operation result is equals to " << res << std::endl;

    // 关闭线程池
    pool.shutdown();
}

int main() {

    example();

    return 0;
}