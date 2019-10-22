#include <iostream>

class A {
public:
    // ...
    static void * operator new(size_t size) {
        std::cout << "operator new!" << std::endl;
        return ::operator new(size);
    }
    static void operator delete(void *p, size_t size) {
        std::cout << "operator delete!" << std::endl;
        return ::operator delete(p);
} };

template <class T, class T2>
struct allocatorExtra {
    typedef T value_type;
    
    allocatorExtra() noexcept{}
    template <class TN, class TN2>
    allocatorExtra(const allocatorExtra<TN, TN2>& alloc) noexcept{}

    T* allocate(std::size_t n) {
        return static_cast<T*>(T2::operator new(n*sizeof(T)));
    }
    void deallocate(T* p, std::size_t n) {
        T2::operator delete(p, n*sizeof(T));
    }
};

int main() {
    allocatorExtra<A, A> alloc;
    auto sp = std::allocate_shared<A>(alloc);
    
    return 0;
}
