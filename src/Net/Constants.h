#pragma once

#include <string>

namespace Net {

using HTTPMethod = std::string;

extern const HTTPMethod HTTP_METHOD_GET;
extern const HTTPMethod HTTP_METHOD_POST;

using ContentType = std::string;

extern const ContentType CONTENT_TYPE_PLAIN_TEXT;
extern const ContentType CONTENT_TYPE_APPLICATION_JSON;
extern const ContentType CONTENT_TYPE_EMPTY;

using AuthSchemeType = std::string;

extern const AuthSchemeType AUTH_SCHEME_TYPE_BEARER;

}
