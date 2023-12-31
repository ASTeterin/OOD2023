#pragma once
#include "ICanvas.h"
#include "IFillStyle.h"
#include <memory>
#include <optional>

class IGroupShape;

class IShape
{
public:
	virtual RectD GetFrame() const = 0;
	virtual void SetFrame(const RectD& rect) = 0;

	virtual std::shared_ptr<IOutlineStyle> GetOutlineStyle() = 0;
	virtual std::shared_ptr<const IOutlineStyle> GetOutlineStyle() const = 0;

	virtual std::shared_ptr<IFillStyle> GetFillStyle() = 0;
	virtual std::shared_ptr<const IFillStyle> GetFillStyle() const = 0;

	virtual std::shared_ptr<IGroupShape> GetGroup() = 0;
	virtual std::shared_ptr<const IGroupShape> GetGroup() const = 0;

	virtual std::weak_ptr<IGroupShape> GetParent() const = 0;
	virtual void SetParent(std::weak_ptr<IGroupShape> parent) = 0;

	virtual void Draw(ICanvas& canvas) const = 0;

	virtual ~IShape() = default;
};