#include "CDesigner.h"
#include "CPainter.h"
#include "CPictureDraft.h"
#include "CShapeFactory.h"
#include <fstream>
#include <iostream>
#include "CCanvas.h"

int main()
{
	std::ofstream result("result.svg");
	IShapeFactoryPtr shapeFactory = std::make_unique<CShapeFactory>();

	CDesigner designer(std::move(shapeFactory));

	CPictureDraft draft = designer.CreateDraft(std::cin);

	CCanvas canvas(result);

	CPainter painter;

	painter.DrawPicture(draft, canvas);
}