#pragma once
#include "ErrorLogger.h"

class WindowContainer;

class RenderWindow
{
public:
	bool Initialize(WindowContainer* pWindowContainer,
		HINSTANCE hInstance, std::string window_title,
		std::string window_class, int width, int height);
	~RenderWindow();

	bool ProcessMessages();
	HWND GetHWND() const;

private:
	void RegisterWindowClass();

	HWND handle = NULL; //handle to this window
	HINSTANCE hinstance = NULL; //handle to application instance

	std::string window_title = "";
	std::wstring window_title_wide = L"";	
	
	std::string window_class = "";
	std::wstring window_class_wide = L"";

	int width = 0;
	int height = 0;
};
