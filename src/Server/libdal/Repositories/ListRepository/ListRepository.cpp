#include "ListRepository.h"

namespace
{
    const std::string& TABLE_NAME = "List";
    const std::string& ID_FIELD = "id";
    const std::string& USER_ID = "userId";
    const std::string& LIST_NAME = "name";
    const std::string& LIST_STATE_ID = "stateId";
    const std::string& TABLE_WITH_CATEGORY = "ListState";
}


ListRepository::ListRepository(pqxx::connection& database_connection) : m_database_connection(database_connection)
{
}


void ListRepository::AddList(const List& list_)
{
    pqxx::work w{m_database_connection};
    try
    {
        w.exec0("INSERT INTO " + TABLE_NAME + " ( " +  USER_ID + ", " + LIST_STATE_ID + ", " + LIST_NAME + ") "
                + "VALUES (" + w.quote(list_.ownerId) + ", " + w.quote(list_.stateId) + ", " + w.quote(list_.name) + ");");

        w.commit();
    }
    catch(const pqxx::pqxx_exception& e)
    {
        throw DatabaseFailure();
    }
}


void ListRepository::Remuve(const idType& id)
{
    pqxx::work w{m_database_connection};

    try
    {
       w.exec0("DELETE FROM " + TABLE_NAME + " WHERE " + ID_FIELD + " = " + w.quote(id) + ";");
        w.commit();
    }
    catch(const pqxx::pqxx_exception& e)
    {
        throw DatabaseFailure();
    }
}


std::optional<List> ListRepository::GetList(const idType& id)
{
    pqxx::work w{m_database_connection};

    try
    {
       pqxx::row list_ =  w.exec1("SELECT * FROM " + TABLE_NAME + " WHERE " + ID_FIELD + " = " + w.quote(id));

       if(!list_.empty()){
             return List{list_[ID_FIELD].as<idType>(), list_[USER_ID].as<idType>(),
                         list_[LIST_STATE_ID].as<idType>(), list_[LIST_NAME].as<std::string>()};
       }
    }
    catch(const pqxx::pqxx_exception& e)
    {
        throw DatabaseFailure();
    }
    return std::nullopt;
}


void ListRepository::Update(const List& list_)
{
    pqxx::work w{m_database_connection};

    try
    {
       w.exec0("UPDATE " + TABLE_NAME + " SET " + LIST_STATE_ID + " = " + w.quote(list_.stateId) + ", "
                + LIST_NAME + " = " + w.quote(list_.name) + " WHERE " + ID_FIELD + " = " + w.quote(list_.id) + ";");

       w.commit();
    }
    catch(const pqxx::pqxx_exception& e)
    {
        throw DatabaseFailure();
    }
}









