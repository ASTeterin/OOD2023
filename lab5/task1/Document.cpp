#include "stdafx.h"
#include "Document.h"
#include "ChangeStringCommand.h"

using namespace std;


shared_ptr<IParagraph> CDocument::InsertParagraph(const string& text, optional<unsigned> position)
{
	shared_ptr<IParagraph> paragraph = make_shared<CParagraph>(text);
	CDocumentItem itemHolder(nullptr, paragraph);
	if (position == nullopt)
		m_items.push_back(itemHolder);
	else
	{
		AssertPositionValid(*position);
		auto it = m_items.begin() + *position;
		m_items.insert(it, itemHolder);
	}
	return paragraph;
}

void CDocument::SetTitle(const std::string& title)
{
	m_history.AddAndExecuteCommand(make_unique<CChangeStringCommand>(m_title, title));
}

std::string CDocument::GetTitle() const
{
	return m_title;
}

bool CDocument::CanUndo() const
{
	return m_history.CanUndo();
}

void CDocument::Undo()
{
	m_history.Undo();
}

bool CDocument::CanRedo() const
{
	return m_history.CanRedo();
}

void CDocument::Redo()
{
	m_history.Redo();
}