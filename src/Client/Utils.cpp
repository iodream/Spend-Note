 #include "Utils.h"

std::string EraseWhitespace(std::string str)
{
	str.erase(std::remove_if(str.begin(), str.end(), ::isspace),
		str.end());
	return str;
}

QString toDBstring(const QDateTime &time)
{
	QString db_str;

	time.date().day() <= 9
			? db_str += "0" + QString::number(time.date().day())
			: db_str += QString::number(time.date().day());

	db_str += "-";

	time.date().month() <= 9
			? db_str += "0" + QString::number(time.date().month())
			: db_str += QString::number(time.date().month());

	db_str += "-";

	db_str += QString::number(time.date().year());
	db_str += " ";
	db_str += (time.time().toString());

	return db_str;
}
