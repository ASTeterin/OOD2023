#pragma once
#include "History.h"
#include "IImage.h"

class CImage : public IImage
{
public:
	CImage(const Path& path, int width, int height, CHistory& history, int imageCounter);
	~CImage();

	Path GetPath() const override;
	int GetWidth() const override;
	int GetHeight() const override;
	void Resize(int width, int height) override;

private:
	Path m_fileName;
	int m_width;
	int m_height;
	CHistory& m_history;
};

