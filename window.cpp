#include "window.h"

#include <windows.h>
#include <string>


class PlatformWindowImpl
{
public:
	HWND hwnd = NULL;
};


static LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);


void errorMessageBox(std::wstring&& message)
{
	// System error codes
	// https://learn.microsoft.com/en-us/windows/win32/debug/system-error-codes
	DWORD errorCode = GetLastError();
	std::wstring errorMessage(message);
	errorMessage += L"\nLast error code: " + std::to_wstring(errorCode);
	MessageBox(NULL, errorMessage.c_str(), L"ERROR", MB_OK | MB_ICONEXCLAMATION);
}


Window::Window()
	: mImpl(new PlatformWindowImpl)
{
}

Window::~Window()
{
	delete mImpl;
}


bool Window::open()
{
	const wchar_t CLASS_NAME[] = L"Game window class";
	const wchar_t WINDOW_NAME[] = L"SampleGame";
	const LONG width = 1920;
	const LONG height = 1080;
	RECT windowRect = { 0, 0, width, height };

	HINSTANCE hInstance = NULL;
	if (!GetModuleHandleEx(0, NULL, &hInstance))
	{
		errorMessageBox(L"Error getting window handle");
		return false;
	}

	WNDCLASSEX windowClass = { 0 };
	windowClass.cbSize = sizeof(WNDCLASSEX);
	windowClass.hIconSm = NULL;
	windowClass.lpfnWndProc = (WNDPROC)WindowProc;
	windowClass.lpszClassName = CLASS_NAME;
	windowClass.hInstance = hInstance;
	windowClass.lpszMenuName = NULL;
	windowClass.style = 0;
	windowClass.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	windowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	windowClass.hbrBackground = NULL;
	windowClass.cbClsExtra = 0;
	windowClass.cbWndExtra = 0;

	if (!RegisterClassEx(&windowClass))
	{
		errorMessageBox(L"Failed to register window class");
		return false;
	}

	if (!AdjustWindowRectEx(&windowRect, WS_OVERLAPPEDWINDOW, FALSE, WS_EX_OVERLAPPEDWINDOW))
	{
		errorMessageBox(L"Error on adjust window rect");
		return false;
	}

	mImpl->hwnd = CreateWindowEx(
		0,                   // Optional window styles.
		CLASS_NAME,          // Window class
		WINDOW_NAME,         // Window text
		WS_OVERLAPPEDWINDOW, // Window style
		CW_USEDEFAULT,       // x
		CW_USEDEFAULT,       // y
		CW_USEDEFAULT,       // width
		CW_USEDEFAULT,       // height
		NULL,                // Parent window
		NULL,                // Menu
		hInstance,           // Instance handle
		NULL                 // Additional application data
	);

	if (!mImpl->hwnd)
	{
		errorMessageBox(L"Failed to create window");
		return false;
	}

	if (ShowWindow(mImpl->hwnd, SW_SHOW))
	{
		errorMessageBox(L"Show window error");
		return false;
	}

	return true;
}


static LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CREATE:
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_MOVE:
		break;
	case WM_SIZE:
		break;
	case WM_DISPLAYCHANGE:
		break;

	case WM_PAINT:
		break;

	default:
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
		break;
	}
}
