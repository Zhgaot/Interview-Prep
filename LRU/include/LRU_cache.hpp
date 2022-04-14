#pragma once
#include <unordered_map>

template <typename KeyType, typename ValType>
class LRUCache {
public:
    LRUCache(const int& _capacity);
    bool get(const KeyType& key, ValType& out_val);
    void set(const KeyType& key, const ValType& val);

private:
    void add_to_head_(DListNode_*& node);
    void remove_node_(DListNode_*& node);
    void move_to_head_(DListNode_*& node);
    DListNode_* delete_node_();

private:
    int capacity_;
    int size_;
    struct DListNode_ {
        KeyType key;
        ValType val;
        DListNode_* prev;  // previous DListNode_ pointer
        DListNode_* next;  // next DListNode_ pointer
        DListNode_() : prev(nullptr), next(nullptr) {}  // Cannot initialize key and val
        DListNode_(const KeyType& _key, const ValType& _val) : \
            key(_key), val(_val), prev(nullptr), next(nullptr) {}
        DListNode_(const KeyType& _key, const ValType& _val,
                   const DListNode_*& _prev, const DListNode_*& _next) : \
            key(_key), val(_val), prev(_prev), next(_next) {}
    };
    DListNode_* head_;
    DListNode_* tail_;
    std::unordered_map<KeyType, DListNode_*> hash_table_;
};

template <typename KeyType, typename ValType>
LRUCache<KeyType, ValType>::LRUCache(const int& _capacity) : capacity_(_capacity), size_(0) {
    this->head_ = new DListNode_();
    this->tail_ = new DListNode_();
    this->head_->next = this->tail;
    this->head_->prev = nullptr;
    this->tail_->prev = this->head_;
    this->tail_->next = nullptr;
}

template <typename KeyType, typename ValType>
bool LRUCache<KeyType, ValType>::get(const KeyType& key, ValType& out_val) {
    if (this->hash_table_.find(key) != this->hash_table_.end()) {
        // Bingo! find it!
        DListNode_* node = this->hash_table_[key];
        out_val = node->key;
        this->move_to_head_(node);
        return true;
    } else {
        // Cannot find it...
        return false;
    }
}
