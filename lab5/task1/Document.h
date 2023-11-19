#pragma once
#include "IDocument.h"
#include "History.h"

class CDocument:public IDocument
{
public:
	shared_ptr<IParagraph> InsertParagraph(const string& text, optional<unsigned> position);

	void SetTitle(const std::string & title) override;
	std::string GetTitle() const override;

	bool CanUndo() const override;	
	void Undo() override;
	bool CanRedo() const override;
	void Redo() override;

private:
	std::string m_title;
	CHistory m_history;


};