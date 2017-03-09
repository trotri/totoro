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

#ifndef AUDIO_REGISTRY_H_
#define AUDIO_REGISTRY_H_

#include "Audio.h"

namespace totoro
{
/**
 * AudioRegistry class file
 * 音效寄存类，基于bass24库
 *
 * @author 宋欢 <trotri@yeah.net>
 * @version $Id: AudioRegistry.h 1 2015-04-29 16:56:06Z huan.song $
 * @since 1.0
 */
class AudioRegistry
{
public:
	static CONST TCHAR * TAG;

private:
	static std::map<String, HSTREAM> sLoops;
	static std::map<String, HSTREAM> sOnces;

protected:
	AudioRegistry();
	virtual ~AudioRegistry();

public:
	static BOOL PlayLoop(String fileName);
	static BOOL PlayLoop(String fileName, BOOL restart);
	static BOOL PlayOnce(String fileName);
	static BOOL PlayOnce(String fileName, BOOL restart);
	static BOOL PauseLoop(String fileName);
	static BOOL PauseOnce(String fileName);
	static BOOL Process(String fileName, BOOL isLoop, BOOL isPause, BOOL restart);
	static BOOL LoadLoop(String fileName);
	static BOOL LoadOnce(String fileName);
	static BOOL LoadAudio(String fileName, BOOL isLoop);
	static VOID ClearLoop();
	static VOID ClearOnce();
	static VOID ClearAll();
	static BOOL IsDisabled();
	static VOID SetDisabled(BOOL disabled);
};

}

#endif /* !AUDIO_REGISTRY_H_ */
