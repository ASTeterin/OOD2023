#pragma once
#include "CDocumentItem.h"
#include "AbstractCommand.h"
#include <vector>

class CDeleteItemCommand : public CAbstractCommand
{
public:
	CDeleteItemCommand(std::vector<CDocumentItem>& items,std::size_t index);

protected:
	void DoExecute() override;
	void DoUnexecute() override;

private:
	std::vector<CDocumentItem>& m_items;
	std::shared_ptr<CDocumentItem> m_item;
	std::size_t m_index;
};
