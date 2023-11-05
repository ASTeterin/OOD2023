#pragma once
#include "Common.h"
#include "ICanvas.h"

class CShape
{
public:
	CShape(Color color)
		: m_color(color)
	{
	}
	Color GetColor() const
	{
		return m_color;
	};

	virtual void Draw(ICanvas& canvas) const = 0;

protected:
	Color m_color;
};
	