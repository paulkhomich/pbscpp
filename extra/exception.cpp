#include <iostream>
#include <gtest/gtest.h>

// Exceptions
class TMyExceptionEQ : public std::exception {
    std::string info;
public:
    TMyExceptionEQ() : info("EQERR") {}
    virtual const char* what() const throw () override {
        return info.c_str();
    }
    virtual TMyExceptionEQ& operator<<(const std::string& msg) {
        this->info += ": " + msg;
        return *this;
    }
};

class TMyExceptionEQANDZ : public TMyExceptionEQ {
public:
    TMyExceptionEQANDZ& operator<<(const std::string& msg) override {
        TMyExceptionEQ::operator<<(msg);
        return *this;
    }
};

// "Sum" function
int sum(int a, int b) {
    if (a == b && a == 0 && b == 0)
        throw TMyExceptionEQANDZ() << "sum(): a and b are equal and zero";
    else if (a == b)
        throw TMyExceptionEQ() << "sum(): a and b are equal";
    return a + b;
}

// Testing
TEST(MyTest, TestThrowEQANDZ) {
    EXPECT_THROW(sum(0,0), TMyExceptionEQANDZ);
}

TEST(MyTest, TestThrowEQ) {
    EXPECT_THROW(sum(2,2), TMyExceptionEQ);
}

TEST(MyTest, TestNoThrow) {
    EXPECT_NO_THROW(sum(3,4));
}

int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
