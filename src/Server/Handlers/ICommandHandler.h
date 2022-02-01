#pragma once

#include <utility>

#include "Net/Message.h"
#include "../libdal/Facade/IDbFacade.h"
#include "../Params.h"

class ICommandHandler
{
public:
	ICommandHandler() {}
	virtual ~ICommandHandler() {}

	virtual Net::Response Handle(Net::Request& request) = 0;

	void set_facade(IDbFacade::Ptr&& facade) { m_facade = std::move(facade); }
	void set_params(Params&& params) { m_params = std::move(params); }

protected:
	IDbFacade::Ptr m_facade;
	Params m_params;
};
