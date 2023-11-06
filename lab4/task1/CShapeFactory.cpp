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
	auto color = GetColorByName(colorStr);

	if (shapeName == RECTANGLE)
		return CreateRectangle(descStream, color);
	if (shapeName == TRIANGLE)
		return CreateTriangle(descStream, color);
	if (shapeName == ELLIPSE)
		return CreateEllipse(descStream, color);
	throw std::invalid_argument("Invalid shape name");
}

Color CShapeFactory::GetColorByName(std::string const& color) const
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
	double leftTopX = -1, leftTopY = -1, rightBottomX = -1, rightBottomY = -1;
	strm >> leftTopX >> leftTopY >> rightBottomX >> rightBottomY;
	Point leftTop = { leftTopX, leftTopY };
	Point rightBottom = { rightBottomX, rightBottomY };

	return std::make_unique<CRectangle>(color, leftTop, rightBottom);
}

std::unique_ptr<CShape> CShapeFactory::CreateTriangle(std::istream& strm, Color color) const
{
	double firstX = -1, firstY = -1, secondX = -1, secondY = -1, thirdX = -1, thirdY = -1;
	strm >> firstX >> firstY >> secondX >> secondY >> thirdX >> thirdY;
	Point firstVert = { firstX, firstY };
	Point secondVert = { secondX, secondY };
	Point thirdVert = { thirdX, thirdY };

	return std::make_unique<CTriangle>(color, firstVert, secondVert, thirdVert);
}

std::unique_ptr<CShape> CShapeFactory::CreateEllipse(std::istream& strm, Color color) const
{
	double centerX = -1, centerY = -1, horizontalRadius = -1, verticalRadius = -1;
	strm >> centerX >> centerY >> horizontalRadius >> verticalRadius;
	Point center = { centerX, centerY };

	return std::make_unique<CEllipse>(color, center, horizontalRadius, verticalRadius);
}