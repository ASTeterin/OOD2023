#include "CShapeFactory.h"
#include "CRectangle.h"
#include <exception>
#include <sstream>
#include "CTriangle.h"
#include "CEllipse.h"

const std::string RECTANGLE = "rectangle";
const std::string TRIANGLE = "triangle";
const std::string ELLIPSE = "ellipse";

const std::string GREEN = "green";
const std::string YELLOW = "yellow";
const std::string RED = "red";
const std::string BLUE = "blue";
const std::string PINK = "pink";
const std::string BLACK = "black";

std::unique_ptr<CShape> CShapeFactory::CreateShape(std::string const& description)
{
	std::istringstream descStream(description);
	std::string shapeName;
	std::string colorStr;
	descStream >> shapeName;
	descStream >> colorStr;
	auto color = GetColor(colorStr);

	if (shapeName == RECTANGLE)
		return CreateRectangle(descStream, color);
	if (shapeName == TRIANGLE)
		return CreateTriangle(descStream, color);
	if (shapeName == ELLIPSE)
		return CreateEllipse(descStream, color);
	throw std::invalid_argument("Invalid shape name");
}

Color CShapeFactory::GetColor(std::string const& color) const
{
	if (color == GREEN)
		return Color::GREEN;
	if (color == YELLOW)
		return Color::YELLOW;
	if (color == BLACK)
		return Color::BLACK;
	if (color == BLUE)
		return Color::BLUE;
	if (color == RED)
		return Color::RED;
	if (color == PINK)
		return Color::PINK;
	throw std::invalid_argument("Invalid color name");
}

std::unique_ptr<CShape> CShapeFactory::CreateRectangle(std::istream& strm, Color color) const
{
	double leftTopX = 0, leftTopY = 0, rightBottomX = 0, rightBottomY = 0;
	strm >> leftTopX >> leftTopY >> rightBottomX >> rightBottomY;
	Point leftTop = { leftTopX, leftTopY };
	Point rightBottom = { rightBottomX, rightBottomY };

	return std::make_unique<CRectangle>(color, leftTop, rightBottom);
}

std::unique_ptr<CShape> CShapeFactory::CreateTriangle(std::istream& strm, Color color) const
{
	double vertex1X = 0, vertex1Y = 0, vertex2X = 0, vertex2Y = 0, vertex3X = 0, vertex3Y = 0;
	strm >> vertex1X >> vertex1Y >> vertex2X >> vertex2Y >> vertex3X >> vertex3Y;
	Point firstVert = { vertex1X, vertex1Y };
	Point secondVert = { vertex2X, vertex2Y };
	Point thirdVert = { vertex3X, vertex3Y };

	return std::make_unique<CTriangle>(color, firstVert, secondVert, thirdVert);
}

std::unique_ptr<CShape> CShapeFactory::CreateEllipse(std::istream& strm, Color color) const
{
	double centerX = 0, centerY = 0, horizontalRadius = 0, verticalRadius = 0;
	strm >> centerX >> centerY >> horizontalRadius >> verticalRadius;
	Point center = { centerX, centerY };

	return std::make_unique<CEllipse>(color, center, horizontalRadius, verticalRadius);
}