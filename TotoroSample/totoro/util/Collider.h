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
 * ͨ����ɫ�ж���ײ��
 *
 * @author �λ� <trotri@yeah.net>
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
	 * �жϵ�������Ƿ���ײ
	 * @param CONST POSITION * pos
	 * @param CONST RECT4P * box
	 * @return BOOL
	 */
	static BOOL IsCollide(CONST POSITION * pos, CONST RECT4P * box);

	/**
	 * �ж����������Ƿ���ײ
	 * @param CONST RECT4P * box1
	 * @param CONST RECT4P * box2
	 * @param BOOL isMutual
	 * @return BOOL
	 */
	static BOOL IsCollide(CONST RECT4P * box1, CONST RECT4P * box2, BOOL isMutual);

	/**
	 * �ж�������ͼ��ɫ�Ƿ���ײ
	 * @param CONST POSITION * pos
	 * @param Texture * texture
	 * @param BOOL isAllowOutside
	 * @return BOOL
	 */
	static BOOL IsCollide(CONST POSITION * pos, Texture * texture, BOOL isAllowOutside);

	/**
	 * �ж������Ƿ��غ�
	 * @param CONST POSITION * pos1
	 * @param CONST POSITION * pos2
	 * @return BOOL
	 */
	static BOOL IsEqual(CONST POSITION * pos1, CONST POSITION * pos2);

	/**
	 * ��ȡ�������
	 * @param CONST POSITION * pos1
	 * @param CONST POSITION * pos2
	 * @return BOOL
	 */
	static FLOAT GetDistance(CONST POSITION * pos1, CONST POSITION * pos2);
};

}

#endif /* !COLLIDER_H_ */
