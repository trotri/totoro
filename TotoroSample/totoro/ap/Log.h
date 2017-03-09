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

#ifndef LOG_H_
#define LOG_H_

#include <tchar.h>
#include <stdio.h>
#include <process.h>
#include <ctime>
#include <fstream>
#include "Defs.h"

#ifndef MAX_LOG_PRINT
#define MAX_LOG_PRINT 1024
#endif // !MAX_LOG_PRINT

#ifndef MAX_DIRECTORY
#define MAX_DIRECTORY MAX_PATH - 32
#endif // !MAX_DIRECTORY

#ifndef DIR_LOG
#define DIR_LOG TEXT("log")
#endif // !DIR_LOG

#ifndef DEBUG
#define DEBUG FALSE
#endif // !DEBUG

// 格式化打印日志，多字节方式
#define LOG_DECLARE_WRITE_A \
CHAR argsstr[MAX_LOG_PRINT]; \
va_list argslist; \
va_start(argslist, msg); \
vsnprintf_s(argsstr, sizeof(argsstr), msg, argslist); \
va_end(argslist); \
return Write(priority, tag, argsstr);

// 格式化打印日志，UNICODE方式
#define LOG_DECLARE_WRITE_W \
WCHAR argsstr[MAX_LOG_PRINT]; \
va_list argslist; \
va_start(argslist, msg); \
vswprintf(argsstr, sizeof(argsstr), msg, argslist); \
va_end(argslist); \
return Write(priority, tag, argsstr);

#ifdef UNICODE
#define LOG_DECLARE_WRITE LOG_DECLARE_WRITE_W
#else
#define LOG_DECLARE_WRITE LOG_DECLARE_WRITE_A
#endif // !UNICODE

namespace totoro
{
/**
 * Log class file
 * 日志类
 * 设置
 * 配置属性->常规->输出目录
 * 配置属性->调试->工作目录
 *
 * @author 宋欢 <trotri@yeah.net>
 * @version $Id: Log.h 1 2015-01-29 10:02:06Z huan.song $
 * @since 1.0
 */
class Log
{
public:
	/**
	 * Priority constant for the println method; use Log.v.
	 */
	static CONST UINT VERBOSE;

	/**
	 * Priority constant for the println method; use Log.d.
	 */
	static CONST UINT DBUG;

	/**
	 * Priority constant for the println method; use Log.i.
	 */
	static CONST UINT INFO;

	/**
	 * Priority constant for the println method; use Log.w.
	 */
	static CONST UINT WARN;

	/**
	 * Priority constant for the println method; use Log.e.
	 */
	static CONST UINT ERR;

	/**
	 * Priority constant for the println method.
	 */
	static CONST UINT ASSERT;

private:
	/**
	 * 日志Id
	 */
	static UINT sLogId;

	/**
	 * 进程Id
	 */
	static UINT sProcessId;

	/**
	 * 目录
	 */
	static TCHAR sDirectory[MAX_DIRECTORY];

public:
	Log();
	virtual ~Log();

public:
	/**
	 * 打印Verbose日志
	 *
	 * @param tag 日志标识
	 * @param msg 日志内容
	 * @return The number of bytes written.
	 */
	static UINT v(CONST TCHAR * tag, CONST TCHAR * msg, ...);

	/**
	 * 打印Debug日志
	 *
	 * @param tag 日志标识
	 * @param msg 日志内容
	 * @return The number of bytes written.
	 */
	static UINT d(CONST TCHAR * tag, CONST TCHAR * msg, ...);

	/**
	 * 打印Info日志
	 *
	 * @param tag 日志标识
	 * @param msg 日志内容
	 * @return The number of bytes written.
	 */
	static UINT i(CONST TCHAR * tag, CONST TCHAR * msg, ...);

	/**
	 * 打印Warn日志
	 *
	 * @param tag 日志标识
	 * @param msg 日志内容
	 * @return The number of bytes written.
	 */
	static UINT w(CONST TCHAR * tag, CONST TCHAR * msg, ...);

	/**
	 * 打印Err日志
	 *
	 * @param tag 日志标识
	 * @param msg 日志内容
	 * @return The number of bytes written.
	 */
	static UINT e(CONST TCHAR * tag, CONST TCHAR * msg, ...);

	/**
	 * 获取日志Id
	 *
	 * @return 日志Id
	 */
	static UINT GetLogId();

	/**
	 * 获取进程Id
	 *
	 * @return 进程Id
	 */
	static UINT GetProcessId();

protected:
	/**
	 * 初始化
	 */
	static VOID Initialize();

	/**
	 * 打印日志
	 *
	 * @param priority 日志级别
	 * @param tag 日志标识
	 * @param msg 日志内容
	 * @return The number of bytes written.
	 */
	static UINT Write(UINT priority, CONST TCHAR * tag, CONST TCHAR * msg);

};

}

#endif /* !LOG_H_ */
