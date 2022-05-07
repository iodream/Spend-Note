#include "Utils.h"
#include "Logger/ScopedLogger.h"

#include <string>
#include "Poco/DigestStream.h"
#include "Poco/SHA1Engine.h"

Net::Response FormErrorResponse(
	Poco::Net::HTTPServerResponse::HTTPStatus status,
	std::string reason)
{
	SCOPED_LOGGER;
	Net::Response response;
	response.content_type = Net::CONTENT_TYPE_PLAIN_TEXT;
	if (reason.size())
		response.reason = reason;
	response.status = status;
	return response;
}


Net::Response FormErrorResponse(
	Poco::Net::HTTPServerResponse::HTTPStatus status,
	const char* reason)
{
	SCOPED_LOGGER;
	return FormErrorResponse(status, std::string(reason));
}

std::string HashingPassword(const std::string& password, const std::string& salt)
{
	std::string hashed_password;

	Poco::SHA1Engine sha1;
	Poco::DigestOutputStream ostr(sha1);
	ostr << password + salt;
	ostr.flush();

	const Poco::DigestEngine::Digest& digest = sha1.digest();
	hashed_password = Poco::DigestEngine::digestToHex(digest);

	return hashed_password;
}

std::string CreateSalt()
{
	std::string salt;

	std::sample(Net::SALT_CHARACTERS.begin(), Net::SALT_CHARACTERS.end(), std::back_inserter(salt),
		Net::SALT_SIZE, std::mt19937{std::random_device{}()});

	return salt;
}
