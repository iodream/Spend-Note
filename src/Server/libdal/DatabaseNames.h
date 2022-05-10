#pragma once
#include <string>

namespace db
{
	namespace income
	{
		const std::string TABLE_NAME = "Income";
		const std::string ID = "id";
		const std::string NAME = "name";
		const std::string USER_ID = "userId";
		const std::string AMOUNT = "amount";
		const std::string CATEGORY_ID = "categoryId";
		const std::string ADD_TIME = "addTime";
		const std::string EXPIRATION_TIME= "expirationTime";
		const std::string PERIODIC_ID = "periodicId";
	}

	namespace incomeCategory
	{
		const std::string TABLE_NAME = "IncomeCategory";
		const std::string ID = "id";
		const std::string USER_ID = "userId";
		const std::string NAME = "name";
	}

	namespace periodType
	{
		const std::string TABLE_NAME = "PeriodType";
		const std::string ID = "id";
		const std::string NAME = "name";
	}

	namespace periodicIncome
	{
		const std::string TABLE_NAME = "PeriodicIncome";
		const std::string ID = "id";
		const std::string NAME = "name";
		const std::string USER_ID = "userId";
		const std::string AMOUNT = "amount";
		const std::string CATEGORY_ID = "categoryId";


		const std::string PERIOD_ID = "periodId";
		const std::string NEXT_ADD_DATE = "nextAddDate";
		const std::string ADD_UNTIL = "addUntil";
	}

	namespace list
	{
		const std::string TABLE_NAME = "List";
		const std::string ID = "id";
		const std::string USER_ID = "userId";
		const std::string NAME = "name";
		const std::string STATE_ID = "stateId";
	}

	namespace listState
	{
		const std::string TABLE_NAME = "ListState";
		const std::string ID = "id";
		const std::string NAME = "name";
	}

	namespace product
	{
		const std::string TABLE_NAME = "Product";
		const std::string ID = "id";
		const std::string LIST_ID = "listId";
		const std::string CATEGORY_ID = "categoryId";
		const std::string NAME = "name";
		const std::string PRICE = "price";
		const std::string AMOUNT = "amount";
		const std::string PRIORITY = "productPriority";
		const std::string IS_BOUGHT = "isBought";
		const std::string ADD_DATE = "addDate";
		const std::string PURCHASE_DATE = "purchaseDate";
		const std::string BUY_UNTIL_DATE = "buyUntilDate";
		const std::string PERIODIC_ID = "periodicId";
	}

	namespace periodicProduct
	{
		const std::string TABLE_NAME = "PeriodicProduct";
		const std::string ID = "id";
		const std::string LIST_ID = "listId";
		const std::string CATEGORY_ID = "categoryId";
		const std::string NAME = "name";
		const std::string PRICE = "price";
		const std::string AMOUNT = "amount";
		const std::string PRIORITY = "productPriority";
		const std::string PERIOD_ID = "periodId";
		const std::string NEXT_ADD_DATE = "nextAddDate";
		const std::string ADD_UNTIL = "addUntil";
	}

	namespace productCategory
	{
		const std::string TABLE_NAME = "ProductCategory";
		const std::string ID = "id";
		const std::string USER_ID = "userId";
		const std::string NAME = "name";
	}

	namespace user
	{
		const std::string TABLE_NAME = "User_";
		const std::string ID = "id";
		const std::string LOGIN = "login";
		const std::string PASSWORD = "password_hash";
		const std::string SALT = "salt";
	}

	namespace statistics
	{
		const std::string TOTAL_PRICE = "totalPrice";
		const std::string PURCHASE_DATE = "purchase_date";
	}
}
