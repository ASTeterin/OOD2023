#pragma once
#include <string>
#include <memory>
#include "IImage.h"
#include "IParagraph.h"
#include "ConstDocumentItem.h"

using namespace std;

/*
	Элемент документа. Позволяет получить доступ к изображению или параграфу
*/
class CDocumentItem : public CConstDocumentItem
{
public:
	CDocumentItem(shared_ptr<IImage> image, shared_ptr<IParagraph> paragraph)
		: CConstDocumentItem(image, paragraph)
	{}
	// Возвращает указатель на изображение, либо nullptr, если элемент не является изображением
	shared_ptr<IImage> GetImage();
	// Возвращает указатель на параграф, либо nullptr, если элемент не является параграфом
	shared_ptr<IParagraph> GetParagraph();
};