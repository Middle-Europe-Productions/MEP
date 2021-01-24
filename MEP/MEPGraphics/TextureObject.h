
////////////////////////////////////////////////////////////
//
//	TextureObject created with the use of SFML
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
#ifndef MEP_TEXTURE_OBJECT_H
#define MEP_TEXTURE_OBJECT_H

#include"AnimationObject.h"
namespace MEP {
	/**
	* Basic type of a MEP::Drawable element in which the creation of a sf::Sprite is done via a single texture.
	* \brief Basic MEP::Drawable element based on a single texture.
	*/
	class TextureObject : public Object, public Sprite {
		void updateSprite() override {
			if (!followingList.empty()) {
				for (auto& x : followingList)
					x->updateVariables(*this, currentSprite);
			}
			currentSprite.setPosition(m_posFixed);
			currentSprite.setScale(m_scaleFixed);
		}
		void init() {
			currentSprite.setTexture(*texture->front());
			currentSprite.setPosition(m_posFixed);
			currentSprite.setScale(m_scaleFixed);
			isInit = true;
		}
		bool isInit = false;
	public:
		/**
		* Constructor of a TextureObject
		* @param[in] x : MEP::Object
		* @param[in] pos : Pos of an MEP::TextureObject
		* @param[in] scale : Scale of an MEP::TextureObject
		*/
		TextureObject(const Object& x,
			sf::Vector2f pos = { 0.f, 0.f },
			sf::Vector2f scale = { 1.f, 1.f }) :
			Object(x),
			Sprite(pos, scale) 
		{ 
			init(); 
		};
		/**
		* On resize we want to update the position.
		*/
		void onResize() override {
			if(getDrawTag() & DrawTag::Resize_Scale)
				updateScale();
			if(getDrawTag() & DrawTag::Resize_Pos)
				updatePosition();
			if (getDrawTag() & DrawTag::Resize_Rect)
				updateRect();
		}
		/**
		* Override of a MEP::Drawable draw.
		*/
		bool draw(sf::RenderWindow& window) override {
			if (isInit) {
				window.draw(currentSprite);
			}
			return true;
		}
		/**
		* Override of a MEP::Drawable update.
		*/
		void update(sf::Time& currentTime) override {
			updateSprite();
		}
		/**
		* Outputs the color of a main sprite.
		* @return sf::Color
		*/
		void setColor(const sf::Color& color) { 
			currentSprite.setColor(color); 
		}
		/**
		* Sets the rotation of an object.
		* param[in] angle : angle of n rotation.
		*/
		void setRotation(const float angle) {
			currentSprite.setRotation(angle);
		}
		/**
		* Outputs the color of a main sprite.
		* @return sf::Color
		*/
		const sf::Color& getColor() const { 
			return currentSprite.getColor(); 
		}
		/**
		* Outputs activity of a texture. It is related to associated animations.
		* @return true - is active, false - otherwise.
		*/
		bool isActive() const override {
			return isFollowerActive();
		}
	};
}

#endif