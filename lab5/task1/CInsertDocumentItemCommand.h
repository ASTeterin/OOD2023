#pragma once
#include "CDocumentItem.h"
#include "AbstractCommand.h"
#include <vector>

class CInsertDocumentItemCommand : public CAbstractCommand
{
public:
	CInsertDocumentItemCommand(std::vector<CDocumentItem>& items, CDocumentItem item, optional<size_t> position);

protected:
	void DoExecute() override;
	void DoUnexecute() override;

private:
	std::vector<CDocumentItem>& m_items;
	CDocumentItem m_item;
	optional<size_t> m_position;
};