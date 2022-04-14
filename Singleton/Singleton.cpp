#include <iostream>
#include <mutex>
#include <thread>

/* =============== 懒汉-单例模式 =============== */
class LazySingleton {
public:
    static LazySingleton* get_instance();
    void print_address() {
        std::cout << this << std::endl;
    }

private:
    static LazySingleton* m_instance_;
    LazySingleton() {}
};

LazySingleton* LazySingleton::m_instance_ = nullptr;
LazySingleton* LazySingleton::get_instance() {
    if (m_instance_ == nullptr) {
        m_instance_ = new LazySingleton();
    }
    return m_instance_;
}
/* =============== 懒汉-单例模式 =============== */


/* =============== 懒汉-加锁-单例模式 =============== */
class LazyLockSingleton {
public:
    static LazyLockSingleton* get_instance();
    void print_address() {
        std::cout << this << std::endl;
    }

private:
    static LazyLockSingleton* m_instance_;
    static std::mutex mutex_;
    LazyLockSingleton() {};
};

LazyLockSingleton* LazyLockSingleton::m_instance_ = nullptr;
std::mutex LazyLockSingleton::mutex_;
LazyLockSingleton* LazyLockSingleton::get_instance() {
    {
        std::lock_guard<std::mutex> guard(mutex_);
        if (m_instance_ == nullptr) {
            m_instance_ = new LazyLockSingleton();
        }
    }
    return m_instance_;
    
}
/* =============== 懒汉-加锁-单例模式 =============== */


/* =============== 饿汉-单例模式 =============== */
class HungrySingleton {
public:
    static HungrySingleton* get_instance();
    void print_address() {
        std::cout << this << std::endl;
    }

private:
    static HungrySingleton* m_instance_;
    HungrySingleton() {}
};

HungrySingleton* HungrySingleton::m_instance_ = new HungrySingleton();
HungrySingleton* HungrySingleton::get_instance() {
    return m_instance_;
}
/* =============== 饿汉-单例模式 =============== */


void test_LazySingleton() {
    LazySingleton::get_instance()->print_address();
    LazySingleton* lazy_1 = LazySingleton::get_instance();
    LazySingleton* lazy_2 = LazySingleton::get_instance();
    lazy_1->print_address();
    lazy_2->print_address();
}

void test_aux() {
    for (int i = 0; i < 100000; ++i)
        LazyLockSingleton::get_instance()->print_address();
}

void test_LazyLockSingleton() {
    std::thread thread_1(test_aux);
    std::thread thread_2(test_aux);
    thread_1.join();
    thread_2.join();
}

int main() {
    // test_LazySingleton();
    test_LazyLockSingleton();
    return 0;
}
