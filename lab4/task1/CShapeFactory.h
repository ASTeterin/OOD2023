#pragma once
#include "CShape.h"
#include "IShapeFactory.h"
#include <memory>
#include <string>

class CShapeFactory : public IShapeFactory
{
public:
	std::unique_ptr<CShape> CreateShape(std::string const& description);

private:
	std::unique_ptr<CShape> CreateRectangle(std::istream& strm, Color color) const;
	std::unique_ptr<CShape> CreateTriangle(std::istream& strm, Color color) const;
	std::unique_ptr<CShape> CreateEllipse(std::istream& strm, Color color) const;
	Color GetColor(std::string const& color) const;
};