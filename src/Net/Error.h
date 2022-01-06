#pragma once

#include "Poco/Net/HTTPServerResponse.h"

#include "../Exception.h"

namespace Net {

class NetError : public Exception {
public:
    using Status = Poco::Net::HTTPServerResponse::HTTPStatus;
    explicit NetError(const char* message, Status status)
        : Exception(message), m_status(status) {}

    explicit NetError(const std::string& message, Status status)
        : Exception(message), m_status(status) {}

    virtual ~NetError() noexcept {}

    Poco::Net::HTTPServerResponse::HTTPStatus get_status() const
    {
        return m_status;
    }
private:
     Status m_status;
};


class ClientError : public NetError {
public:
    using Status = Poco::Net::HTTPServerResponse::HTTPStatus;
    explicit ClientError(const char* message, Status status)
        : NetError(message, status) {}

    explicit ClientError(const std::string& message, Status status)
        : NetError(message, status) {}

    virtual ~ClientError() noexcept {}
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


class ServerError : public NetError {
public:
    using Status = Poco::Net::HTTPServerResponse::HTTPStatus;
    explicit ServerError(const char* message, Status status)
        : NetError(message, status) {}

    explicit ServerError(const std::string& message, Status status)
        : NetError(message, status) {}

    virtual ~ServerError() noexcept {}

    Poco::Net::HTTPServerResponse::HTTPStatus get_status() const
    {
        return m_status;
    }
private:
     Status m_status;
};

class InternalError : public ServerError
{
public:
    explicit InternalError(const char* message)
        : ServerError(message, Status::HTTP_INTERNAL_SERVER_ERROR) {}

    explicit InternalError(const std::string& message)
        : ServerError(message, Status::HTTP_INTERNAL_SERVER_ERROR) {}

    virtual ~InternalError() noexcept {}
};

class NotImplementedError : public ServerError
{
public:
    explicit NotImplementedError(const char* message)
        : ServerError(message, Status::HTTP_NOT_IMPLEMENTED) {}

    explicit NotImplementedError(const std::string& message)
        : ServerError(message, Status::HTTP_NOT_IMPLEMENTED) {}

    virtual ~NotImplementedError() noexcept {}
};

}
