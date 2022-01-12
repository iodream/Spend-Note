#pragma once

#include <QObject>

#include "IHandler.h"

class LoginHandler : public IHandler
{
public:
    void Handle(std::any, MainWindow*) override;
};
