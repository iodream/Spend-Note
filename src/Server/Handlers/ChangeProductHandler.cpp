#include <QJsonObject>
#include <memory>
#include <optional>

#include "QJsonObject"
#include "QJsonArray"


#include "ChangeProductHandler.h"
#include "Common.h"
#include "Net/Parsing.h"
#include "../libdal/Facade/DbFacade.h"
#include "../libdal/DTOs/Product.h"
#include "Server/Error.h"
#include "Server/Utils.h"

ChangeProductHandler::ChangeProductHandler()
	: m_facade(std::make_unique<DbFacade>(DB_CONN_STRING))
{
}


Product ChangeProductHandler::Parser(const QJsonObject &obj)
{
	Product product;

	product.id = obj["id"].toInt();
	product.list_id = obj["list_id"].toInt();
	product.category_id	= obj["category_id"].toInt();
	product.name = (obj["name"].toString()).toStdString();
	product.price = obj["price"].toDouble();
	product.amount = obj["amount"].toInt();
	product.is_bought = obj["is_bought"].toBool();
	product.add_date = (obj["add_date"].toString()).toStdString();
	product.purchase_date = (obj["purchase_date"].toString()).toStdString();
	product.buy_until_date = (obj["buy_until_date"].toString()).toStdString();

	return product;
}

Net::Response ChangeProductHandler::AuthHandle(const Net::Request &request)
{
	if(request.method == Net::HTTP_METHOD_POST)
	{
		auto dto = request.json_payload;
		m_facade->UpdateProduct(Parser(dto.object()));
	}
	return FormErrorResponse(
		NetError::Status::HTTP_BAD_REQUEST,
		"Unsupported method"
		);
}
