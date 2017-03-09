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

#ifndef AUDIO_H_
#define AUDIO_H_

#include "..\ap\Defs.h"
#include "..\ap\Window.h"
#include <bass.h>

/**
 * 附加依赖项：bass.lib
 * 包含目录：...\bass24\c
 * 库目录：...\bass24\c
 */

#pragma comment(lib, "bass.lib")

namespace totoro
{
/**
 * Audio class file
 * 音效处理类，基于bass24库
 *
 * @author 宋欢 <trotri@yeah.net>
 * @version $Id: Audio.h 1 2015-04-29 16:56:06Z huan.song $
 * @since 1.0
 */
class Audio : public ISingleton<Audio>
{
private:
	BOOL mDisabled;

public:
	Audio();
	virtual ~Audio();

public:
	HSTREAM StreamCreate(String fileName, DWORD flags);
	BOOL StreamFree(HSTREAM hStream);
	BOOL Play(HSTREAM hStream, BOOL restart);
	BOOL Pause(HSTREAM hStream);
	BOOL IsDisabled() CONST;
	VOID SetDisabled(BOOL disabled);
};

}

#endif /* !AUDIO_H_ */
