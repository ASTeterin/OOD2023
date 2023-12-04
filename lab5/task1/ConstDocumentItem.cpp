#include "ConstDocumentItem.h"

CConstDocumentItem::CConstDocumentItem(std::shared_ptr<IParagraph> const& paragraph)
	: m_paragraph(paragraph)
	, m_image(nullptr)
{
}

CConstDocumentItem::CConstDocumentItem(std::shared_ptr<IImage> const& image)
	: m_image(image)
	, m_paragraph(nullptr)
{
}

const std::shared_ptr<IImage> CConstDocumentItem::GetImage() const
{
	return m_image;
}

const std::shared_ptr<IParagraph> CConstDocumentItem::GetParagraph() const
{
	return m_paragraph;
}