//
//  functions.cpp
//  pbscpp-task-2
//
//  Created by Павел Хомич on 23/11/2019.
//  Copyright © 2019 Павел Хомич. All rights reserved.
//

#include <cstdio>
#include <iostream>
#include <math.h>
#include <any>
#include "functions.h"

// Overloaded operators
std::shared_ptr<TFunction> operator+(std::shared_ptr<TFunction> a, std::any b) {
    std::shared_ptr<TFunction> bn;
    try {
        bn = std::any_cast<std::shared_ptr<TFunction>>(b);
    } catch (std::bad_cast& e) {
        throw std::logic_error("need ptr<TFunc> + ptr<TFunc>");
    }
    return std::make_shared<TFunctionPlus>(a, bn);
}
std::shared_ptr<TFunction> operator-(std::shared_ptr<TFunction> a, std::any b) {
    std::shared_ptr<TFunction> bn;
    try {
        bn = std::any_cast<std::shared_ptr<TFunction>>(b);
    } catch (std::bad_cast& e) {
        throw std::logic_error("need ptr<TFunc> - ptr<TFunc>");
    }
    return std::make_shared<TFunctionMinus>(a, bn);
}
std::shared_ptr<TFunction> operator*(std::shared_ptr<TFunction> a, std::any b) {
    std::shared_ptr<TFunction> bn;
    try {
        bn = std::any_cast<std::shared_ptr<TFunction>>(b);
    } catch (std::bad_cast& e) {
        throw std::logic_error("need ptr<TFunc> * ptr<TFunc>");
    }
    return std::make_shared<TFunctionMulti>(a, bn);
}
std::shared_ptr<TFunction> operator/(std::shared_ptr<TFunction> a, std::any b) {
    std::shared_ptr<TFunction> bn;
    try {
        bn = std::any_cast<std::shared_ptr<TFunction>>(b);
    } catch (std::bad_cast& e) {
        throw std::logic_error("need ptr<TFunc> / ptr<TFunc>");
    }
    return std::make_shared<TFunctionDiv>(a, bn);
}

// Indent
double TFunctionIndent::operator()(double x) const { return x; }
double TFunctionIndent::GetDeriv(double x) const { return 1.0; }
std::string TFunctionIndent::ToString() const { return std::string("x"); };

// Const
TFunctionConst::TFunctionConst(const std::any& param) : constant(std::any_cast<int>(param)) {};
double TFunctionConst::operator()(double x) const { return constant; }
double TFunctionConst::GetDeriv(double x) const { return 0.0; }
std::string TFunctionConst::ToString() const { return std::to_string(constant); };

// Power
TFunctionPower::TFunctionPower(const std::any& param) : power(std::any_cast<int>(param)) {};
double TFunctionPower::operator()(double x) const { return pow(x, power); }
double TFunctionPower::GetDeriv(double x) const { return (power*pow(x, power - 1)); }
std::string TFunctionPower::ToString() const {
    return std::string("x^") + std::to_string(power);
};

// Exp
double TFunctionExp::operator()(double x) const { return exp(x); }
double TFunctionExp::GetDeriv(double x) const { return exp(x); }
std::string TFunctionExp::ToString() const {
    return std::string("e^x");
};

// Polynomical
TFunctionPoly::TFunctionPoly(const std::any& param) : coef(std::any_cast<std::vector<int>>(param)) {};
double TFunctionPoly::operator()(double x) const {
    double result = 0.0;
    for (int i = 0; i < coef.size(); i++) {
        result += coef[i] * pow(x, i);
    }
    
    return result;
}
double TFunctionPoly::GetDeriv(double x) const {
    double result = 0.0;
    for (int i = 1; i < coef.size(); i++) {
        result += coef[i] * i * pow(x, i - 1);
    }

    return result;
}
std::string TFunctionPoly::ToString() const {
    std::string result = std::to_string(coef[0]);
    for (int i = 1; i < coef.size(); i++) {
        result += (std::string(" + ") + std::to_string(coef[i]) + "x^" + std::to_string(i));
    }
    
    return result;
};

// Plus
TFunctionPlus::TFunctionPlus(std::shared_ptr<TFunction> a, std::shared_ptr<TFunction> b) : f1(a), f2(b) {};
double TFunctionPlus::operator()(double x) const { return (*f1)(x) + (*f2)(x); }
double TFunctionPlus::GetDeriv(double x) const { return f1->GetDeriv(x) + f2->GetDeriv(x); }
std::string TFunctionPlus::ToString() const { return f1->ToString() + " + " + f2->ToString(); }

// Minus
TFunctionMinus::TFunctionMinus(std::shared_ptr<TFunction> a, std::shared_ptr<TFunction> b) : f1(a), f2(b) {};
double TFunctionMinus::operator()(double x) const { return (*f1)(x) - (*f2)(x); }
double TFunctionMinus::GetDeriv(double x) const { return f1->GetDeriv(x) - f2->GetDeriv(x); }
std::string TFunctionMinus::ToString() const { return f1->ToString() + " - " + f2->ToString(); }

// Multi
TFunctionMulti::TFunctionMulti(std::shared_ptr<TFunction> a, std::shared_ptr<TFunction> b) : f1(a), f2(b) {};
double TFunctionMulti::operator()(double x) const { return (*f1)(x) * (*f2)(x); }
double TFunctionMulti::GetDeriv(double x) const { return f1->GetDeriv(x) * (*f2)(x) + (*f1)(x) * f2->GetDeriv(x); }
std::string TFunctionMulti::ToString() const { return "(" + f1->ToString() + ") * (" + f2->ToString() + ")"; }

// Div
TFunctionDiv::TFunctionDiv(std::shared_ptr<TFunction> a, std::shared_ptr<TFunction> b) : f1(a), f2(b) {};
double TFunctionDiv::operator()(double x) const { return (*f1)(x) / (*f2)(x); }
double TFunctionDiv::GetDeriv(double x) const { return (f1->GetDeriv(x) * (*f2)(x) - (*f1)(x) * f2->GetDeriv(x)) / ((*f2)(x) * (*f2)(x)); }
std::string TFunctionDiv::ToString() const { return "(" + f1->ToString() + ") / (" + f2->ToString() + ")"; }

// FindRoot of function f(x) = 0 (func, initial, steps)
double findRoot(std::shared_ptr<TFunction> ptr, double init, int n) {
    double x = init;
    
    for (int i = 0; i <= n; i++) {
        x = x - (*ptr)(x)/ptr->GetDeriv(x);
    }
    
    return x;
}
