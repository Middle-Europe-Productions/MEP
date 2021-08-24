////////////////////////////////////////////////////////////
//
//	TextureObject.cpp created with the use of SFML
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
#include<MEPGraphics/TextureObject.h>

namespace MEP
{
	void TextureObject::updateSprite() {
		if (followingListv2._size() != 0)
			followingListv2._execute([&](auto& x) {
			x.get()->updateVariables(*this, currentSprite);
				});
		currentSprite.setPosition(m_posFixed);
		currentSprite.setScale(m_scaleFixed);
	}
	void TextureObject::init() {
		currentSprite.setTexture(*texture->front());
		currentSprite.setPosition(m_posFixed);
		currentSprite.setScale(m_scaleFixed);
		isInit = true;
	}
	TextureObject::TextureObject(const Object& x,
		sf::Vector2f pos,
		sf::Vector2f scale) :
		Object(x),
		Sprite(pos, scale)
	{
		init();
	};

	void TextureObject::onResize() {
		if (getDrawTag() & DrawTag::Resize_Scale)
			updateScale();
		if (getDrawTag() & DrawTag::Resize_Pos)
			updatePosition();
		if (getDrawTag() & DrawTag::Resize_Rect)
			updateRect();
	}

	bool TextureObject::draw(sf::RenderWindow& window) {
		if (isInit) {
			window.draw(currentSprite);
		}
		return true;
	}

	void TextureObject::update(sf::Time&) {
		updateSprite();
	}

	void TextureObject::setColor(const sf::Color& color) {
		currentSprite.setColor(color);
	}

	void TextureObject::setRotation(const float angle) {
		currentSprite.setRotation(angle);
	}

	const sf::Color& TextureObject::getColor() const {
		return currentSprite.getColor();
	}

	bool TextureObject::isActive() const {
		return isFollowerActive();
	}

	void TextureObject::debugOutput(std::ostream& out) const {
		out << "MEP::TextureObject, Following:" << std::endl;
		followingDebug(out, "  ");
		out << "   \\MEP::Object, ID: " << getID() << ", name : " << getName() << std::endl;
		out << "     \\";
		drawTagDebug(out);
	}

	std::ostream& operator<<(std::ostream& out, const TextureObject& x) {
		x.debugOutput(out);
		return out;
	}
}