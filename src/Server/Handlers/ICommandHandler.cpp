#include "ICommandHandler.h"

#include "../Error.h"
#include "../libdal/Exceptions/DatabaseFailure.h"
#include "../../Net/Parsing.h"

Net::Response ICommandHandler::SafeHandle(Net::Request& request){
	try {
		return Handle(request);
	}
	catch (const db::DatabaseFailure& ex) {
		throw InternalError(ex.what());
	}
	catch (const ParsingError& ex) {
		throw BadRequestError(ex.what());
	}
}

void ICommandHandler::set_facade(db::IDbFacade::Ptr&& facade)
{
	m_facade = std::move(facade);
}

void ICommandHandler::set_params(Params&& params)
{
	m_params = std::move(params);
}
