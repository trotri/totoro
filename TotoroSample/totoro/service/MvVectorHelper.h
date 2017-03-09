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

#ifndef MV_VECTOR_HELPER_H_
#define MV_VECTOR_HELPER_H_

#include "..\ap\Window.h"
#include "..\util\Text.h"
#include "..\util\Collider.h"

namespace totoro
{
/**
 * MvVectorHelper class file
 * 计算游戏元素随向量自动移动类
 *
 * @author 宋欢 <trotri@yeah.net>
 * @version $Id: MvVectorHelper.h 1 2015-04-02 16:18:06Z huan.song $
 * @since 1.0
 */
class MvVectorHelper
{
public:
	typedef struct tagMV_VECTOR {
		POSITION start;
		POSITION end;
		FLOAT delay;
	} MV_VECTOR;

private:
	std::vector<MV_VECTOR> mMvVectors;
	UINT mSize;
	INT mIndex;
	POSITION mDestVertex;
	FLOAT mDelay;
	BOOL mIsBackward;
	BOOL mIsNeedBackward;

public:
	MvVectorHelper();
	virtual ~MvVectorHelper();

public:
	static MvVectorHelper * Create(String fileName);

protected:
	BOOL _Initialize(String fileName);

public:
	CONST POSITION * GetDestVertex(CONST POSITION * currPos);
	CONST POSITION * GetFirstVertex() CONST;
	BOOL IsNeedBackward() CONST;
	BOOL SetNeedBackward(BOOL isNeedBackward);
	BOOL Reset();
};

}

#endif /* !MV_VECTOR_HELPER_H_ */
