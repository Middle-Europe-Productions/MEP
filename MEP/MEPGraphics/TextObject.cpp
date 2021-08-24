////////////////////////////////////////////////////////////
//
//	TextObject.cpp created with the use of SFML
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
#include<MEPGraphics/TextObject.h>

namespace MEP
{
	Text::Text(const std::string& content,
		sf::Font& font,
		unsigned int fontSize,
		sf::Vector2f position,
		PositionTag tag) :
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

	Text::Text(const std::string& content,
		sf::Font& font,
		const Following& follow,
		unsigned int fontSize,
		PositionTag tag) :
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

	void Text::onResize() {
		if (getDrawTag() & DrawTag::Resize_Scale)
			updateScale();
		if (getDrawTag() & DrawTag::Resize_Pos)
			updatePosition();
	}

	void Text::update(sf::Time&) {
		followingListv2._execute([&](auto& x) {
			x.get()->updateVariables(*this);
			});
		text.setPosition(getPosition());
		text.setScale(getScale());
		text.setFillColor(getColor());
	}
	void Text::changePositionTag(const PositionTag& x) {
		if (x != m_tag) {
			m_tag = x;
			tagApplied = false;
		}
	}

	bool Text::draw(sf::RenderWindow& window) {
		window.draw(text);
		if (!tagApplied and m_tag != PositionTag::Non) {
			if (m_tag == PositionTag::Middle) {
				text.setOrigin({ text.getLocalBounds().width / 2,
					 (float)text.getCharacterSize() / 2 + ((float)text.getCharacterSize() - text.getLocalBounds().height) / 2 });
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

	const std::string& Text::getString() const {
		return m_content;
	}

	sf::Text& Text::getText() {
		return text;
	}

	void Text::setText(const std::string& in) {
		if (in != m_content) {
			m_content = in;
			text.setString(in);
			tagApplied = false;
		}

	}

	void Text::setColor(const sf::Color& in) {
		m_color = in;
	}

	void Text::debugOutput(std::ostream& out) const {
		out << "MEP::Text, content: " << m_content << std::endl;
		followingDebug(out, "  ");
		out << "   \\";
		drawTagDebug(out);
	}

	std::ostream& operator<<(std::ostream& out, const Text& x) {
		x.debugOutput(out);
		return out;
	}
}