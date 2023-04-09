#include "window.h"
#include <d3d12.h>
#include <windows.h>



// Window main
_Use_decl_annotations_
int WINAPI wWinMain(HINSTANCE /*hInstance*/, HINSTANCE /*hPrevInstance*/, LPWSTR /*pCmdLine*/, int /*nCmdShow*/)
{
	Window window;
	window.open();

	MSG msg = { };
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}
