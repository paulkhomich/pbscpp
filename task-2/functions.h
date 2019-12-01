//
//  functions.h
//  pbscpp-task-2
//
//  Created by Павел Хомич on 23/11/2019.
//  Copyright © 2019 Павел Хомич. All rights reserved.
//

#ifndef functions_h
#define functions_h

#include <vector>
#include <any>

class TFunction {
public:
    virtual ~TFunction(){};
    virtual double operator()(double x) const = 0;
    virtual double GetDeriv(double x) const = 0;
    virtual std::string ToString() const = 0;
};

std::shared_ptr<TFunction> operator+(std::shared_ptr<TFunction>, std::any);
std::shared_ptr<TFunction> operator-(std::shared_ptr<TFunction>, std::any);
std::shared_ptr<TFunction> operator*(std::shared_ptr<TFunction>, std::any);
std::shared_ptr<TFunction> operator/(std::shared_ptr<TFunction>, std::any);

// Indent
class TFunctionIndent : public TFunction {
public:
    TFunctionIndent(const std::any& param) {};
    double operator()(double x) const override;
    double GetDeriv(double x) const override;
    std::string ToString() const override;
};

// Const
class TFunctionConst : public TFunction {
    int constant;
public:
    TFunctionConst(const std::any& param);
    double operator()(double x) const override;
    double GetDeriv(double x) const override;
    std::string ToString() const override;
};

// Power
class TFunctionPower : public TFunction {
    int power;
public:
    TFunctionPower(const std::any& param);
    double operator()(double x) const override;
    double GetDeriv(double x) const override;
    std::string ToString() const override;
};

// Exp
class TFunctionExp : public TFunction {
public:
    TFunctionExp(const std::any& param) {};
    double operator()(double x) const override;
    double GetDeriv(double x) const override;
    std::string ToString() const override;
};

// Poly
class TFunctionPoly : public TFunction {
    std::vector<int> coef;
public:
    TFunctionPoly(const std::any& param);
    double operator()(double x) const override;
    double GetDeriv(double x) const override;
    std::string ToString() const override;
};

// Plus
class TFunctionPlus : public TFunction {
    std::shared_ptr<TFunction> f1;
    std::shared_ptr<TFunction> f2;
public:
    TFunctionPlus(std::shared_ptr<TFunction> a, std::shared_ptr<TFunction> b);
    double operator()(double x) const override;
    double GetDeriv(double x) const override;
    std::string ToString() const override;
};

// Minus
class TFunctionMinus : public TFunction {
    std::shared_ptr<TFunction> f1;
    std::shared_ptr<TFunction> f2;
public:
    TFunctionMinus(std::shared_ptr<TFunction> a, std::shared_ptr<TFunction> b);
    double operator()(double x) const override;
    double GetDeriv(double x) const override;
    std::string ToString() const override;
};

// Multi
class TFunctionMulti : public TFunction {
    std::shared_ptr<TFunction> f1;
    std::shared_ptr<TFunction> f2;
public:
    TFunctionMulti(std::shared_ptr<TFunction> a, std::shared_ptr<TFunction> b);
    double operator()(double x) const override;
    double GetDeriv(double x) const override;
    std::string ToString() const override;
};

// Div
class TFunctionDiv : public TFunction {
    std::shared_ptr<TFunction> f1;
    std::shared_ptr<TFunction> f2;
public:
    TFunctionDiv(std::shared_ptr<TFunction> a, std::shared_ptr<TFunction> b);
    double operator()(double x) const override;
    double GetDeriv(double x) const override;
    std::string ToString() const override;
};

// FindRoot(func, initial, steps)
double findRoot(std::shared_ptr<TFunction>, double, int);

#endif /* functions_h */
