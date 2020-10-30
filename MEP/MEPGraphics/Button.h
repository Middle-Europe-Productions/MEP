
////////////////////////////////////////////////////////////
//
//	Button.h created with the use of SFML
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
	class Button : public AnimationObject {
	public:
		//status of a button
		enum class ButtonStatus {
			Base = (int)0,
			Active = (int)1,
			Pressed = (int)2
		};
	private:
		unsigned int m_base;
		unsigned int m_active;
		unsigned int m_pressed;
		ButtonStatus m_status = ButtonStatus::Base;
	public:
		Button(const Object& x,
			unsigned int active_breakpoint,
			sf::Vector2f poss = { 0, 0 },
			sf::Vector2f scale = { 1, 1 });
		Button(const float frameRate,
			const Object& x,
			unsigned int active_breakpoint,
			sf::Vector2f poss = { 0, 0 },
			sf::Vector2f scale = { 1, 1 });
		Button(const float frameRate,
			const Object& x,
			unsigned int base_breakpoint,
			unsigned int active_breakpoint,
			unsigned int pressed_breakpoint,
			sf::Vector2f poss = { 0, 0 },
			sf::Vector2f scale = { 1, 1 });
		//update function
		void update(sf::Time& currentTime) override;
		//handle events by changing button status and returns true if button is pressed and has beed released
		bool handleEvent(sf::Event& event, sf::Vector2i& pos);
		//checks the transparency of an object
		bool isTansparent(unsigned int x, unsigned int y) override;
		//changes the status of the button
		void ChangeStatus(const ButtonStatus& status) { m_status = status; }
		const ButtonStatus& GetStatus() const { return  m_status; }
	};
	MEP::Button::Button(const Object& x, unsigned int active_breakpoint, sf::Vector2f poss, sf::Vector2f scale) :
		AnimationObject(1, x, poss, scale),
		m_base(0)
	{
		if (x.GetNufTextures() < 3)
			throw "Textures too small!";
		if (active_breakpoint < x.GetNufTextures())
			m_active = active_breakpoint;
		else
			throw "Wrong middle paremeter!";
		if (active_breakpoint < x.GetNufTextures() - 1)
			m_pressed = x.GetNufTextures() - 1;
		else
			throw "Wrong end parameter!";
	}

	MEP::Button::Button(const float frameRate, const Object& x, unsigned int active_breakpoint, sf::Vector2f poss, sf::Vector2f scale) :
		AnimationObject(frameRate, x, poss, scale),
		m_base(0)
	{
		if (x.GetNufTextures() < 3)
			throw "Textures too small!";
		if (active_breakpoint < x.GetNufTextures())
			m_active = active_breakpoint;
		else
			throw "Wrong middle paremeter!";
		if (active_breakpoint < x.GetNufTextures() - 1)
			m_pressed = x.GetNufTextures() - 1;
		else
			throw "Wrong end parameter!";
	}

	MEP::Button::Button(const float frameRate, const Object& x, unsigned int base_breakpoint, unsigned int active_breakpoint, unsigned int pressed_breakpoint, sf::Vector2f poss, sf::Vector2f scale) :
		AnimationObject(frameRate, x, poss, scale),
		m_base(0)
	{
		if (x.GetNufTextures() < 3)
			throw "Textures too small!";
		if (active_breakpoint < x.GetNufTextures())
			m_active = active_breakpoint;
		else
			throw "Wrong middle paremeter!";
		if (active_breakpoint < x.GetNufTextures() - 1)
			m_pressed = x.GetNufTextures() - 1;
		else
			throw "Wrong end parameter!";
	}

	void MEP::Button::update(sf::Time& currentTime)
	{
		if (isInit == AnimationInit::ObjectAnimation) {
			if (currentTime - updateTime >= toWait) {
				if (m_status == ButtonStatus::Active and index_currentFrame != m_active) {
					if (index_currentFrame > m_active) {
						while (index_currentFrame != m_active) {
							index_currentFrame--;
							currentFrame--;
						}
					}
					else {
						index_currentFrame++;
						currentFrame++;
					}
					updateSprite();
				}
				else if (m_status == ButtonStatus::Base and index_currentFrame != m_base) {
					if (index_currentFrame > m_active) {
						while (index_currentFrame != m_base) {
							index_currentFrame--;
							currentFrame--;
						}
					}
					else {
						index_currentFrame--;
						currentFrame--;
					}
					updateSprite();
				}
				else if (m_status == ButtonStatus::Pressed and index_currentFrame != m_pressed) {
					index_currentFrame++;
					currentFrame++;
					updateSprite();
				}
			}
		}
		if (!followingList.empty()) {
			updateSprite();
		}
	}

	bool MEP::Button::handleEvent(sf::Event& event, sf::Vector2i& pos)
	{
		bool isTran = isTansparent(pos.x, pos.y);
		if (!followingList.empty()) {
			if (!isTran)
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
					ChangeStatus(ButtonStatus::Pressed);
				else
					ChangeStatus(ButtonStatus::Active);
			else
				ChangeStatus(ButtonStatus::Base);
		}
		if (event.type == sf::Event::MouseMoved) {
			if (!isTran)
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
					ChangeStatus(ButtonStatus::Pressed);
				else
					ChangeStatus(ButtonStatus::Active);
			else
				ChangeStatus(ButtonStatus::Base);
		}
		else if (event.type == sf::Event::MouseButtonPressed) {
			if (event.key.code == sf::Mouse::Left) {
				if (!isTran)
					ChangeStatus(ButtonStatus::Pressed);
			}
		}
		else if (event.type == sf::Event::MouseButtonReleased) {
			if (event.key.code == sf::Mouse::Left) {
				if (!isTran) {
					ChangeStatus(ButtonStatus::Active);
					return true;
				}
			}
		}
		return false;
	}

	bool MEP::Button::isTansparent(unsigned int x, unsigned int y)
	{
		int fixed_x = (x - m_possFixed.x) / m_scaleFixed.x;
		int fixed_y = (y - m_possFixed.y) / m_scaleFixed.y;
		if ((fixed_x >= 0 and fixed_x < m_size.x) and (fixed_y >= 0 and fixed_y < m_size.y)) {
			if (transparency)
				return table[fixed_x][fixed_y];
			else
				return false;

		}
		return true;
	}
}