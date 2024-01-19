#pragma once
#include "IFillStyle.h"
#include <functional>
#include "IShape.h"

class CGroupLineStyle : public IOutlineStyle
{
public:
	CGroupLineStyle(std::vector<std::shared_ptr<IShape>>& shapes)
		: m_shapes(shapes)
	{
	}

	std::optional<RGBAColor> GetColor() const override
	{
		auto firstElemColor = m_shapes[0]->GetOutlineStyle()->GetColor();
		for (auto& shape : m_shapes)
		{
			if (firstElemColor != shape->GetOutlineStyle()->GetColor())
				return std::nullopt;
		}
		return firstElemColor;
	}

	void SetColor(RGBAColor color) override
	{
		for (auto& shape : m_shapes)
			shape->GetOutlineStyle()->SetColor(color);
	}

	std::optional<double> GetLineWidth() const override
	{
		auto firstElemWidth = m_shapes[0]->GetOutlineStyle()->GetLineWidth();
		for (auto& shape : m_shapes)
		{
			if (firstElemWidth != shape->GetOutlineStyle()->GetLineWidth())
				return std::nullopt;
		}
		return firstElemWidth;
	}

	void SetLineWidth(double size) override
	{
		for (auto& shape : m_shapes)
			shape->GetOutlineStyle()->SetLineWidth(size);
	}

private:
	std::vector<std::shared_ptr<IShape>>& m_shapes;
};
