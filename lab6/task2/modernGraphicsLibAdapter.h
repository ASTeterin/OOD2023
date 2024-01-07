#pragma once
#include <ostream>
#include "graphics_lib.h"
#include "modern_graphics_lib.h"

	class CModernGraphicsLibAdapter : private modern_graphics_lib::CModernGraphicsRenderer
	, public graphics_lib::ICanvas
{
public:
	CModernGraphicsLibAdapter(std::ostream& strm)
		: CModernGraphicsRenderer(strm)
		, m_startPoint(0, 0)
	{
		BeginDraw();
	}
	~CModernGraphicsLibAdapter()
	{
		EndDraw();
	}
	void MoveTo(int x, int y) override
	{
		m_startPoint = modern_graphics_lib::CPoint(x, y);
	}
	void LineTo(int x, int y) override
	{
		modern_graphics_lib::CPoint end(x, y);
		DrawLine(m_startPoint, end);
		m_startPoint = end;
	}

private:
	modern_graphics_lib::CPoint m_startPoint;
};