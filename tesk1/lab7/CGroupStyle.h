#pragma once
#include "CommonTypes.h"
#include "IFillStyle.h"
#include <optional>
#include <vector>

class CGroupFillStyle : public IFillStyle
{
public:
	CGroupFillStyle(std::vector<std::shared_ptr<IShape>>& shapes)
		: m_shapes(shapes)
	{
	}

	std::optional<RGBAColor> GetColor() const override
	{
		std::optional<RGBAColor> firstElemColor = m_shapes.back()->GetFillStyle()->GetColor();
		for (auto& shape : m_shapes)
		{
			if (firstElemColor != shape->GetFillStyle()->GetColor())
				return std::nullopt;
		}
		return firstElemColor;
	}

	void SetColor(RGBAColor color) override
	{
		for (auto& shape : m_shapes)
			shape->GetFillStyle()->SetColor(color);
	}

private:
	std::vector<std::shared_ptr<IShape>>& m_shapes;
};