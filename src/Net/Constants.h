#pragma once

#include <string>
#include <vector>

namespace Net {

using HTTPMethod = std::string;

const HTTPMethod HTTP_METHOD_GET = "GET";
const HTTPMethod HTTP_METHOD_POST = "POST";
const HTTPMethod HTTP_METHOD_PUT = "PUT";
const HTTPMethod HTTP_METHOD_DELETE = "DELETE";

using ContentType = std::string;

const ContentType CONTENT_TYPE_PLAIN_TEXT = "text/plain; charset=UTF-8";
const ContentType CONTENT_TYPE_APPLICATION_JSON = "application/json";
const ContentType CONTENT_TYPE_EMPTY = "";

using AuthSchemeType = std::string;

const AuthSchemeType AUTH_SCHEME_TYPE_BEARER = "Bearer";

const std::string DUMMY_PASSWORD = "0123456789ABCDEF0123456789ABCDEF";

const std::string VERIFICATION_FAILED = "Verification failed";

const int SALT_SIZE = 6;

const std::vector<char> SALT_CHARACTERS
{
	'!', '"', '#','$', '%', '&', '\'', '(', ')', '*', '+', ',', '.', '/',
	'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', ':', ';', '<', '=', '>', '?',
	'@', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O',
	'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '[', '\\', ']', '^', '_',
	'`', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o',
	'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '{', '|', '}', '~' };
}
