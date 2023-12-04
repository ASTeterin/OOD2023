#pragma once
#include "AbstractCommand.h"
#include "IImage.h"

class CResizeImageCommand : public CAbstractCommand
{
public:
	CResizeImageCommand(int& width, int& height, int newWidth, int newHeight);

protected:
	void DoExecute() override;
	void DoUnexecute() override;

private:
	int& m_width;
	int& m_height;
	int m_newWidth;
	int m_newHeight;
};