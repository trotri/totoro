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

#ifndef WINDOW_H_
#define WINDOW_H_

#include "ISingleton.h"
#include "String.h"
#include "Console.h"
#include "Log.h"
#include <list>

namespace totoro
{

class INode;

#define APP_TITLE TEXT("Totoro Sample")
#define WND_CLASS TEXT("TOTORO_WINDOW")
#define WND_WIDTH 1024
#define WND_HEIGHT 768
#define WND_X 400
#define WND_Y 20
#define WND_CMD_SHOW SW_SHOW

typedef LRESULT(CALLBACK* DRAWPROC)();
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

/**
 * Window class file
 * Window´°¿ÚÀà
 *
 * @author ËÎ»¶ <trotri@yeah.net>
 * @version $Id: Window.h 1 2015-01-30 10:02:06Z huan.song $
 * @since 1.0
 */
class Window : public ISingleton<Window>
{
public:
	CONST TCHAR * TAG = TEXT("Window");

	/**
	 * the Frames Per Second constant; default 60.
	 */
	static CONST UINT FPS;

private:
	HWND mHandle;
	WNDPROC mWndProc;
	DRAWPROC mDrawProc;
	String mWndClass;
	INT mCmdShow;
	String mTitle;
	RECTWH mWndSize;
	RECTXY mWndPos;
	POINT mCursorPoint;
	POSITION mCursorPos;
	FLOAT mRefreshInterval;
	std::list<INode *> mListeners;

public:
	Window();
	virtual ~Window();

protected:
	BOOL _Initialize();
	ATOM _RegisterClass();
	BOOL _InitInstance();
	BOOL _Show();
	BOOL _MoveRepaint();
	VOID _UpdateRefreshInterval();

public:
	MSG Run();

public:
	HWND GetHandle() CONST;
	CONST WNDPROC GetWndProc() CONST;
	CONST DRAWPROC GetDrawProc() CONST;
	BOOL SetDrawProc(DRAWPROC lpfnDrawProc);
	String GetWndClass() CONST;
	INT GetCmdShow() CONST;
	String GetTitle() CONST;
	BOOL SetTitle(String appTitle);
	INT GetCaptionHeight() CONST;
	UINT GetWndWidth() CONST;
	UINT GetWndHeight() CONST;
	CONST RECTWH * GetWndSize() CONST;
	BOOL SetWndSize(CONST RECTWH * wndSize);
	BOOL SetWndSize(UINT width, UINT height);
	INT GetWndX() CONST;
	INT GetWndY() CONST;
	CONST RECTXY * GetWndPos() CONST;
	BOOL SetWndPos(CONST RECTXY * wndPos);
	BOOL SetWndPos(INT x, INT y);
	CONST POINT * GetCursorPoint();
	CONST POSITION * GetCursorPos();
	FLOAT GetRefreshInterval() CONST;
	std::list<INode *> GetListeners() CONST;
	BOOL AddListener(INode * node);
	BOOL ClearListeners();
	BOOL PostCloseMessage();
};

}

#endif /* !WINDOW_H_ */
