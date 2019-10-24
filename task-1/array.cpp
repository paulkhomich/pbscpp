#include <iostream>
#include <vector>

template <typename T>
class Array {
private:
    T* data;
    size_t size;
    
public:
    Array(size_t n)
    : size(n)
    {
        data = new T[n];
    }
    
    T& operator[](size_t i) {
        return data[i];
    }
    
    const T& operator[](size_t i) const {
        return data[i];
    }
    
    // Перегрузил присваивание, так как при его отсутствии у "первообразного" массива
    // терялись его собственные data, что приводило к удалению памяти у временного объекта
    // а после удаление этой же памяти у "первообразного" (Что вызывало ошибку)
    // Решение — не перемещать указатель, а скопировать значения из временного в "первообразный"
    const Array& operator=(const Array& el) {
        for (size_t i = 0; i < (*this).GetSize(); i++)
            data[i] = el[i];
        
        return *this;
    }
    
    // При добавлении push_back'ом, каждый раз происходит удвоение capacity, а при удвоении
    // происходит копирование старых элементов в новые, на 1ом вызове все ОК, на втором
    // B копируется в новый вектор и происходит его destruct, соответственно на 3ем вызове
    // происходит ошибка — память уже очищена, а ее еще раз destruct'ят
    // Решение — при копировании создать новый объект с персональной data, чтобы после
    // destruct'ились уже эти новые data-области
    Array(const Array& el) : size(el.GetSize()) {
        data = new T[size];
        for (size_t i = 0; i < size; i++)
            data[i] = el[i];
    }
    
    const size_t GetSize() const {
        return size;
    }
    
    ~Array() {
        delete[] data;
    }
};

template <typename T>
Array<T> GetArray(size_t n, T x) {
    Array<T> A(n);
    for (size_t i = 0; i != n; ++i) {
        A[i] = x;
    }
    return A;
}

template <typename T>
std::ostream& operator<<(std::ostream& out, const Array<T>& A) {
    for (size_t i = 0; i != A.GetSize(); ++i) {
        out << A[i] << " ";
    }
    out << "\n";
    return out;
}

int main() {
    size_t n;
    std::cin >> n;
    Array<int> A(n);
    A = GetArray<int>(n, 0);
    // print the array
    std::cout << A << "\n";

    std::vector<Array<int>> vec;
    Array<int> B(n);
    // fill vector of 100 arrays
    for (size_t i = 0; i < 100; ++i) {
        B = GetArray<int>(n, i);
        vec.push_back(B);
    }
}
