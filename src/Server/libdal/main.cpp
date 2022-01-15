#include "idbfacade.h"
#include "dbfacade.h"

#include <memory>
#include <iostream>

int main()
{
    std::unique_ptr<IDbFacade> db = std::make_unique<DbFacade>("user=postgres host=localhost dbname=Test password=postgres");
    auto user = db->getUserById(2);
    std::cout
            << "User:\n"
            << "\tid: " << user.id << "\n"
            << "\tlogin: " << user.login << "\n"
            << "\tpass: " << user.pass << "\n";
}
