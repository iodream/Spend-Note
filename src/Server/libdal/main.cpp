#include "Facade/dbfacade.h"
#include "Facade/idbfacade.h"
#include <memory>
#include <iostream>

int main()
{
	DbFacade facade{"user=postgres host=localhost dbname=postgres password=123445"};

	auto r = facade.GetAllIncomes(20);
	for(auto& el : *r)
	{
		std::cout << el.amount << std::endl;
	}

	auto t = facade.GetListCategoriesAll();
	for(auto& el : t)
	{
		std::cout << el.name << std::endl;
	}

}
