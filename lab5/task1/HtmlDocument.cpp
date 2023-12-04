#include "HtmlDocument.h"
#include "CParagraph.h"
#include "CImage.h"
#include "CDeleteItemCommand.h"
#include "CInsertDocumentItemCommand.h"
#include "ChangeStringCommand.h"
#include "SetTitleCommand.h"
#include <fstream>
#include <string>
#include <iostream>
#include <filesystem>

shared_ptr<IParagraph> CHtmlDocument::InsertParagraph(const string& text, optional<size_t> position)
{
	auto paragraph = std::make_shared<CParagraph>(text, m_history);
	auto item = CDocumentItem(paragraph);
	m_history.AddAndExecuteCommand(make_unique<CInsertDocumentItemCommand>(m_items, item, position));

	return paragraph;
}

shared_ptr<IImage> CHtmlDocument::InsertImage(const Path& path, int width, int height, optional<size_t> position)
{
	shared_ptr<IImage> image = std::make_shared<CImage>(path, width, height, m_history, m_imageCounter++);
	auto item = CDocumentItem(image);
	m_history.AddAndExecuteCommand(make_unique<CInsertDocumentItemCommand>(m_items, item, position));

    return image;
}

size_t CHtmlDocument::GetItemsCount() const
{
    return m_items.size();
}

CConstDocumentItem CHtmlDocument::GetItem(size_t index) const
{
    AssertPositionValid(index);
    return m_items[index];
}

CDocumentItem CHtmlDocument::GetItem(size_t index)
{
    AssertPositionValid(index);
    return m_items[index];
}

void CHtmlDocument::DeleteItem(size_t index)
{
    AssertPositionValid(index);
	m_history.AddAndExecuteCommand(std::make_unique<CDeleteItemCommand>(m_items, index));
}

string CHtmlDocument::GetTitle() const
{
    return m_title;
}

void CHtmlDocument::SetTitle(const string& title)
{
	m_history.AddAndExecuteCommand(std::make_unique<CSetTitleCommand>(m_title, title));
}

void CHtmlDocument::ReplaceText(const std::string& text, size_t position)
{
	if (position >= GetItemsCount())
	{
		throw std::invalid_argument("Invalid position");
	}

	auto item = GetItem(position);
	auto paragraph = item.GetParagraph();
	if (paragraph == nullptr)
	{
		throw std::invalid_argument("Invalid item type");
	}

	paragraph->SetText(text);
}

void CHtmlDocument::ResizeImage(size_t position, int width, int height)
{
	if (position >= GetItemsCount())
	{
		throw std::invalid_argument("Invalid position");
	}

	auto item = GetItem(position);
	if (item.GetImage() == nullptr)
	{
		throw std::invalid_argument("Invalid item type");
	}

	item.GetImage()->Resize(width, height);
}

void CHtmlDocument::AssertPositionValid(size_t position) const
{
    if (position > m_items.size() - 1)
        throw invalid_argument("Position is out of range");
}

bool CHtmlDocument::CanUndo() const
{
    return m_history.CanUndo();
}

void CHtmlDocument::Undo()
{
    m_history.Undo();
}

bool CHtmlDocument::CanRedo() const
{
    return m_history.CanRedo();
}

void CHtmlDocument::Redo()
{
    m_history.Redo();
}

void CHtmlDocument::Save(const Path& path) const
{
    ofstream output(path);
    output << "<html>" << endl;
	output << "<h1>" << ReplaceCharacters(GetTitle()) << "</h1>" << endl;
    for (size_t i = 0; i < GetItemsCount(); i++)
    {
        auto item = GetItem(i);
        
		if (auto paragraph = item.GetParagraph())
			output << "<p>" << ReplaceCharacters(paragraph->GetText()) << "</p>" << endl;
		else if (auto image = item.GetImage())
		{
			Path src = image->GetPath();
			int width = image->GetWidth();
			int height = image->GetHeight();

			output << "<img src=\"" + src.string() + "\" width=\"" + std::to_string(width) + "\" height=\"" + std::to_string(height) + "\" />" << std::endl;
		}
    }
    output << "</html>";
}

std::string CHtmlDocument::ReplaceCharacters(const std::string& str)
{
	std::string result;
	for (const auto ch : str)
	{
		switch (ch)
		{
		case '<':
			result.append("&lt;");
			break;
		case '>':
			result.append("&gt;");
			break;
		case '"':
			result.append("&quot;");
			break;
		case '\'':
			result.append("&apos;");
			break;
		case '&':
			result.append("&amp;");
			break;
		default:
			result += ch;
		}
	}
	return result;
}
