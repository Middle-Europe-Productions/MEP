
////////////////////////////////////////////////////////////
//
//	TextObject.h created with the use of SFML
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

#include<string>
#include"Following.h"
#include"Drawable.h"

namespace MEP {
	/**
	* Type only very important feature here is the ability of displaying the text with a position tag.
	* The tricky part in here is that we are not able to tell the size of a Text before rendering it on a screen in order to solve the issue
	* MEP::Text has an ability of skiping the frame. But keep in mind that this is a very costly operation.
	* \brief A basic Text class.
	*/
	class Text : public Drawable, public Following {
	public:
		enum class PositionTag {
			Non,
			XMiddle,
			YMiddle,
			Middle
		};
	private:
		bool tagApplied = false;
		PositionTag m_tag;
		sf::Text text;
		std::string m_content;
	public:
		Text(const std::string& content, sf::Font& font, sf::Vector2f position = {0, 0}, unsigned int fontSize = 40): m_content(content) {
			text.setFont(font);
			text.setString(content); 
			text.setCharacterSize(fontSize);
			m_tag = PositionTag::Middle;
			// set the color
			text.setFillColor(sf::Color::Black);
			// set the text style
			text.setStyle(sf::Text::Bold);
			text.setPosition(position.x, position.y);
			std::cout << text.getLocalBounds().height << " " << text.getLocalBounds().width << std::endl;
		}
		bool draw(sf::RenderWindow& window) override {
			window.draw(text); 
			if (!tagApplied and m_tag != PositionTag::Non) {
				if (m_tag == PositionTag::Middle) {
					text.setPosition(text.getPosition().x - text.getLocalBounds().width / 2, 
						text.getPosition().y - 24);
					tagApplied = true;
					return false;
				}
			}
			return true;
		}
		const std::string& getText() const { return m_content; }
	};
}