#pragma once
#include "CShape.h"
#include "Common.h"
#include <stdexcept>

class CTriangle : public CShape
{
public:
	CTriangle(Color color, Point vertex1, Point vertex2, Point vertex3)
		: m_vertex1(vertex1)
		, m_vertex2(vertex2)
		, m_vertex3(vertex3)
		, CShape(color)
	{
		if (vertex1.x < 0 || vertex1.y < 0 || vertex2.x < 0 || vertex2.y < 0 || vertex3.x < 0 || vertex3.y < 0)
			throw std::invalid_argument("Invalid params");
	}

	void Draw(ICanvas& canvas) const override;
	Point GetVertex1() const;
	Point GetVertex2() const;
	Point GetVertex3() const;

private:
	Point m_vertex1;
	Point m_vertex2;
	Point m_vertex3;
};
