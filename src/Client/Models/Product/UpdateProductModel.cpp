#include "UpdateProductModel.h"


Net::Request UpdateProductModel::FormRequest(const Product& product)
{
	Net::Request request;
	request.uri = m_hostname + "products/" + std::to_string(product.id);
	request.method = Net::HTTP_METHOD_PUT;
	request.content_type = Net::CONTENT_TYPE_APPLICATION_JSON;
	request.json_payload = QJsonDocument(m_formatter.Format(product));
	return request;
}
