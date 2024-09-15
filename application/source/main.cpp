#include "pch.h"

#include "Application.h"

int main()
{
	Application& application = Application::getInstance();
	application.Create();
	application.Run();

	return 0;
}