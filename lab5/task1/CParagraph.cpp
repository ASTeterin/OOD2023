#include "ChangeStringCommand.h"
#include "CParagraph.h"

using namespace std;

CParagraph::CParagraph(const string& text, CHistory& history)
	: m_text(text)
	, m_history(history)
{
}

string CParagraph::GetText() const
{
	return m_text;
}

void CParagraph::SetText(const string& text)
{
	m_history.AddAndExecuteCommand(make_unique<CChangeStringCommand>(m_text, text));
}