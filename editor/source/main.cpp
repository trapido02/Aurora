#include "pch.h"

#include "Editor.h"

int main()
{
	Editor& editor = Editor::getInstance();
	editor.Create();
	editor.Run();

	return 0;
}