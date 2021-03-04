
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
#ifndef MEP_TEXT_H
#define MEP_TEXT_H

#include<string>
#include<MEPGraphics/Following.h>
#include<MEPGraphics/Drawable.h>

namespace MEP {
	/**
	* Type only very important feature here is the ability of displaying the text with a position tag.
	* The tricky part in here is that we are not able to tell the size of a Text before rendering it on a screen in order to solve the issue
	* MEP::Text has an ability of skiping the frame. But keep in mind that this is a very costly operation.
	* \brief A basic Text class.
	*/
	class Text : public Drawable, public Following {
	public:
		/**
		* @enum MEP::Text::PositionTag
		* Defines an additional tag to the position of a text.
		*/
		enum class PositionTag {
			/** Position.x and Position.y are the top left corner of the text.*/
			Non,
			/** Position.y is not changed while Position.x is in the middle of the text.*/
			XMiddle,
			/** Position.x is not changed while Position.y is in the middle of the text.*/
			YMiddle,
			/** Both Postition.x and Position.y are exactly in the middle of the text.*/
			Middle
		};
	private:
		/**
		* This is a m_tag guard.
		* When false it basically means that position tah has not been applied.
		*/
		bool tagApplied = false;
		/**
		* Position tag. It infuances the origin of the Text.
		*/
		PositionTag m_tag = PositionTag::Non;
		/**
		* SFML Text object. 
		*/
		sf::Text text;
		/**
		* Content of a text.
		*/
		std::string m_content;
	public:
		/**
		* Constructor of a text.
		* @param[in] context : This goes on your screen.
		* @param[in] font : Font of a Text.
		* @param[in] fontSize : Size of the font.
		* @param[in] position : Position on the screen.
		* @param[in] tag : MEP::TextOboject::PositionTag
		*/
		Text(const std::string& content,
			sf::Font& font,
			unsigned int fontSize = 40,
			sf::Vector2f position = { 0, 0 },
			PositionTag tag = PositionTag::Non) :
			Following(position, position),
			m_tag(tag),
			m_content(content)
		{
			setPosition(position);
			text.setFont(font);
			text.setString(content); 
			text.setCharacterSize(fontSize);
			//By default its black. We are using it here.
			text.setFillColor(getColor());
		}
		/**
		* Constructor of a text.
		* @param[in] context : This goes on your screen.
		* @param[in] font : Font of a Text.
		* @param[in] fontSize : Size of the font.
		* @param[in] position : Position on the screen.
		* @param[in] tag : MEP::TextOboject::PositionTag
		*/
		Text(const std::string& content,
			sf::Font& font,
			const Following& follow,
			unsigned int fontSize = 40,
			PositionTag tag = PositionTag::Non) :
			Following(follow),
			m_tag(tag),
			m_content(content)
		{
			setPosition(m_posFixed);
			text.setFont(font);
			text.setString(content);
			text.setCharacterSize(fontSize);
			//By default its black. We are using it here.
			text.setFillColor(getColor());
		}
		Text& operator<<(const Sprite& x) {
			(Following&)(*this) << x;
			return *this;
		}
		Text& operator<<(const Text& x) {
			if (this != &x) {
				(Following&)(*this) << x;
			}
			return *this;
		}
		/**
		* On resize we want to update the position.
		*/
		void onResize() override {
			if (getDrawTag() & DrawTag::Resize_Scale)
				updateScale();
			if (getDrawTag() & DrawTag::Resize_Pos)
				updatePosition();
		}
		/**
		* Override of a MEP::Drawable update.
		*/
		void update(sf::Time&) override {
			for (auto& x : followingList)
				x->updateVariables(*this);
			text.setPosition(getPosition());
			text.setScale(getScale());
			text.setFillColor(getColor());
		}
		void changePositionTag(const PositionTag& x) {
			if (x != m_tag) {
				m_tag = x;
				tagApplied = false;
			}
		}
		/**
		*	The implementation of this draw method is slightly different than the other ones.
		*	It does some update job. The reason for that is rather straightforward, in order to get text bound we do need to render it.
		*	MEP::Text provides operation based on that that is why I needed to implement some user friendly solution.
		*	I would highly recommend you to avoid using the PositionTag beacause in order to use it you need to 'loose first frame of the execution'.
		*	why? Text is being rendered than we calculate the bound and after all of that we do need to request frame rebuild
		*	to avoid text without MEP::TextObject::PositionTag applied.
		*	@param[in] window : Classic sf::RenderWindow
		*/
		bool draw(sf::RenderWindow& window) override {
			window.draw(text); 
			if (!tagApplied and m_tag != PositionTag::Non) {
				if (m_tag == PositionTag::Middle) {
					text.setOrigin({ text.getLocalBounds().width / 2,
						 (float)text.getCharacterSize()/2 + ((float)text.getCharacterSize() - text.getLocalBounds().height)/2});
					text.setPosition(getPosition());
					tagApplied = true;
					return false;
				}
				else if (m_tag == PositionTag::XMiddle) {
					text.setOrigin({ text.getLocalBounds().width / 2,
						 0 });
					text.setPosition(getPosition());
					tagApplied = true;
					return false;
				}
				else if (m_tag == PositionTag::YMiddle) {
					text.setOrigin({ 0,
						 (float)text.getCharacterSize() / 2 + ((float)text.getCharacterSize() - text.getLocalBounds().height) / 2 });
					text.setPosition(getPosition());
					tagApplied = true;
					return false;
				}
			}
			return true;
		}
		/**
		*	Outputs the content of a string of the text
		*	@return : Text as std::string
		*/
		const std::string& getString() const { 
			return m_content; 
		}
		/**
		*	Outputs the content of a sf::Text
		*	@return : sf::Text
		*/
		sf::Text& getText() {
			return text;
		}
		/**
		*	Changes the main string.
		*	@param[in] in : New string.
		*/
		void setText(const std::string& in) {
			if (in != m_content) {
				m_content = in;
				text.setString(in);
				tagApplied = false;
			}
			
		}
		/**
		*	Changes the main string.
		*	@param[in] in : New string.
		*/
		void setColor(const sf::Color& in) {
			m_color = in;
		}
	};
}

#endif
