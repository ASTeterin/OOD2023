#pragma once
#include "stdafx.h"
#include "AbstractCommand.h"
#include "IDocument.h"

class InsertParagraphCommand : public CAbstractCommand
{
public:
	InsertParagraphCommand(IDocument& document, const string& text, optional<unsigned> position = nullopt)
		: m_document(document)
		, m_text(text)
		, m_position(position)
	{
	}

protected:
	void DoExecute() override
	{
		m_document.InsertParagraph(m_text, m_position);
	}
	void DoUnexecute() override
	{
		auto position = m_position == nullopt ? m_document.GetItemsCount() - 1 : *m_position;
		m_document.DeleteItem(position);
	}

private:
	IDocument& m_document;
	string m_text;
	optional<unsigned> m_position = nullopt;
};