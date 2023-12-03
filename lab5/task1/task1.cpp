#include <iostream>
#include <memory>
#include <filesystem>
#include <optional>
#include "HtmlDocument.h"
#include "InsertParagraphCommand.h"
#include "Menu.h"
#include "Editor.h"

using namespace std;

int main()
{
	setlocale(LC_ALL, "");

	CEditor editor(cin, cout);
	editor.Start();
	return 0;
}