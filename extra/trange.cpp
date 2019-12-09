#include <iostream>
#include <iterator>
#include <optional>
#include <unordered_set>

class TRange {
    int64_t be;
    int64_t en;
    int64_t st;
public:
    class const_iterator {
        int64_t val;
        int64_t step;
        public:
            using iterator_category = std::forward_iterator_tag;
            using value_type = int64_t;
            using difference_type = int64_t;
            using pointer = int64_t*;
            using reference = int64_t&;
        
            const_iterator(const int64_t& v, const int64_t& s) : val(v), step(s) {};
        
            const int64_t& operator*() const {
                return this->val;
            }
            bool operator==(const const_iterator& who) const {
                return (this->val == who.val);
            }
            bool operator!=(const const_iterator& who) const {
                return !(*this == who);
            }
            const_iterator& operator++() {
                this->val += step;
                return *this;
            }
            const_iterator operator++(int) {
                const_iterator temp = *this;
                ++*this;
                return temp;
            }
    };

    TRange(const int64_t& n, const int64_t& m, const int64_t& s) {
        if (s == 0)
            throw std::logic_error("s must be non-zero");
        else {
            be = n;
            en = s > 0 ? m - (m - n) % s : m + (n - m) % s;
            st = s;
        }
    }
    bool operator==(const TRange& who) const {
        return (this->be == who.be && this->en == who.en);
    }
    bool operator!=(const TRange& who) const {
        return !(*this == who);
    }
    int64_t GetSize() const {
        return (en - be) / st + 1;
    }
    std::optional<int64_t> operator[](const int64_t& i) const {
        if (i < GetSize())
            return be + i*st;
        return std::nullopt;
    }
    const_iterator begin() {
        return const_iterator(be, st);
    }
    const_iterator end() {
        return const_iterator((en + st), st);
    }
};

class RangeHash {
public:
    size_t operator()(const TRange& ranger) const {
        return ranger.GetSize();
    }
};

int main(int argc, const char * argv[]) {
    auto p = TRange(1, 8, 3);
    auto r = TRange(108, 83, -4);
    auto z = TRange(2, 2, 2);
    
    // positive iteration
    std::cout << "p Size: " << p.GetSize() << "\n";
    std::cout << "p[0] = " << *p[0] << ", p[2] = " << *p[2] << "\n";
    for (auto it = p.begin(); it != p.end(); it++) {
        std::cout << *it << "\n";
    }
    
    // negative iteration
    std::cout << "r Size: " << r.GetSize() << "\n";
    std::cout << "r[0] = " << *r[0] << ", r[2] = " << *r[2] << "\n";
    for (auto it = r.begin(); it != r.end(); it++) {
        std::cout << *it << "\n";
    }
    
    // unordered_set
    std::unordered_set<TRange, RangeHash> uset;
    uset.insert(p);
    uset.insert(r);
    for (auto el : uset) {
        std::cout << "uset: " << el.GetSize() << "\n";
    }
    
    return 0;
}
