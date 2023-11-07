#pragma once
#include "CShape.h"
#include "Common.h"
#include <stdexcept>
#include <vector>

class CPolygon : public CShape
{
public:
	CPolygon(Color color, int vertexCount, Point centre, double radius)
		: m_vertexCount(vertexCount)
		, m_centre(centre)
		, m_radius(radius)
		, CShape(color)
	{
		if (centre.x < 0 || centre.y < 0 || radius < 0 || vertexCount < 0)
			throw std::invalid_argument("Invalid params");
	}

	void Draw(ICanvas& canvas) const override;
	int GetVertexCount() const;
	Point GetCentre() const;
	double GetRadius() const;

private:
	void CalculateVertex();

	int m_vertexCount;
	Point m_centre;
	double m_radius;
	std::vector<Point> m_vertex;
};