//
//  factory.h
//  pbscpp-task-2
//
//  Created by Павел Хомич on 23/11/2019.
//  Copyright © 2019 Павел Хомич. All rights reserved.
//

#ifndef factory_h
#define factory_h

#include "functions.h"
#include <any>

class FuncFactory {
    class TImpl;
    std::unique_ptr<const TImpl> Impl;
    
public:
    FuncFactory();
    ~FuncFactory();
    std::shared_ptr<TFunction> CreateFunc(const std::string& name, const std::any& param = nullptr) const;
    std::vector<std::string> GetAvailableFunctions() const;
};


#endif /* factory_h */
