#include "atoi.h"

using namespace myatoi;

namespace myatoi {
class AtoiStateMechine {
public:
    AtoiStateMechine();
    int get_res();
    void set(const char& ch);
    
private:
    int get_col_(const char& ch);
    
private:
    short sign_;
    long long number_;
    std::string cur_state_;
    std::unordered_map<std::string, std::vector<std::string>> state_table_;
};

inline AtoiStateMechine::AtoiStateMechine() : \
    sign_(1), number_(0), cur_state_("start") {
        this->state_table_ = {
                {"start", {"start", "signed", "in_number", "end"}},
                {"signed", {"end", "end", "in_number", "end"}},
                {"in_number", {"end", "end", "in_number", "end"}},
                {"end", {"end", "end", "end", "end"}}
        };
    }

inline int AtoiStateMechine::get_res() {
        return this->sign_ * this->number_;
    }

inline void AtoiStateMechine::set(const char& ch) {
        this->cur_state_ = this->state_table_[this->cur_state_][this->get_col_(ch)];
        if (this->cur_state_ == "signed") {
            this->sign_ = ch == '+' ? 1 : -1;
        } else if (this->cur_state_ == "in_number") {
            this->number_ = this->number_ * 10 + (ch - '0');
            this->number_ = this->sign_ == 1 ? \
            std::min(this->number_, static_cast<long long>(INT_MAX)) : \
            std::min(this->number_, -static_cast<long long>(INT_MIN));  // <limits.h>
        }
    }

inline int AtoiStateMechine::get_col_(const char& ch) {
        if (isspace(ch)) {  // <cctype>
            return 0;
        } else if (ch == '+' || ch == '-') {
            return 1;
        } else if (isdigit(ch)) {  // <cctype>
            return 2;
        } else {
            return 3;
        }
    }

int Atoi(const std::string& str) {
    AtoiStateMechine atoi_state_mechine;
    for (const char ch : str) {
        atoi_state_mechine.set(ch);
    }
    return atoi_state_mechine.get_res();
}

int Atoi(const char* c_str, const int& size) {
    AtoiStateMechine atoi_state_mechine;
    for (int i = 0; i < size; ++i) {
        atoi_state_mechine.set(c_str[i]);
    }
    return atoi_state_mechine.get_res();
}
}
