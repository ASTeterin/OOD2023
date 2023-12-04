#include "CDocumentItem.h"

CDocumentItem::CDocumentItem(const std::shared_ptr<IParagraph>& paragraph)
	: CConstDocumentItem(paragraph)
{
}
CDocumentItem::CDocumentItem(const std::shared_ptr<IImage>& image)
	: CConstDocumentItem(image)
{
}

shared_ptr<IImage> CDocumentItem::GetImage()
{
	return m_image;
}

shared_ptr<IParagraph> CDocumentItem::GetParagraph()
{
	return m_paragraph;
}
