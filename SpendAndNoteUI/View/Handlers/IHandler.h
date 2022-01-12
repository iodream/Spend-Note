#pragma once

#include <any>
#include "./View/MainWindow.h"

class IHandler
{
public:
    virtual void Handle(std::any, MainWindow*) = 0;
};
