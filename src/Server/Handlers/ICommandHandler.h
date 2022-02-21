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
	Net::Response SafeHandle(Net::Request& request);

	void set_facade(db::IDbFacade::Ptr&& facade);
	void set_params(Params&& params);

protected:
	db::IDbFacade::Ptr m_facade;
	Params m_params;
};
