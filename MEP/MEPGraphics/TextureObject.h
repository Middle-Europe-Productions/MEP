
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
#pragma once
#include"AnimationObject.h"
namespace MEP {
	/**
	* Basic type of a MEP::Drawable element in which the creation of a sf::Sprite is done via a single texture.
	* \brief Basic MEP::Drawable element based on a single texture. 
	*/
	class TextureObject : public Object, public Following {
		//current sprite ready to bo rendered
		sf::Sprite currentSprite;
		void updateSprite() {
			if (!followingList.empty()) {
				for (auto& x : followingList)
					x->CheckVariables(m_pos, m_posFixed, m_scale, m_scaleFixed);
			}
			currentSprite.setPosition(m_posFixed);
			currentSprite.setScale(m_scaleFixed);
		}
		void init() {
			currentSprite.setTexture(*texture.front());
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
			Following(pos, pos, scale, scale) 
		{ 
			init(); 
		};
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
		* Sets the main sprite Rect
		*/
		void SetRect(const sf::IntRect& rect) { 
			currentSprite.setTextureRect(rect); 
		}
		/**
		* Outputs the color of a main sprite.
		* @return sf::Color
		*/
		void SetColor(const sf::Color& color) { 
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
		const sf::Color& GetColor() const { 
			return currentSprite.getColor(); 
		}
		/**
		* Outputs activity of a texture. It is related to associated animations.
		* @return true - is active, false - otherwise.
		*/
		bool IsActive() const override {
			return isFollowerActive();
		}
	};
}