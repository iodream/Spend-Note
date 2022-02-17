#include "DbConnectionHelper.h"

std::string DbConnectionHelper::FormConnectionString(const Poco::Util::JSONConfiguration& config) const
{
	return
		USER + "=" + config.getString(USER) + " " +
		HOST + "=" + config.getString(HOST) + " " +
		PASSWORD + "=" + config.getString(PASSWORD) + " " +
		DBNAME + "=" + config.getString(DBNAME);
}
