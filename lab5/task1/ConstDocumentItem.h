#pragma once
#include <string>
#include <memory>
#include "IImage.h"
#include "IParagraph.h"

using namespace std;

/*
	Неизменяемый элемент документа
*/
class CConstDocumentItem
{
public:
	CConstDocumentItem(std::shared_ptr<IParagraph> const& paragraph);
	CConstDocumentItem(std::shared_ptr<IImage> const& image);

	const std::shared_ptr<IImage> GetImage() const;
	const std::shared_ptr<IParagraph> GetParagraph() const;
	virtual ~CConstDocumentItem() = default;

protected:
	std::shared_ptr<IParagraph> m_paragraph;
	std::shared_ptr<IImage> m_image;
};