#include "ChangeStringCommand.h"
#include "IParagraph.h"
#include <memory>

CChangeStringCommand::CChangeStringCommand(std::shared_ptr<IParagraph> paragraph, std::string newValue)
	: m_target(paragraph->GetText())
	, m_newValue(std::move(newValue))
{
}

void CChangeStringCommand::DoExecute()
{
	m_newValue.swap(m_target);
}

void CChangeStringCommand::DoUnexecute()
{
	m_newValue.swap(m_target);
}