#pragma once
#include <string>
#include <memory>
#include "IImage.h"
#include "IParagraph.h"
#include "ConstDocumentItem.h"

using namespace std;

/*
	������� ���������. ��������� �������� ������ � ����������� ��� ���������
*/
class CDocumentItem : public CConstDocumentItem
{
public:
	CDocumentItem(shared_ptr<IImage> image, shared_ptr<IParagraph> paragraph)
		: CConstDocumentItem(image, paragraph)
	{}
	// ���������� ��������� �� �����������, ���� nullptr, ���� ������� �� �������� ������������
	shared_ptr<IImage> GetImage();
	// ���������� ��������� �� ��������, ���� nullptr, ���� ������� �� �������� ����������
	shared_ptr<IParagraph> GetParagraph();
};