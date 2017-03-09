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

#ifndef MACROS_H_
#define MACROS_H_

#define DEBUG TRUE

#include <Windows.h>

/**
 * timeGetTimeº¯Êý
 */
#include <MMSystem.h>
#pragma comment(lib, "winmm.lib")

namespace totoro
{
#define DELETE_PTR(p)   do { if (p) { delete (p); (p) = nullptr; } } while(0) 
#define RELEASE_PTR(p)  do { if (p) { (p)->Release(); (p) = nullptr; } } while (0)

#define TCOLOR     DWORD
#define TEXTURE_ID ULONG

#ifndef FINAL_H_
#define FINAL_H_

CONST FLOAT FINAL_PI = 3.141592654f;
CONST FLOAT FINAL_UNIT_RADIAN = (FINAL_PI / 180.0f);
CONST FLOAT FINAL_Z_INDEX_MIN = 0.0f;
CONST FLOAT FINAL_Z_INDEX_MAX = 1.0f;
CONST FLOAT FINAL_POSITION_EQUAL_DISTANCE = 2.0f;
CONST DWORD FINAL_COLLIDED_COLOR = 0xFF0000FF;

#endif // !FINAL_H_

}

#endif /* !MACROS_H_ */
