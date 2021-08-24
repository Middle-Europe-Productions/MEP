////////////////////////////////////////////////////////////
//
//	Font.cpp created with the use of SFML
//	MEP - Middle Europe Productions
//  Work in progress. 
//
//	Licensed under the Apache License, Version 2.0 (the "License");
//	you may not use this file except in compliance with the License.
//	You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
//	Unless required by applicable law or agreed to in writing, software
//	distributed under the License is distributed on an "AS IS" BASIS,
//	WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//	See the License for the specific language governing permissions and
//	limitations under the License.
//
//
//	Created by Piotr Skibiñski
//	Copyright © Middle Europe Productions. All rights reserved.
//
////////////////////////////////////////////////////////////
#include<MEPGraphics/Font.h>

namespace MEP
{
	Font::Font(U_int32 ID, const std::string& name, const std::string& path) : m_ID(ID), m_name(name)
	{
		if (!m_font.loadFromFile(path + name))
			throw ResourceException("path", "Could not load the font!", ResourceException::ExceptionType::CouldntLoadFont);
	}

	U_int32 Font::getID() const
	{
		return m_ID;
	}

	const std::string& Font::getName() const
	{
		return m_name;
	}

	sf::Font& Font::getFont()
	{
		return m_font;
	}
}