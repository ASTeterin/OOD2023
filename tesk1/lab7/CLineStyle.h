#pragma once
#include "CommonTypes.h"
#include "IFillStyle.h"
#include <optional>

class CLineStyle : public IOutlineStyle
{
public:
	std::optional<RGBAColor> GetColor() const override
	{
		return m_color;
	}

	void SetColor(RGBAColor color) override
	{
		m_color = color;
	}

	std::optional<double> GetLineWidth() const override
	{
		return m_lineWidth;
	}

	void SetLineWidth(double size) override
	{
		m_lineWidth = size;
	}

private:
	RGBAColor m_color = 0;
	double m_lineWidth = 0;
};