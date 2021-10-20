#include <Windows.h>
#include<stdio.h>
#include "Utility.cpp"

global bool Running = true;

struct RenderState
{
	void* Memory;
	int Width;
	int Height;
	BITMAPINFO BitMapInfo;
};


global RenderState Buffer;

#include "Renderer.cpp"
#include "PlatformComman.cpp"
#include "Game.cpp"

Internal LRESULT CALLBACK 
WindowCallback(HWND Window, UINT Message, WPARAM WParam, LPARAM LParam)
{
	LRESULT Result = 0;

	switch (Message)
	{
		case WM_CLOSE:
		case WM_DESTROY:
			Running = false;
			break;

		case WM_SIZE:
			RECT Rect;
			GetClientRect(Window, &Rect);
			Buffer.Width = Rect.right - Rect.left;
			Buffer.Height = Rect.bottom - Rect.top;

			if (Buffer.Memory)
			{
				VirtualFree(Buffer.Memory, 0, MEM_RELEASE);
			}

			
			Buffer.Memory = VirtualAlloc(0, Buffer.Height * Buffer.Width * sizeof(unsigned int), MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

			Buffer.BitMapInfo.bmiHeader.biSize = sizeof(Buffer.BitMapInfo.bmiHeader);
			Buffer.BitMapInfo.bmiHeader.biWidth = Buffer.Width;
			Buffer.BitMapInfo.bmiHeader.biHeight = -Buffer.Height;
			Buffer.BitMapInfo.bmiHeader.biPlanes = 1;
			Buffer.BitMapInfo.bmiHeader.biBitCount = 32;
			Buffer.BitMapInfo.bmiHeader.biCompression = BI_RGB;
			break;

		default:
			Result = DefWindowProcA(Window, Message, WParam, LParam);
	}

	return Result;
}

int WinMain(HINSTANCE hInstance,
			HINSTANCE hPrevInstance,
			LPSTR     lpCmdLine,
			int       nShowCmd)
{
	//Creat Window Class
	WNDCLASSA WindowClass = {};
	WindowClass.style = CS_HREDRAW | CS_VREDRAW;
	WindowClass.lpszClassName = "Game Window Class";
	WindowClass.lpfnWndProc = WindowCallback;
	// Register Class
	RegisterClassA(&WindowClass);

	// Create Window
	HWND Window = CreateWindowA(WindowClass.lpszClassName, "MySecondGP", WS_VISIBLE | WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 1920, 1080, 0, 0, hInstance, 0);
	HDC DeviceContext = GetDC(Window);

	Input Input = {};

	float DeltaTime = 0.0166666666f;
	LARGE_INTEGER FrameBegin;
	QueryPerformanceCounter(&FrameBegin);
	LARGE_INTEGER PerformanceFrequency;
	QueryPerformanceFrequency(&PerformanceFrequency);
	while (Running)
	{
		// INput 
		MSG Message;
		for (int i = 0; i < BUTTON_COUNT; i++)
		{
			Input.Buttons[i].Changed = false;
		}

		while (PeekMessageA(&Message, Window, 0, 0, PM_REMOVE))
		{
			switch (Message.message)
			{
			case WM_KEYUP:
			case WM_KEYDOWN:
			{
				uint32 VKCode = (uint32)Message.wParam;
				bool IsDown = ((Message.lParam & (1 << 31)) == 0);

#define ProcessButton(BUTTON, VKCODE)\
case VKCODE:{\
Input.Buttons[BUTTON].IsDown = IsDown;\
Input.Buttons[BUTTON].Changed = true;\
}break;
				switch (VKCode)
				{

					ProcessButton(BUTTON_UP, VK_UP);
					ProcessButton(BUTTON_RIGHT, VK_RIGHT);
					ProcessButton(BUTTON_LEFT, VK_LEFT);
					ProcessButton(BUTTON_DOWN, VK_DOWN);
				}
			}break;

			default:
				TranslateMessage(&Message);
				DispatchMessage(&Message);
			}
		}

		// Simulate
		SimulateGame(&Input, DeltaTime);
		// Render 
		StretchDIBits(DeviceContext, 0, 0, Buffer.Width, Buffer.Height, 0, 0, Buffer.Width, Buffer.Height, Buffer.Memory, &Buffer.BitMapInfo, DIB_RGB_COLORS, SRCCOPY);

		LARGE_INTEGER FrameEnd;
		QueryPerformanceCounter(&FrameEnd);
		DeltaTime = (float)(FrameEnd.QuadPart - FrameBegin.QuadPart) / (float)PerformanceFrequency.QuadPart;
		float FPS = 1 / DeltaTime;
		FrameBegin = FrameEnd;

		char TextBuffer[256];
		_snprintf_s(TextBuffer, sizeof(TextBuffer),
			"DeltaTime:%f, FPS:%.2f\n", DeltaTime, FPS);
		OutputDebugStringA(TextBuffer);
	}


}