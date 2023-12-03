#pragma once
#include "AbstractCommand.h"
#include "IDocument.h"

class CDeleteItemCommand : public CAbstractCommand
{
public:
	CDeleteItemCommand(std::vector<CDocumentItem>& items, size_t index);
	~CDeleteItemCommand();

protected:
	void DoExecute() override;
	void DoUnexecute() override;

private:
	IDocument& m_document;
	size_t m_position;
	CDocumentItem m_item;
};
