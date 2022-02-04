#pragma once

#include <stack>
#include "View/Constants.h"


class NavHistory {
public:
	void Update(MainSubPages page);
	MainSubPages GetLastPage();
	void ForgetLastPage();
	void Clear();
private:
	std::stack<MainSubPages> m_storage;
};
