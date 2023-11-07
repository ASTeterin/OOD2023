#define _USE_MATH_DEFINES // for C++
#include <cmath>
#include "CPolygon.h"
#include "ICanvas.h"

void CPolygon::Draw(ICanvas& canvas) const
{
	canvas.SetColor(m_color);

	for (Point point : m_vertex)
	{
		//	canvas.DrawLine(point, m_vertex2);
	}
}

Point CPolygon::GetCentre() const
{
	return m_centre;
}

double CPolygon::GetRadius() const
{
	return m_radius;
}

int CPolygon::GetVertexCount() const
{
	return m_vertexCount;
}

void CPolygon::CalculateVertex()
{
	double angle;
	for (int i = 0; i < m_vertexCount - 1; i++)
	{
		angle = 2 * M_PI * i / m_vertexCount;
		m_vertex.push_back(Point{ m_radius * cos(angle) + m_centre.x, m_radius * sin(angle) + m_centre.y });
	}
}
