#pragma once
#include "graphics_lib.h"
#include "modern_graphics_lib.h"

class CModernGraphicsLibAdapter : public graphics_lib::ICanvas
{
public:
	CModernGraphicsLibAdapter(modern_graphics_lib::CModernGraphicsRenderer& modernGraphicsRenderer)
		: m_modernGraphicsRenderer(modernGraphicsRenderer)
		, m_startPoint({ 0, 0 })
	{
	}

	void MoveTo(int x, int y) override
	{
		m_startPoint = { x, y };
	}

	void LineTo(int x, int y) override
	{
		modern_graphics_lib::CPoint newPoint = { x, y };
		m_modernGraphicsRenderer.DrawLine(m_startPoint, newPoint);
		m_startPoint = newPoint;
	}

private:
	modern_graphics_lib::CModernGraphicsRenderer& m_modernGraphicsRenderer;
	modern_graphics_lib::CPoint m_startPoint;
};