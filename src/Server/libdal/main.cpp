#include <QCoreApplication>
#include <iostream>

#include "Fasade/dbfacade.h"

int main(int argc, char *argv[])
{
    std::string ex="user=postgres host=localhost dbname=postgres password=123445";

    Income in{16, 1, "i", 10012, 6, "2021-01-01 14:00:00", "2021-01-01 14:00:00"};
    List ls{6, 1, 2, "u"};

    DbFacade fas{ex};

    fas.RemuveList(6);

}
