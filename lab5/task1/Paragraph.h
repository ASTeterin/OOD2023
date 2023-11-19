#pragma once
#include "IParagraph.h"


class CParagraph : public IParagraph
{
public:
	CParagraph(const std::string& text)
		: m_text(text)
	{
	}
	std::string GetText() const;
	void SetText(const std::string& text);

private:
	std::string m_text;
};
