#include "CImage.h"
#include "CResizeImageCommand.h"
#include <filesystem>
#include <string>
#include <iostream>
#include <memory>
#include <optional>

const Path IMAGE_FOLDER = "images";
const Path IMAGE_NAME_PATTERN = "image";

CImage::CImage(const Path& path, int width, int height, CHistory& history, int imageCounter)
	: m_history(history)
	, m_width(width)
	, m_height(height)
{
	Path imageName(IMAGE_NAME_PATTERN.string() + std::to_string(imageCounter));
	Path newImagePath = IMAGE_FOLDER / imageName;
	newImagePath.replace_extension(path.extension());
	m_fileName = newImagePath;
	std::filesystem::create_directory(IMAGE_FOLDER);
	try
	{
		std::filesystem::copy(path.u8string(), newImagePath.u8string(),std::filesystem::copy_options::overwrite_existing);
	}
	catch (std::exception)
	{
		throw std::invalid_argument("File does not exists: " + path.string());
	}
}

CImage::~CImage()
{
	try
	{
		remove(m_fileName);
	}
	catch (...)
	{
	}
}

Path CImage::GetPath() const
{
	return m_fileName;
}

int CImage::GetWidth() const
{
	return m_width;
}

int CImage::GetHeight() const
{
	return m_height;
}

void CImage::Resize(int width, int height)
{
	m_history.AddAndExecuteCommand(std::make_unique<CResizeImageCommand>(m_width, m_height, width, height));
}
