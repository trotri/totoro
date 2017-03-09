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

#ifndef ISINGLETON_H_
#define ISINGLETON_H_

#include <assert.h>
#include <Windows.h>

namespace totoro
{
/**
 * ISingleton class file
 * 单例模式接口
 *
 * @author 宋欢 <trotri@yeah.net>
 * @version $Id: ISingleton.h 1 2016-02-06 10:00:06Z huan.song $
 * @since 1.0
 */
template <typename T>
class ISingleton
{
public:
	static T * sInstance;

public:
	ISingleton()
	{
		assert(sInstance == NULL);
		sInstance = static_cast<T *>(this);
	}

	virtual ~ISingleton()
	{
		assert(sInstance != NULL);
		sInstance = NULL;
	}

public:
	static T * GetInstance()
	{
		if (sInstance == NULL) {
			sInstance = new T;
		}

		return sInstance;
	}

};

template <typename T>
T * ISingleton<T>::sInstance = NULL;
}

#endif /* !ISINGLETON_H_ */
