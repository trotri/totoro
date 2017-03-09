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

#ifndef ISCENE_H_
#define ISCENE_H_

#include "INode.h"

namespace totoro
{
/**
 * IScene class file
 * 场景接口
 *
 * @author 宋欢 <trotri@yeah.net>
 * @version $Id: IScene.h 1 2015-01-30 16:02:06Z huan.song $
 * @since 1.0
 */
class IScene : public INode
{
public:
	CONST TCHAR * TAG = TEXT("IScene");

protected:
	IScene() {}

public:
	virtual ~IScene() {}

public:
	BOOL Visit()
	{
		if (!Begin())
		{
			Log::e(TAG, TEXT("Visit '%s' Begin Failure!"), GetName().c_str());
			return FALSE;
		}

		INode::Visit();

		if (!End())
		{
			Log::e(TAG, TEXT("Visit '%s' End Failure!"), GetName().c_str());
			return FALSE;
		}

		return TRUE;
	}

public:
	/**
	 * 开启场景，需子类实现该方法
	 */
	virtual BOOL Begin()
	{
		return TRUE;
	}

	/**
	 * 关闭场景，需子类实现该方法
	 */
	virtual BOOL End()
	{
		return TRUE;
	}
};

}

#endif /* !ISCENE_H_ */
