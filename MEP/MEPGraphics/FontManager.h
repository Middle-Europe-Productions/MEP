////////////////////////////////////////////////////////////
//
//	FontManager.h created with the use of SFML
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
#ifndef MEP_FONT_MANAGER_H
#define MEP_FONT_MANAGER_H
#include<list>
#include<SFML/Graphics/Font.hpp>
#include"Group.h"
/**
* A class manages the fonts.
* \brief A main sf::Font container.
*/
namespace MEP{
	class FontManager {
	protected:
		class Font {
			U_int32 m_ID;
			std::string m_name;
			sf::Font m_font;
		public:
			/**
			* Constructor of a Font
			* @param[in] ID : Unique ID of an object.
			* @param[in] name : Name of an objects. (Last part of the directory ex. Font.ttf).
			* @param[in] path : Path of the font. (End it with \).
			*/
			Font(U_int32 ID, const std::string& name, const std::string& path): m_ID(ID), m_name(name) {
				if (!m_font.loadFromFile(path+name))
					throw ResourceException("path", "Could not load the font!", ResourceException::ExceptionType::CouldntLoadFont);
			}
			/**
			* Outputs the ID.
			*/
			U_int32 getID() const { return m_ID; }
			/**
			* Outputs the name.
			*/
			const std::string& getName() const { return m_name; }
			/**
			* Outputs the sf::Font.
			*/
			sf::Font& getFont() { return m_font; }
		};
		//Cointainer
		std::list<Group<Font>> fonts;
	public:
		FontManager() = default;
	};
}
#endif