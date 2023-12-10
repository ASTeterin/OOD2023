#pragma once
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
	CDocumentItem(const std::shared_ptr<IParagraph>& paragraph);
	CDocumentItem(const std::shared_ptr<IImage>& image);
	// Возвращает указатель на изображение, либо nullptr, если элемент не является изображением
	shared_ptr<IImage> GetImage();
	// Возвращает указатель на параграф, либо nullptr, если элемент не является параграфом
	shared_ptr<IParagraph> GetParagraph();
};