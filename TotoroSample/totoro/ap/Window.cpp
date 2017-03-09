/*
 * Copyright (C) 2015 The C++ Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "Window.h"
#include "INode.h"

using namespace totoro;

CONST UINT Window::FPS = 60;

Window::Window() : mHandle(NULL), mWndProc(WndProc), mDrawProc(NULL), mCmdShow(WND_CMD_SHOW), mTitle(APP_TITLE), mWndClass(WND_CLASS), mRefreshInterval(0)
{
	mWndSize.width = WND_WIDTH;
	mWndSize.height = WND_HEIGHT;
	mWndPos.x = WND_X;
	mWndPos.y = WND_Y;
	ZeroMemory(&mCursorPoint, sizeof(POINT));

	_Initialize();
}

Window::~Window()
{
}

BOOL Window::_Initialize()
{
	Log::d(TAG, TEXT("_Initialize %s"), TEXT("Test"));
	Console::d(TEXT("%s::_Initialize\n"), TAG);

	_RegisterClass();

	if (_InitInstance())
	{
		return TRUE;
	}

	return FALSE;
}

ATOM Window::_RegisterClass()
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = mWndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = NULL;
	wcex.hIcon = NULL;
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = mWndClass.c_str();
	wcex.hIconSm = NULL;

	return RegisterClassEx(&wcex);
}

BOOL Window::_InitInstance()
{
	mHandle = CreateWindow(GetWndClass().c_str(), GetTitle().c_str(), WS_OVERLAPPEDWINDOW, GetWndX(), GetWndY(), GetWndWidth(), GetWndHeight(), NULL, NULL, NULL, NULL);
	if (!mHandle)
	{
		Console::e(TEXT("%s::_InitInstance CreateWindow Failure!\n"), TAG);
		return FALSE;
	}

	return TRUE;
}

BOOL Window::_Show()
{
	BOOL result = ShowWindow(GetHandle(), GetCmdShow());
	UpdateWindow(GetHandle());
	return result;
}

BOOL Window::_MoveRepaint()
{
	return MoveWindow(GetHandle(), GetWndX(), GetWndY(), GetWndWidth(), GetWndHeight(), TRUE);
}

VOID Window::_UpdateRefreshInterval()
{
	static FLOAT minRefreshInterval = 1000 / FPS;
	static DWORD dwLastTime = timeGetTime();

	DWORD dwNowTime = timeGetTime();
	mRefreshInterval = (dwNowTime - dwLastTime) * 0.001f;

	if (mRefreshInterval < minRefreshInterval)
	{
		Sleep(static_cast<DWORD>(minRefreshInterval - mRefreshInterval));
		dwLastTime = timeGetTime();
	}
	else
	{
		dwLastTime = dwNowTime;
	}
}

MSG Window::Run()
{
	_Show();

	MSG msg;

	ZeroMemory(&msg, sizeof(msg));
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			_UpdateRefreshInterval();
			if (mDrawProc != NULL)
			{
				mDrawProc();
			}
		}
	}

	return msg;
}

HWND Window::GetHandle() CONST
{
	return mHandle;
}

CONST WNDPROC Window::GetWndProc() CONST
{
	return mWndProc;
}

CONST DRAWPROC Window::GetDrawProc() CONST
{
	return mDrawProc;
}

BOOL Window::SetDrawProc(DRAWPROC lpfnDrawProc)
{
	if (lpfnDrawProc == NULL)
	{
		return FALSE;
	}

	mDrawProc = lpfnDrawProc;
	return TRUE;
}

String Window::GetWndClass() CONST
{
	return mWndClass;
}

INT Window::GetCmdShow() CONST
{
	return mCmdShow;
}

String Window::GetTitle() CONST
{
	return mTitle;
}

BOOL Window::SetTitle(String appTitle)
{
	if (appTitle.IsEmpty())
	{
		return FALSE;
	}

	mTitle = appTitle;
	return SetWindowText(GetHandle(), mTitle.c_str());
}

INT Window::GetCaptionHeight() CONST
{
	return GetSystemMetrics(SM_CYCAPTION);
}

UINT Window::GetWndWidth() CONST
{
	return mWndSize.width;
}

UINT Window::GetWndHeight() CONST
{
	return mWndSize.height;
}

CONST RECTWH * Window::GetWndSize() CONST
{
	return &mWndSize;
}

BOOL Window::SetWndSize(CONST RECTWH * wndSize)
{
	if (wndSize == NULL)
	{
		return FALSE;
	}

	return SetWndSize(wndSize->width, wndSize->height);
}

BOOL Window::SetWndSize(UINT width, UINT height)
{
	mWndSize.width = width;
	mWndSize.height = height;
	_MoveRepaint();
	return TRUE;
}

INT Window::GetWndX() CONST
{
	return mWndPos.x;
}

INT Window::GetWndY() CONST
{
	return mWndPos.y;
}

CONST RECTXY * Window::GetWndPos() CONST
{
	return &mWndPos;
}

BOOL Window::SetWndPos(CONST RECTXY * wndPos)
{
	if (wndPos == NULL)
	{
		return FALSE;
	}

	return SetWndPos(wndPos->x, wndPos->y);
}

BOOL Window::SetWndPos(INT x, INT y)
{
	mWndPos.x = x;
	mWndPos.y = y;
	_MoveRepaint();
	return TRUE;
}

CONST POINT * Window::GetCursorPoint()
{
	::GetCursorPos(&mCursorPoint);
	ScreenToClient(GetHandle(), &mCursorPoint);
	return &mCursorPoint;
}

CONST POSITION * Window::GetCursorPos()
{
	CONST POINT * cursorPoint = GetCursorPoint();
	mCursorPos.x = static_cast<FLOAT>(cursorPoint->x);
	mCursorPos.y = static_cast<FLOAT>(cursorPoint->y);
	return &mCursorPos;
}

FLOAT Window::GetRefreshInterval() CONST
{
	return mRefreshInterval;
}

std::list<INode *> Window::GetListeners() CONST
{
	return mListeners;
}

BOOL Window::AddListener(INode * node)
{
	if (node == NULL)
	{
		return FALSE;
	}

	mListeners.push_back(node);
	return TRUE;
}

BOOL Window::ClearListeners()
{
	mListeners.clear();
	return TRUE;
}

BOOL Window::PostCloseMessage()
{
	return PostMessage(GetHandle(), WM_CLOSE, 0, 0);
}

LRESULT CALLBACK totoro::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;
	Window * window = Window::GetInstance();

	INode * tmp = NULL;
	std::list<INode *> nodes = window->GetListeners();
	for (std::list<INode *>::reverse_iterator it = nodes.rbegin(); it != nodes.rend(); it++)
	{
		tmp = *it;
		if (tmp != NULL)
		{
			if (!tmp->IsDraw())
			{
				continue;
			}

			if (!tmp->WndProc(hWnd, message, wParam, lParam))
			{
				break;
			}
		}
	}

	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		EndPaint(hWnd, &ps);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}
