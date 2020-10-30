
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
	class TextureObject : public Object, public Following {
		//current sprite ready to bo rendered
		sf::Sprite currentSprite;
		void updateSprite();
		void init();
		bool isInit = false;
	public:
		TextureObject(const std::string& path,
			const std::string& filename,
			sf::Vector2f poss = { 0.f, 0.f },
			sf::Vector2f scale = { 1.f, 1.f },
			bool transparencyM = false) :
			Object(path, filename, transparencyM), Following(poss, poss, scale, scale) { init(); };
		TextureObject(const Object& x,
			sf::Vector2f poss = { 0.f, 0.f },
			sf::Vector2f scale = { 1.f, 1.f }) :
			Object(x),
			Following(poss, poss, scale, scale) { init(); };
		void draw(sf::RenderWindow& window) override;
		void update(sf::Time& currentTime) override;
		void SetRect(const sf::IntRect& rect) { currentSprite.setTextureRect(rect); }
		void SetColor(const sf::Color& color) { currentSprite.setColor(color); }
		const sf::Color& GetColor() const { return currentSprite.getColor(); }
		//returns activity of an object it is mainly related to the associated animations
		bool IsActive() const override;
	};
	void MEP::TextureObject::updateSprite()
	{
		if (!followingList.empty()) {
			for (auto& x : followingList)
				x->CheckVariables(m_poss, m_possFixed, m_scale, m_scaleFixed);
		}
		currentSprite.setPosition(m_possFixed);
		currentSprite.setScale(m_scaleFixed);
	}

	void MEP::TextureObject::init()
	{
		currentSprite.setTexture(*texture.front());
		currentSprite.setPosition(m_possFixed);
		currentSprite.setScale(m_scaleFixed);
		isInit = true;
	}

	void MEP::TextureObject::draw(sf::RenderWindow& window)
	{
		if (isInit) {
			window.draw(currentSprite);
		}
	}

	void MEP::TextureObject::update(sf::Time& currentTime)
	{
		updateSprite();
	}

	bool MEP::TextureObject::IsActive() const
	{
		return isFollowerActive();
	}

}