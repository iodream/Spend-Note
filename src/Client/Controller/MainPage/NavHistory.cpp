#include "NavHistory.h"


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
	return m_storage.top();
}

void NavHistory::ForgetLastPage()
{
	m_storage.pop();
}
