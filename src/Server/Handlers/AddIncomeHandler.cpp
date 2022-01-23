#include "AddIncomeHandler.h"

#include "Common.h"
#include "Net/Parsing.h"

#include "Server/Error.h"
#include "Server/Utils.h"

#include "../libdal/Exceptions/SQLFailure.h"

AddIncomeHandler::AddIncomeHandler(IDbFacade::Ptr facade)
  : AuthorizedHandler(std::move(facade))
{
}

Income AddIncomeHandler::JSONParser::Parse(
  const QJsonDocument& json_doc)
{
  Income dto;

  auto json = json_doc.object();

  try {
	SafeReadId(json, "user_id", dto.user_id);
	SafeReadString(json, "name", dto.name);
	SafeReadNumber(json, "amount", dto.amount);
	SafeReadId(json, "category_id", dto.category_id);
	SafeReadString(json, "add_time", dto.add_time);
	SafeReadString(json, "expiration_time", *dto.expiration_time);
  }  catch (const ParsingError& ex) {
	throw BadRequestError{std::string{"Parsing Error: "}.append(ex.what())};
  }

  return dto;
}

Net::Response AddIncomeHandler::AuthHandle(const Net::Request& request)
{
  if(request.method == Net::HTTP_METHOD_POST)
  {
	auto dto = m_parser.Parse(request.json_payload);
	dto.user_id = request.uid;

	AddIncomeHandler::JSONFormatter::DTO out_dto;

	try {
	  out_dto.income_id = m_facade->AddIncome(dto).value();
	}  catch (const SQLFailure& e) {
	  throw FormErrorResponse(
		NetError::Status::HTTP_CONFLICT,
		"Unable to create resource");
	}

	return FormJSONResponse(m_formatter.Format(out_dto));
  }
  return FormErrorResponse(
	NetError::Status::HTTP_BAD_REQUEST,
	"Unsupported method");
}

QJsonDocument AddIncomeHandler::JSONFormatter::Format(const DTO& dto)
{
  QJsonObject json;
  json["id"] = std::to_string(dto.income_id).c_str();
  return QJsonDocument{json};
}
