#pragma once
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
	CDocumentItem(const std::shared_ptr<IParagraph>& paragraph);
	CDocumentItem(const std::shared_ptr<IImage>& image);
	// ���������� ��������� �� �����������, ���� nullptr, ���� ������� �� �������� ������������
	shared_ptr<IImage> GetImage();
	// ���������� ��������� �� ��������, ���� nullptr, ���� ������� �� �������� ����������
	shared_ptr<IParagraph> GetParagraph();
};