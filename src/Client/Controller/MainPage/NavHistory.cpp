#include "NavHistory.h"
#include <exception>

void NavHistory::Update(MainSubPages page)
{
	if (m_storage.empty())
		m_storage.push(page);
	else if (m_storage.top() != page)
		m_storage.push(page);
}

void NavHistory::Clear()
{
	m_storage = std::stack<MainSubPages>{};
}

MainSubPages NavHistory::GetLastPage()
{
	if(m_storage.empty())
		throw std::out_of_range("goback top lvl reached"); // don't go further up than top level
	return m_storage.top();
}

void NavHistory::ForgetLastPage()
{
	m_storage.pop();
}
