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

template <class T>
struct allocatorExtra {
    typedef T value_type;
    allocatorExtra() noexcept{}
    
    template <class TN> allocatorExtra(const allocatorExtra<TN>& alloc) noexcept{}

    T* allocate(std::size_t n) {
        return static_cast<T*>(A::operator new(n*sizeof(T)));
    }
    void deallocate(T* p, std::size_t n) {
        A::operator delete(p, n*sizeof(T));
    }
};

int main() {
    allocatorExtra<A> alloc;
    auto up = std::allocate_shared<A>(alloc);
    
    return 0;
}
