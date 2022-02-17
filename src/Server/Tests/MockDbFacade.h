#include "gmock/gmock.h"

#include "../libdal/Facade/IDbFacade.h"

class MockDbFacade : public db::IDbFacade
{
public:
	using Ptr = std::unique_ptr<MockDbFacade>;

	MOCK_METHOD(std::optional<db::IdType>, AddUser, (const db::User&), (override));
	MOCK_METHOD(std::optional<db::User>, GetUserById, (db::IdType), (override));
	MOCK_METHOD(std::optional<db::User>, GetUserByLogin, (const std::string&), (override));
	MOCK_METHOD(bool, UpdateUser, (const db::User&), (override));
	MOCK_METHOD(bool, RemoveUser, (db::IdType), (override));

	MOCK_METHOD(std::optional<db::IdType>, AddProduct, (const db::Product&), (override));
	MOCK_METHOD(std::optional<db::Product>, GetProductById, (db::IdType), (override));
	MOCK_METHOD(std::vector<db::Product>, GetProductsForList, (db::IdType), (override));
	MOCK_METHOD(bool, UpdateProduct, (const db::Product&), (override));
	MOCK_METHOD(bool, RemoveProduct, (db::IdType), (override));

	MOCK_METHOD(std::optional<db::ProductCategory>, GetProductCategoryById, (db::IdType), (override));
	MOCK_METHOD(std::vector<db::ProductCategory>, GetAllProductCategories, (), (override));

	MOCK_METHOD(std::optional<db::IdType>, AddIncome, (const db::Income&), (override));
	MOCK_METHOD(std::optional<db::Income>, GetIncomeById, (const db::IdType& id), (override));
	MOCK_METHOD(std::vector<db::Income>, GetAllIncomes, (const db::IdType& id), (override));
	MOCK_METHOD(bool, UpdateIncome, (const db::Income&), (override));
	MOCK_METHOD(bool, RemoveIncome, (const db::IdType&), (override));

	MOCK_METHOD(std::optional<db::IdType>, AddList, (const db::List& list_), (override));
	MOCK_METHOD(std::optional<db::List>, GetListById, (const db::IdType&), (override));
	MOCK_METHOD(std::vector<db::List>, GetAllLists, (const db::IdType&), (override));
	MOCK_METHOD(bool, UpdateList, (const db::List&), (override));
	MOCK_METHOD(bool, RemoveList, (const db::IdType&), (override));

	MOCK_METHOD(std::optional<db::IncomeCategory>, GetIncomeCategoryById, (const db::IdType&), (override));
	MOCK_METHOD(std::vector<db::IncomeCategory>, GetAllIncomeCategories, (), (override));

	MOCK_METHOD(std::optional<db::ListState>, GetListStateById, (const db::IdType&), (override));
	MOCK_METHOD(std::vector<db::ListState>, GetAllListStates, (), (override));

	MOCK_METHOD(db::Money, CalculateBalanceForUser, (db::IdType), (override));
	MOCK_METHOD(db::Money, CalculatePlannedBalanceForUser, (db::IdType), (override));

	MOCK_METHOD(bool, CanUserEditList, (db::IdType, db::IdType), (override));
	MOCK_METHOD(bool, CanUserEditProduct, (db::IdType, db::IdType), (override));
	MOCK_METHOD(bool, CanUserEditIncome, (db::IdType, db::IdType), (override));

	MOCK_METHOD(std::vector<db::Product>, GetDailyList, (db::IdType), (override));
};
