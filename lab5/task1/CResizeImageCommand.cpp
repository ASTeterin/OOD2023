#include "CResizeImageCommand.h"

using namespace std;

CResizeImageCommand::CResizeImageCommand(int& width, int& height,
	int newWidth, int newHeight)
	: m_width(width)
	, m_height(height)
	, m_newWidth(newWidth)
	, m_newHeight(newHeight)
{
}

void CResizeImageCommand::DoExecute()
{
	swap(m_width, m_newWidth);
	swap(m_height, m_newHeight);
}

void CResizeImageCommand::DoUnexecute()
{
	swap(m_width, m_newWidth);
	swap(m_height, m_newHeight);
}