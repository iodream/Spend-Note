#include "gmock/gmock.h"

#include "../libdal/Facade/IDbFacade.h"

class MockDbFacade : public IDbFacade
{
public:
    using Ptr = std::unique_ptr<MockDbFacade>;

    MOCK_METHOD(void, AddUser, (const User&), (override));
    MOCK_METHOD(std::optional<User>, GetUserById, (IdType), (override));
    MOCK_METHOD(std::optional<User>, GetUserByLogin, (const std::string&), (override));
    MOCK_METHOD(void, UpdateUser, (const User&), (override));
	MOCK_METHOD(bool, RemoveUser, (IdType), (override));

	MOCK_METHOD(std::optional<IdType>, AddProduct, (const Product&), (override));
    MOCK_METHOD(std::optional<Product>, GetProductById, (IdType), (override));
    MOCK_METHOD(std::vector<Product>, GetProductsForList, (IdType), (override));
    MOCK_METHOD(void, UpdateProduct, (const Product&), (override));
	MOCK_METHOD(bool, RemoveProduct, (IdType), (override));

    MOCK_METHOD(std::optional<ProductCategory>, GetProductCategoryById, (IdType), (override));
    MOCK_METHOD(std::vector<ProductCategory>, GetAllProductCategories, (), (override));

	MOCK_METHOD(std::optional<IdType>, AddIncome, (const Income&), (override));
    MOCK_METHOD(std::optional<Income>, GetIncomeById, (const IdType& id), (override));
	MOCK_METHOD(std::vector<Income>, GetAllIncomes, (const IdType& id), (override));
    MOCK_METHOD(void, UpdateIncome, (const Income&), (override));
	MOCK_METHOD(bool, RemoveIncome, (const IdType&), (override));

	MOCK_METHOD(std::optional<IdType>, AddList, (const List& list_), (override));
    MOCK_METHOD(std::optional<List>, GetListById, (const IdType&), (override));
	MOCK_METHOD(std::vector<List>, GetAllLists, (const IdType&), (override));
    MOCK_METHOD(void, UpdateList, (const List&), (override));
	MOCK_METHOD(bool, RemoveList, (const IdType&), (override));

    MOCK_METHOD(std::optional<IncomeCategory>, GetIncomeCategoryById, (const IdType&), (override));
	MOCK_METHOD(std::vector<IncomeCategory>, GetAllIncomeCategories, (), (override));

    MOCK_METHOD(std::optional<ListState>, GetListStateById, (const IdType&), (override));
    MOCK_METHOD(std::vector<ListState>, GetAllListStates, (), (override));
};
