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

#include "Console.h"

using namespace totoro;

CONST UINT Console::VERBOSE = 2;
CONST UINT Console::DBUG    = 3;
CONST UINT Console::INFO    = 4;
CONST UINT Console::WARN    = 5;
CONST UINT Console::ERR     = 6;
CONST UINT Console::ASSERT  = 7;

Console::Console()
{
}

Console::~Console()
{
}

VOID Console::v(CONST TCHAR * msg, ...)
{
	OutputDebugString(TEXT("[Verbose] "));
	CONSOLE_DECLARE_WRITE
}

VOID Console::d(CONST TCHAR * msg, ...)
{
	if (DEBUG)
	{
		OutputDebugString(TEXT("[Debug] "));
		CONSOLE_DECLARE_WRITE
	}
}

VOID Console::i(CONST TCHAR * msg, ...)
{
	OutputDebugString(TEXT("[Info] "));
	CONSOLE_DECLARE_WRITE
}

VOID Console::w(CONST TCHAR * msg, ...)
{
	OutputDebugString(TEXT("[Warn] "));
	CONSOLE_DECLARE_WRITE
}

VOID Console::e(CONST TCHAR * msg, ...)
{
	OutputDebugString(TEXT("[Error] "));
	CONSOLE_DECLARE_WRITE
}
