#include "CInsertDocumentItemCommand.h"

CInsertDocumentItemCommand::CInsertDocumentItemCommand(std::vector<CDocumentItem>& items, CDocumentItem item, optional<size_t> position)
	: m_items(items)
	, m_item(item)
	, m_position(position)
{
	if (position && position > m_items.size())
		throw out_of_range("Position is out of range");
}

void CInsertDocumentItemCommand::DoExecute()
{
	auto index = (m_position) ? (m_items.begin() + m_position.value()) : (m_items.end());
	m_items.emplace(index, m_item);
}

void CInsertDocumentItemCommand::DoUnexecute()
{
	auto index = (m_position) ? (m_items.begin() + m_position.value()) : (--m_items.end());
	m_items.erase(index);
}