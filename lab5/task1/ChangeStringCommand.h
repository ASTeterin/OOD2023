#pragma once
#include "AbstractCommand.h"
#include <string>

class CChangeStringCommand : public CAbstractCommand
{
public:
	CChangeStringCommand(shared_ptr<IParagraph> paragraph, std::string newValue);

protected:
	void DoExecute() override;
	void DoUnexecute() override;

private:
	std::string m_newValue;
	std::string& m_target;
};