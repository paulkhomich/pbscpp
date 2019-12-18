#include <iostream>

template <char ...c> struct TString {
    static constexpr char data[sizeof...(c)] = {c...};
    constexpr operator const char* () const { return data; }
    
    template <char ...add> constexpr
    auto operator+(TString<add...> const &) const {
        return TString<c..., add...>();
    }
};

template <typename Char, Char ...c>
constexpr auto operator"" _s() { return TString<c...>(); }

int main(int argc, const char * argv[]) {
    constexpr auto hello = "hello"_s + " world"_s;
    static_assert(hello == "hello world"_s);
    
    std::cout << hello.data << std::endl;
    
    return 0;
}
