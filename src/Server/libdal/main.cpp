#include "Facade/DbFacade.h"
#include "Facade/IDbFacade.h"
#include <memory>
#include <iostream>

int main()
{

	DbFacade f("user=postgres host=localhost dbname=postgres password=123445");
	auto t =f.GetAllIncomeCategories();
	for(const auto& y : t){
		std::cout << y.name<<std::endl;
	}
}
