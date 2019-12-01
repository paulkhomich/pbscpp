//
//  factory.cpp
//  pbscpp-task-2
//
//  Created by Павел Хомич on 23/11/2019.
//  Copyright © 2019 Павел Хомич. All rights reserved.
//

#include <iostream>
#include <map>
#include <any>
#include "factory.h"
#include "functions.h"

class FuncFactory::TImpl {
    class ICreator {
    public:
        virtual ~ICreator(){};
        virtual std::shared_ptr<TFunction> Create(const std::any& param) const = 0;
    };

    using TCreatorPtr = std::shared_ptr<ICreator>;
    using TRegisteredCreators = std::map<std::string, TCreatorPtr>;
    TRegisteredCreators RegisteredCreators;

public:
    template <class TCurrentFunc>
    class TCreator : public ICreator {
        std::shared_ptr<TFunction> Create(const std::any& param) const override {
            return std::make_unique<TCurrentFunc>(param);
        }
    };

    TImpl() { RegisterAll(); }

    template <typename T>
    void RegisterCreator(const std::string& name) {
        RegisteredCreators[name] = std::make_shared<TCreator<T>>();
    }

    void RegisterAll() {
        RegisterCreator<TFunctionIndent>("indent");
        RegisterCreator<TFunctionConst>("const");
        RegisterCreator<TFunctionPower>("power");
        RegisterCreator<TFunctionExp>("exp");
        RegisterCreator<TFunctionPoly>("polynomial");
    }

    std::shared_ptr<TFunction> CreateFunc(const std::string& name, const std::any& param) const {
        auto creator = RegisteredCreators.find(name);
        if (creator == RegisteredCreators.end())
            return nullptr;

        return creator->second->Create(param);
    }

    std::vector<std::string> GetAvailableFunctions() const {
        std::vector<std::string> result;
        for (const auto& creatorPair : RegisteredCreators)
            result.push_back(creatorPair.first);

        return result;
    }
};

FuncFactory::FuncFactory() : Impl(std::make_unique<FuncFactory::TImpl>()) {}
FuncFactory::~FuncFactory() {}

std::shared_ptr<TFunction> FuncFactory::CreateFunc(const std::string& name, const std::any& param) const {
    return Impl->CreateFunc(name, param);
}

std::vector<std::string> FuncFactory::GetAvailableFunctions() const {
    return Impl->GetAvailableFunctions();
}
