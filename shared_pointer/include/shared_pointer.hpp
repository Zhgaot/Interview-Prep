#pragma once
#include <iostream>

template <typename T>
class SharedPointer {
public:
    SharedPointer(T* p = nullptr);
    ~SharedPointer();
    SharedPointer(const SharedPointer<T>& other);
    SharedPointer<T>& operator=(const SharedPointer<T>& other);
private:
    T* ptr_;
    unsigned int* count_;
};

template <typename T>
SharedPointer<T>::SharedPointer(T* p) {
    this->ptr_ = p;
    this->count_ = new unsigned int(0);
    ++(*this->count_);
    std::cout << "Constructor is succeed" << std::endl;
}

template <typename T>
SharedPointer<T>::~SharedPointer() {
    --(*this->count_);
    if (*this->count_ == 0) {
        delete[] this->ptr_;
        this->ptr_ = nullptr;
        delete[] this->count_;
        this->count_ = nullptr;
        std::cout << "Delete pointer is succeed" << std::endl;
    }
    std::cout << "Destructor is succeed" << std::endl;
}

template <typename T>
SharedPointer<T>::SharedPointer(const SharedPointer<T>& other) {
    this->ptr_ = other.ptr_;
    this->count_ = other.count_;
    ++(*this->count_);
    std::cout << "Copy Constructor is succeed" << std::endl;
}

template <typename T>
SharedPointer<T>& SharedPointer<T>::operator=(const SharedPointer<T>& other) {
    if (this = &other)
        return *this;
    --(*this->count_);
    if (*this->count_ == 0) {
        delete[] this->ptr_;
        this->ptr_ = nullptr;
        delete[] this->count_;
        this->count_ = nullptr;
    }
    this->ptr_ = other.ptr_;
    this->count_ = other.ptr_;
    ++(*this->count_);
    std::cout << "Assignment operator overload is succeed" << std::endl;
    return *this;
}
