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

#ifndef CONSOLE_H_
#define CONSOLE_H_

#include <tchar.h>
#include <stdio.h>
#include "Defs.h"

#ifndef MAX_LOG_PRINT
#define MAX_LOG_PRINT 1024
#endif // !MAX_LOG_PRINT

#ifndef DEBUG
#define DEBUG FALSE
#endif // !DEBUG

// 格式化打印日志，多字节方式
#define CONSOLE_DECLARE_WRITE_A \
CHAR argsstr[MAX_LOG_PRINT]; \
va_list argslist; \
va_start(argslist, msg); \
vsnprintf_s(argsstr, sizeof(argsstr), msg, argslist); \
va_end(argslist); \
OutputDebugStringA(argsstr);

// 格式化打印日志，UNICODE方式
#define CONSOLE_DECLARE_WRITE_W \
WCHAR argsstr[MAX_LOG_PRINT]; \
va_list argslist; \
va_start(argslist, msg); \
vswprintf(argsstr, sizeof(argsstr), msg, argslist); \
va_end(argslist); \
OutputDebugStringW(argsstr);

#ifdef UNICODE
#define CONSOLE_DECLARE_WRITE CONSOLE_DECLARE_WRITE_W
#else
#define CONSOLE_DECLARE_WRITE CONSOLE_DECLARE_WRITE_A
#endif // !UNICODE

namespace totoro
{
/**
 * Console class file
 * 控制台输出类
 * Debug时在“输出”中打印日志
 *
 * @author 宋欢 <trotri@yeah.net>
 * @version $Id: Console.h 1 2015-01-29 10:02:06Z huan.song $
 * @since 1.0
 */
class Console
{
public:
	/**
	 * Priority constant for the println method; use Console.v.
	 */
	static CONST UINT VERBOSE;

	/**
	 * Priority constant for the println method; use Console.d.
	 */
	static CONST UINT DBUG;

	/**
	 * Priority constant for the println method; use Console.i.
	 */
	static CONST UINT INFO;

	/**
	 * Priority constant for the println method; use Console.w.
	 */
	static CONST UINT WARN;

	/**
	 * Priority constant for the println method; use Console.e.
	 */
	static CONST UINT ERR;

	/**
	 * Priority constant for the println method.
	 */
	static CONST UINT ASSERT;

public:
	Console();
	virtual ~Console();

public:
	/**
	 * 打印Verbose日志
	 *
	 * @param msg 日志内容
	 */
	static VOID v(CONST TCHAR * msg, ...);

	/**
	 * 打印Debug日志
	 *
	 * @param msg 日志内容
	 */
	static VOID d(CONST TCHAR * msg, ...);

	/**
	 * 打印Info日志
	 *
	 * @param msg 日志内容
	 */
	static VOID i(CONST TCHAR * msg, ...);

	/**
	 * 打印Warn日志
	 *
	 * @param msg 日志内容
	 */
	static VOID w(CONST TCHAR * msg, ...);

	/**
	 * 打印Err日志
	 *
	 * @param msg 日志内容
	 */
	static VOID e(CONST TCHAR * msg, ...);

};

}

#endif /* !CONSOLE_H_ */
