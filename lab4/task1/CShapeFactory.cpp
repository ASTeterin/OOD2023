#include "CShapeFactory.h"
#include "CRectangle.h"
#include <exception>
#include <sstream>

const std::string RECTANGLE_NAME = "rectangle";
const std::string TRIANGLE_NAME = "triangle";
const std::string ELLIPSE_NAME = "ellipse";
const std::string POLYGON_NAME = "polygon";



const std::string GREEN_NAME = "green";
const std::string YELLOW_NAME = "yellow";
const std::string RED_NAME = "red";
const std::string BLUE_NAME = "blue";
const std::string PINK_NAME = "pink";
const std::string BLACK_NAME = "black";

std::unique_ptr<CShape> CShapeFactory::CreateShape(std::string const& description)
{
	std::istringstream descStream(description);
	std::string shapeName;
	std::string colorStr;
	descStream >> shapeName;
	descStream >> colorStr;
	auto color = GetColorByName(colorStr);

	if (shapeName == RECTANGLE_NAME)
		return CreateRectangle(descStream, color);
	throw std::invalid_argument("Invalid shape name");
}

Color CShapeFactory::GetColorByName(std::string const& color) const
{
	if (color == GREEN_NAME)
		return Color::GREEN;
	if (color == YELLOW_NAME)
		return Color::YELLOW;
	if (color == BLACK_NAME)
		return Color::BLACK;
	if (color == BLUE_NAME)
		return Color::BLUE;
	if (color == RED_NAME)
		return Color::RED;
	if (color == PINK_NAME)
		return Color::PINK;
	throw std::invalid_argument("Invalid color name");
}

std::unique_ptr<CShape> CShapeFactory::CreateRectangle(std::istream& strm, Color color) const
{
	double leftTopX = -1, leftTopY = -1, rightBottomX = -1, rightBottomY = -1;
	strm >> leftTopX >> leftTopY >> rightBottomX >> rightBottomY;
	Point leftTop = { leftTopX, leftTopY };
	Point rightBottom = { rightBottomX, rightBottomY };

	return std::make_unique<CRectangle>(color, leftTop, rightBottom);
}
