//
//  main.cpp
//  pbscpp-task-2
//
//  Created by Павел Хомич on 23/11/2019.
//  Copyright © 2019 Павел Хомич. All rights reserved.
//

#include <iostream>
#include <gtest/gtest.h>
#include "factory.h"

TEST(FuncTest, TestCreation) {
    FuncFactory factory;
    EXPECT_NO_THROW(factory.CreateFunc("polynomial", std::vector<int>{1,5,-3}));
    EXPECT_NO_THROW(factory.CreateFunc("indent"));
    EXPECT_NO_THROW(factory.CreateFunc("const", 17));
    EXPECT_NO_THROW(factory.CreateFunc("power", 4));
    EXPECT_NO_THROW(factory.CreateFunc("exp"));
    EXPECT_NO_THROW({
        auto g = factory.CreateFunc("polynomial", std::vector<int>{1,5,-3});
        auto f = factory.CreateFunc("indent");
        auto s = g + f;
    });
    EXPECT_NO_THROW({
        auto g = factory.CreateFunc("const", 17);
        auto f = factory.CreateFunc("indent");
        auto s = g - f;
    });
    EXPECT_NO_THROW({
        auto g = factory.CreateFunc("power", 4);
        auto f = factory.CreateFunc("power", 2);
        auto s = g * f;
    });
    EXPECT_NO_THROW({
        auto g = factory.CreateFunc("indent");
        auto f = factory.CreateFunc("exp");
        auto s = g / f;
    });
}

TEST(FuncTest, TestThrow) {
    FuncFactory factory;
    EXPECT_THROW(factory.CreateFunc("polynomial", std::vector<double>{1,5,-3}), std::bad_cast);
    EXPECT_THROW(factory.CreateFunc("polynomial", 2), std::bad_cast);
    EXPECT_THROW(factory.CreateFunc("const"), std::bad_cast);
    EXPECT_THROW(factory.CreateFunc("power", 2.4), std::bad_cast);
    EXPECT_THROW({
        auto f = factory.CreateFunc("indent");
        auto g = f + "23";
    }, std::logic_error);
     EXPECT_THROW({
        auto f = factory.CreateFunc("power", 2);
        auto g = f + 10;
    }, std::logic_error);
}

TEST(FuncTest, TestResults) {
    FuncFactory factory;
    EXPECT_EQ(256, (*factory.CreateFunc("power", 4))(4));
    EXPECT_EQ(729, (*factory.CreateFunc("power", 6))(3));
    EXPECT_EQ(2019, (*factory.CreateFunc("indent"))(2019));
    EXPECT_NEAR(7.38, (*factory.CreateFunc("exp"))(2), 0.01);
    EXPECT_EQ(2019, (*factory.CreateFunc("const", 2019))(1997));
    EXPECT_EQ(17, (*factory.CreateFunc("polynomial", std::vector<int>{1,2,3}))(2));
}

TEST(FuncTest, TestDeriv) {
    FuncFactory factory;
    EXPECT_EQ(32, factory.CreateFunc("power", 4)->GetDeriv(2));
    EXPECT_EQ(1, factory.CreateFunc("indent")->GetDeriv(2));
    EXPECT_EQ(0, factory.CreateFunc("const", 20)->GetDeriv(2));
    EXPECT_NEAR(7.38, factory.CreateFunc("exp")->GetDeriv(2), 0.01);
    EXPECT_EQ(14, factory.CreateFunc("polynomial", std::vector<int>{1,2,3})->GetDeriv(2));
}

TEST(FuncTest, TestRoot) {
    FuncFactory factory;
    auto poly = factory.CreateFunc("polynomial", std::vector<int>{1,2,-5});
    EXPECT_NEAR(0.68, findRoot(poly, 1.0, 50), 0.01);
    EXPECT_NEAR(-0.28, findRoot(poly, 0.0, 50), 0.01);

    auto indent = factory.CreateFunc("indent");
    auto sum = poly * indent;
    EXPECT_NEAR(-0.28, findRoot(sum, -1.0, 50), 0.01);
    EXPECT_NEAR(0, findRoot(sum, 0.25, 50), 0.01);
    EXPECT_NEAR(0.68, findRoot(sum, 1.0, 50), 0.01);

    auto multi = indent * indent * indent;
    EXPECT_NEAR(0.0, findRoot(multi, 1.0, 12), 0.01);
}

int main(int argc, char * argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
