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

#ifndef COLLIDER_H_
#define COLLIDER_H_

#include "..\ap\Defs.h"
#include "..\graphics\Texture.h"

namespace totoro
{
/**
 * Collider class file
 * 通过颜色判定碰撞类
 *
 * @author 宋欢 <trotri@yeah.net>
 * @version $Id: Collider.h 1 2015-04-02 16:18:06Z huan.song $
 * @since 1.0
 */
class Collider
{
public:
	static CONST TCHAR * TAG;

public:
	Collider();
	virtual ~Collider();

public:
	/**
	 * 判断点与盒子是否碰撞
	 * @param CONST POSITION * pos
	 * @param CONST RECT4P * box
	 * @return BOOL
	 */
	static BOOL IsCollide(CONST POSITION * pos, CONST RECT4P * box);

	/**
	 * 判断两个盒子是否碰撞
	 * @param CONST RECT4P * box1
	 * @param CONST RECT4P * box2
	 * @param BOOL isMutual
	 * @return BOOL
	 */
	static BOOL IsCollide(CONST RECT4P * box1, CONST RECT4P * box2, BOOL isMutual);

	/**
	 * 判定点与贴图颜色是否碰撞
	 * @param CONST POSITION * pos
	 * @param Texture * texture
	 * @param BOOL isAllowOutside
	 * @return BOOL
	 */
	static BOOL IsCollide(CONST POSITION * pos, Texture * texture, BOOL isAllowOutside);

	/**
	 * 判断两点是否重合
	 * @param CONST POSITION * pos1
	 * @param CONST POSITION * pos2
	 * @return BOOL
	 */
	static BOOL IsEqual(CONST POSITION * pos1, CONST POSITION * pos2);

	/**
	 * 获取两点距离
	 * @param CONST POSITION * pos1
	 * @param CONST POSITION * pos2
	 * @return BOOL
	 */
	static FLOAT GetDistance(CONST POSITION * pos1, CONST POSITION * pos2);
};

}

#endif /* !COLLIDER_H_ */
