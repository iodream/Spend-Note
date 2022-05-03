#include "gmock/gmock.h"

#include "../libdal/Facade/IDbFacade.h"

class MockDbFacade : public db::IDbFacade
{
public:
	using Ptr = std::unique_ptr<MockDbFacade>;

	MOCK_METHOD(std::optional<db::IdType>, AddUser, (const db::User&), (override));
	MOCK_METHOD(std::optional<db::User>, GetUserById, (db::IdType), (override));
	MOCK_METHOD(std::optional<db::User>, GetUserByEmail, (const std::string&), (override));
	MOCK_METHOD(bool, UpdateUser, (const db::User&), (override));
	MOCK_METHOD(bool, UpdateUserPassword, (const db::IdType, const std::string&, const std::string&), (override));
	MOCK_METHOD(bool, UpdateUserVerification, (db::IdType), (override));
	MOCK_METHOD(bool, RemoveUser, (db::IdType), (override));

	MOCK_METHOD(std::optional<db::IdType>, AddProduct, (const db::Product&), (override));
	MOCK_METHOD(std::optional<db::Product>, GetProductById, (db::IdType), (override));
	MOCK_METHOD(std::vector<db::Product>, GetProductsForList, (db::IdType), (override));
	MOCK_METHOD(bool, UpdateProduct, (const db::Product&), (override));
	MOCK_METHOD(bool, RemoveProduct, (db::IdType), (override));

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

	MOCK_METHOD(std::optional<db::ListState>, GetListStateById, (const db::IdType&), (override));
	MOCK_METHOD(std::vector<db::ListState>, GetAllListStates, (), (override));

	MOCK_METHOD(db::Money, CalculateBalanceForUser, (db::IdType), (override));
	MOCK_METHOD(db::Money, CalculatePlannedBalanceForUser, (db::IdType), (override));

	MOCK_METHOD(bool, CanUserEditList, (db::IdType, db::IdType), (override));
	MOCK_METHOD(bool, CanUserEditProduct, (db::IdType, db::IdType), (override));
	MOCK_METHOD(bool, CanUserEditIncome, (db::IdType, db::IdType), (override));
	MOCK_METHOD(bool, CanUserEditIncomeCategory, (db::IdType, db::IdType), (override));

	MOCK_METHOD(std::vector<db::Product>, GetDailyList, (db::IdType), (override));

	MOCK_METHOD(std::vector<db::ExpensePerCategory>, ExpensesPerCategory, (db::IdType, db::Period), (override));
	MOCK_METHOD(std::vector<db::ExpensePercentagePerCategory>, ExpensesPercentagePerCategory, (db::IdType, db::Period), (override));
	MOCK_METHOD(std::vector<db::ExpensePerDay>, ExpensesDynamics, (db::IdType, db::Period), (override));

	MOCK_METHOD(std::vector<db::IncomePerCategory>, IncomesPerCategory, (db::IdType, db::Period), (override));
	MOCK_METHOD(std::vector<db::IncomePercentagePerCategory>, IncomesPercentagePerCategory, (db::IdType, db::Period), (override));
	MOCK_METHOD(std::vector<db::IncomePerDay>, IncomesDynamics, (db::IdType, db::Period), (override));

	MOCK_METHOD(std::optional<db::IncomeCategory>, GetIncomeCategoryById, (db::IdType),(override));
	MOCK_METHOD(std::vector<db::IncomeCategory>, GetAllIncomeCategories, (db::IdType), (override));
	MOCK_METHOD(std::optional<db::IdType>, AddIncomeCategory, (const db::IncomeCategory& category), (override));
	MOCK_METHOD(bool, UpdateIncomeCategory, (const db::IncomeCategory& category), (override));
	MOCK_METHOD(bool, RemoveIncomeCategory, (db::IdType), (override));

	MOCK_METHOD(std::optional<db::ProductCategory>, GetProductCategoryById, (db::IdType),(override));
	MOCK_METHOD(std::vector<db::ProductCategory>, GetAllProductCategories, (db::IdType), (override));
	MOCK_METHOD(std::optional<db::IdType>, AddProductCategory, (const db::ProductCategory& category), (override));
	MOCK_METHOD(bool, UpdateProductCategory, (const db::ProductCategory& category), (override));
	MOCK_METHOD(bool, RemoveProductCategory, (db::IdType), (override));
	MOCK_METHOD(bool, CanUserEditProductCategory, (db::IdType, db::IdType), (override));

	MOCK_METHOD(std::optional<db::IdType>, AddVerificationCode, (const db::VerificationCode&), (override));
	MOCK_METHOD(std::optional<db::VerificationCode>, GetVerificationCodeById, (db::IdType), (override));
	MOCK_METHOD(std::optional<db::VerificationCode>, GetVerificationCodeByUserId, (db::IdType), (override));
	MOCK_METHOD(bool, UpdateVerificationCode, (const db::VerificationCode&), (override));
	MOCK_METHOD(bool, RemoveVerificationCode, (db::IdType), (override));
};
