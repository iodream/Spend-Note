#pragma once

#include <string>

namespace Net {

using HTTPMethod = std::string;

const HTTPMethod HTTP_METHOD_GET = "GET";
const HTTPMethod HTTP_METHOD_POST = "POST";
const HTTPMethod HTTP_METHOD_DELETE = "DELETE";

using ContentType = std::string;

const ContentType CONTENT_TYPE_PLAIN_TEXT = "text/plain; charset=UTF-8";
const ContentType CONTENT_TYPE_APPLICATION_JSON = "application/json";
const ContentType CONTENT_TYPE_EMPTY = "";

using AuthSchemeType = std::string;

const AuthSchemeType AUTH_SCHEME_TYPE_BEARER = "Bearer";

const std::string DUMMY_PASSWORD = "0123456789ABCDEF0123456789ABCDEF";

}
