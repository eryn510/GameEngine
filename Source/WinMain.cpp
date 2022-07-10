#include <windows.h>

#define MAX_NAME_STRING 256
#define HINSTANCE() GetModuleHandle(NULL)

WCHAR WindowsClass[MAX_NAME_STRING];
WCHAR WindowsTitle[MAX_NAME_STRING];
INT WindowsWidth;
INT WindowsHeight;

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) 
{
	switch (msg) 
	{
	case WM_CLOSE:
		PostQuitMessage(2);
		break;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

int CALLBACK WinMain(HINSTANCE, HINSTANCE, LPSTR, INT) 
{

	//Initialize Global Variables
	wcscpy_s(WindowsClass, TEXT("TDGClass"));
	wcscpy_s(WindowsTitle, TEXT("TDGWindow"));
	WindowsWidth = 1366;
	WindowsHeight = 768;

	//Create Window Class
	WNDCLASSEX wcex;
	
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_OWNDC;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;

	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)GetStockObject(NULL_BRUSH);

	wcex.hIcon = LoadIcon(0, IDI_APPLICATION);
	wcex.hIconSm = LoadIcon(0, IDI_APPLICATION);

	wcex.lpszClassName = WindowsClass;

	wcex.lpszMenuName = nullptr;

	wcex.hInstance = HINSTANCE();

	wcex.lpfnWndProc = WndProc;

	RegisterClassEx(&wcex);

	//Create and Display Window

	HWND hWnd = CreateWindowEx(0, WindowsClass, WindowsTitle, WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU,
		CW_USEDEFAULT, 0, WindowsWidth, WindowsHeight, nullptr, nullptr, HINSTANCE(), nullptr);

	if (!hWnd) {
		MessageBox(0, L"Failed to Create Window!.", 0, 0);
		return 0;
	}

	ShowWindow(hWnd, SW_SHOW);

	//Listen for Message Events

	MSG msg = { 0 };
	while (msg.message != WM_QUIT) 
	{

		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE)) 
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);

		}
	}

	if (msg.message == WM_QUIT) 
	{
		return msg.wParam;
	}
	else if (msg.wParam < 0) 
	{
		return -1;
	}
	else
	{
		return 0;
	}


}