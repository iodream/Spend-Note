#pragma once

#include <utility>

#include "Net/Message.h"
#include "../libdal/Facade/IDbFacade.h"

class ICommandHandler
{
public:
	ICommandHandler(IDbFacade::Ptr facade) : m_facade{std::move(facade)} {}
    virtual ~ICommandHandler() {}

	virtual Net::Response Handle(Net::Request& request) = 0;

protected:
	IDbFacade::Ptr m_facade;
};
