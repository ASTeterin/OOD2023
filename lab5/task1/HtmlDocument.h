#pragma once
#include "IDocument.h"
#include <vector>
#include "History.h"

class CHtmlDocument : public IDocument
{
public:
	// ��������� �������� ������ � ��������� ������� (������� ����������� ��������)
	// ���� �������� position �� ������, ������� ���������� � ����� ���������
	shared_ptr<IParagraph> InsertParagraph(const string& text,
		optional<size_t> position = nullopt);

	// ��������� ����������� � ��������� ������� (������� ����������� ��������)
	// �������� path ������ ���� � ������������ �����������
	// ��� ������� ����������� ������ ������������ � ���������� images 
	// ��� ������������� ��������������� ������
	shared_ptr<IImage> InsertImage(const Path& path, int width, int height,
		optional<size_t> position = nullopt);

	// ���������� ���������� ��������� � ���������
	size_t GetItemsCount()const;

	// ������ � ��������� �����������
	CConstDocumentItem GetItem(size_t index)const;
	CDocumentItem GetItem(size_t index);

	// ������� ������� �� ���������
	void DeleteItem(size_t index);

	// ���������� ��������� ���������
	string GetTitle()const;
	// �������� ��������� ���������
	void SetTitle(const string& title);

	void ReplaceText(const std::string& text, size_t position);
	void ResizeImage(size_t position, int width, int height);

	// �������� � ����������� �������� Undo
	bool CanUndo()const;
	// �������� ������� ��������������
	void Undo();

	// �������� � ����������� �������� Redo
	bool CanRedo()const;
	// ��������� ���������� ������� ��������������
	void Redo();

	// ��������� �������� � ������� html. ����������� ����������� � ���������� images
	// ���� � ������������ ����������� ������������ ���� � ������������ HTML �����
	void Save(const Path& path)const;

private:
	void AssertPositionValid(size_t position) const;

	static string ReplaceCharacters(const string& str);

	CHistory m_history;
	vector<CDocumentItem> m_items;
	string m_title;
	Path m_path;
	int m_imageCounter = 0;
};

