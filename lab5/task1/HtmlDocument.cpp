#include "HtmlDocument.h"
#include "CParagraph.h"
#include "CImage.h"
#include <fstream>
#include <string>
#include <iostream>
#include <filesystem>

const Path IMAGE_FOLDER = "images";
const Path IMAGE_NAME_PATTERN = "image";

shared_ptr<IParagraph> CHtmlDocument::InsertParagraph(const string& text, optional<size_t> position)
{
    shared_ptr<IParagraph> paragraph = make_shared<CParagraph>(text);
    CDocumentItem itemHolder(nullptr, paragraph);
    if (position == nullopt)
        m_items.push_back(itemHolder);
    else
    {
        AssertPositionValid(*position);
        auto it = m_items.begin() + *position;
        m_items.insert(it, itemHolder);
    }
    return paragraph;
}

shared_ptr<IImage> CHtmlDocument::InsertImage(const Path& path, int width, int height, optional<size_t> position)
{
    Path imageName(IMAGE_NAME_PATTERN.string() + to_string(m_imageCounter++));
    Path newImagePath = IMAGE_FOLDER / imageName;
    newImagePath.replace_extension(path.extension());
    filesystem::create_directory(IMAGE_FOLDER);
	try
	{
		filesystem::copy(path.u8string(), newImagePath.u8string(), filesystem::copy_options::overwrite_existing);
	}
	catch (exception)
	{
		throw invalid_argument("File does not exists: " + m_path.string());
	}
    shared_ptr<IImage> image = make_shared<CImage>(newImagePath, width, height);
    CDocumentItem itemHolder(image, nullptr);
    if (position == nullopt)
        m_items.push_back(itemHolder);
    else
    {
        AssertPositionValid(*position);
        auto it = m_items.begin() + *position;
        m_items.insert(it, itemHolder);
    }

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
    m_items.erase(m_items.begin() + index);
}

string CHtmlDocument::GetTitle() const
{
    return m_title;
}

void CHtmlDocument::SetTitle(const string& title)
{
    m_title = title;
}

void CHtmlDocument::AssertPositionValid(size_t position) const
{
    if (position > m_items.size() - 1)
        throw invalid_argument("Position is out of bounce");
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

void CHtmlDocument::HandleCommand(unique_ptr<ICommand>&& command)
{
    m_history.AddAndExecuteCommand(move(command));
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
