#include "CCanvas.h"
#include "CEllipse.h"
#include "CGroupShape.h"
#include "CRectangle.h"
#include "CSlide.h"
#include "CTriangle.h"
#include "CommonTypes.h"
#include <cstdint>
#include <fstream>
#include <iostream>

using namespace std;

int main()
{
	CSlide slide(1200, 1200);
	ofstream out("result.svg");
	CCanvas canvas(out);
	canvas.BeginDraw();
	shared_ptr<IShape> road = make_shared<CRectangle>(PointD{ 0, 600 }, 1200, 500);
	road->GetFillStyle()->SetColor(0x808080);
	shared_ptr<IShape> frontWheel = make_shared<CEllipse>(PointD{ 200, 500 }, 50, 50);
	frontWheel->GetFillStyle()->SetColor(0);
	shared_ptr<IShape> backWheel = make_shared<CEllipse>(PointD{ 800, 500 }, 50, 50);
	backWheel->GetFillStyle()->SetColor(0);

	shared_ptr<IShape> bodywork = make_shared<CRectangle>(PointD{ 100, 400 }, 900, 100);
	bodywork->GetFillStyle()->SetColor(0x793119);
	shared_ptr<IShape> windscreen = make_shared<CTriangle>(PointD{ 800, 200 }, PointD{ 800, 400 }, PointD{ 1000, 400 });
	windscreen->GetFillStyle()->SetColor(0x46F5F4);
	shared_ptr<IShape> cabin = make_shared<CRectangle>(PointD{ 700, 200 }, 200, 200);
	cabin->GetFillStyle()->SetColor(0x793119);
	std::vector<std::shared_ptr<IShape>> shapes;
	shapes.push_back(road);

	shared_ptr<IGroupShape> picture = make_shared<CGroupShape>(shapes);
	picture->InsertShape(bodywork);
	picture->InsertShape(windscreen);
	picture->InsertShape(cabin);
	picture->InsertShape(frontWheel);
	picture->InsertShape(backWheel);
	picture->GetFillStyle()->SetColor(0x00FFff);
	picture->GetOutlineStyle()->SetColor(0x0000ff);
	picture->GetOutlineStyle()->SetStrokeSize(9);

	slide.InsertShape(picture);
	RectD frame = picture->GetFrame();
	picture->SetFrame(RectD{ 0, 700, 800, 300 });
	slide.Draw(canvas);
	canvas.EndDraw();
}