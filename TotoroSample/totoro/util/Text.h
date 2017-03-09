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

#ifndef TEXT_H_
#define TEXT_H_

#include "..\ap\Defs.h"
#include <fstream>

namespace totoro
{
/**
 * Text class file
 * ��ȡ�ļ���
 *
 * @author �λ� <trotri@yeah.net>
 * @version $Id: Text.h 1 2015-04-06 19:22:06Z huan.song $
 * @since 1.0
 */
class Text
{
public:
	static CONST TCHAR * TAG;
	static CONST TCHAR * DEFAULT_TAG_NAME;
	static CONST String TAG_BEGIN;
	static CONST String TAG_END;

public:
	Text();
	virtual ~Text();

public:
	/**
     * ���ļ��ж�ȡ�������
	 * <pre>
	 * �����ļ���ʽ��
	 * Tag image
	 * name = warcraft
	 * path = raw\\img\\warcraft.png
	 * hotspot_x = 0
	 * hotspot_y = 0
	 * region_left = -1
	 * region_top = -1
	 * region_right = -1
	 * region_bottom = -1
	 * scale_x = 1.0
	 * scale_y = 1.0
	 * angle = 0
	 * pos_x = 100.50
	 * pos_y = 100.50
	 * z_index = 1
	 * is_transform = 1
	 * End Tag //!image
	 *
	 * Tag image
	 * name = enemy
	 * path = raw\\img\\enemy.png
	 * hotspot_x = 0
	 * hotspot_y = 0
	 * region_left = -1
	 * region_top = -1
	 * region_right = -1
	 * region_bottom = -1
	 * scale_x = 1.0
	 * scale_y = 1.0
	 * angle = 0
	 * pos_x = 200.50
	 * pos_y = 200.50
	 * z_index = 1
	 * is_transform = 1
	 * End Tag //!image
	 * </pre>
	 * @param String fileName
     * @return map<String, vector<map<String, String>>>
     */
	static std::map<String, std::vector<std::map<String, String>>> GetCfgs(String fileName);
	static BOOL IsBeginTag(String line, String &tagName);
	static BOOL IsEndTag(String line);

	/**
     * ���ļ��ж�ȡһ������
	 * <pre>
	 * �����ļ���ʽ��
	 * name = warcraft
	 * path = raw\\img\\warcraft.png
	 * hotspot_x = 0
	 * hotspot_y = 0
	 * region_left = -1
	 * region_top = -1
	 * region_right = -1
	 * region_bottom = -1
	 * scale_x = 1.0
	 * scale_y = 1.0
	 * angle = 0
	 * pos_x = 100.50
	 * pos_y = 100.50
	 * z_index = 1
	 * is_transform = 1
	 * </pre>
	 * @param String fileName
     * @return map<String, String>
     */
	static std::map<String, String> GetCfg(String fileName);

	/**
     * ��ȡ�ļ������е�ԭʼ�ַ���
	 * @param String fileName
	 * @param list<String> * data
     * @return BOOL
     */
	static BOOL GetStrings(String fileName, std::list<String> * data);
};

}

#endif /* !TEXT_H_ */
