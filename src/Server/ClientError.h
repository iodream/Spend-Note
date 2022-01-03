#pragma once

#include "Poco/Net/HTTPServerResponse.h"

#include "../Exception.h"

class ClientError : public Exception {
public:
    using Status = Poco::Net::HTTPServerResponse::HTTPStatus;
    explicit ClientError(const char* message, Status status)
        : Exception(message), m_status(status) {}

    explicit ClientError(const std::string& message, Status status)
        : Exception(message), m_status(status) {}

    virtual ~ClientError() noexcept {}

    Poco::Net::HTTPServerResponse::HTTPStatus get_status() const
    {
        return m_status;
    }
private:
     Status m_status;
};

class BadRequestError : public ClientError
{
public:
    explicit BadRequestError(const char* message)
        : ClientError(message, Status::HTTP_BAD_REQUEST) {}

    explicit BadRequestError(const std::string& message)
        : ClientError(message, Status::HTTP_BAD_REQUEST) {}

    virtual ~BadRequestError() noexcept {}
};

class ForbiddenError : public ClientError
{
public:
    explicit ForbiddenError(const char* message)
        : ClientError(message, Status::HTTP_FORBIDDEN) {}

    explicit ForbiddenError(const std::string& message)
        : ClientError(message, Status::HTTP_FORBIDDEN) {}

    virtual ~ForbiddenError() noexcept {}
};

class NotFoundError : public ClientError
{
public:
    explicit NotFoundError(const char* message)
        : ClientError(message, Status::HTTP_NOT_FOUND) {}

    explicit NotFoundError(const std::string& message)
        : ClientError(message, Status::HTTP_NOT_FOUND) {}

    virtual ~NotFoundError() noexcept {}
};

class UnauthorizedError : public ClientError
{
public:
    explicit UnauthorizedError(const char* message)
        : ClientError(message, Status::HTTP_UNAUTHORIZED) {}

    explicit UnauthorizedError(const std::string& message)
        : ClientError(message, Status::HTTP_UNAUTHORIZED) {}

    virtual ~UnauthorizedError() noexcept {}
};
