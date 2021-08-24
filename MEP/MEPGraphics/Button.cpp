////////////////////////////////////////////////////////////
//
//	Button.cpp created with the use of SFML
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
#include<MEPGraphics/Button.h>

namespace MEP
{
	Button::Button(const Object& x, unsigned int active_breakpoint, sf::Vector2f pos, sf::Vector2f scale) :
		AnimationObject(1, x, pos, scale),
		m_base(0)
	{
		if (x.getNufTextures() < 3)
			throw "Textures too small!";
		if (active_breakpoint < x.getNufTextures())
			m_active = active_breakpoint;
		else
			throw "Wrong middle paremeter!";
		if (active_breakpoint < x.getNufTextures() - 1)
			m_pressed = x.getNufTextures() - 1;
		else
			throw "Wrong end parameter!";
	}

	Button::Button(const float frameRate, const Object& x, unsigned int active_breakpoint, sf::Vector2f pos, sf::Vector2f scale) :
		AnimationObject(frameRate, x, pos, scale),
		m_base(0)
	{
		if (x.getNufTextures() < 3)
			throw "Textures too small!";
		if (active_breakpoint < x.getNufTextures())
			m_active = active_breakpoint;
		else
			throw "Wrong middle paremeter!";
		if (active_breakpoint < x.getNufTextures() - 1)
			m_pressed = x.getNufTextures() - 1;
		else
			throw "Wrong end parameter!";
	}

	void Button::update(sf::Time& currentTime)
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
					updateSprite(**currentFrame);
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
					updateSprite(**currentFrame);
				}
				else if (m_status == ButtonStatus::Pressed and index_currentFrame != m_pressed) {
					index_currentFrame++;
					currentFrame++;
					updateSprite(**currentFrame);
				}
			}
		}
		if (!followingListv2._empty()) {
			updateSprite();
		}
	}

	bool Button::handleEvent(sf::Event& event, sf::Vector2i& pos)
	{
		if (m_block)
			return false;
		bool isTran = isTansparent(pos.x, pos.y);
		if (event.type == sf::Event::MouseMoved or !followingListv2._empty()) {
			if (!isTran)
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
					changeStatus(ButtonStatus::Pressed);
				else
					if (event.type == sf::Event::MouseButtonReleased) {
						changeStatus(ButtonStatus::Active);
						return true;
					}
					else
						changeStatus(ButtonStatus::Active);
			else
				changeStatus(ButtonStatus::Base);
		}
		else if (event.type == sf::Event::MouseButtonPressed) {
			if (event.mouseButton.button == sf::Mouse::Left) {
				if (!isTran)
					changeStatus(ButtonStatus::Pressed);
			}
		}
		else if (event.type == sf::Event::MouseButtonReleased) {
			if (event.mouseButton.button == sf::Mouse::Left) {
				if (!isTran) {
					changeStatus(ButtonStatus::Active);
					return true;
				}
			}
		}
		return false;
	}

	bool Button::isTansparent(unsigned int x, unsigned int y)
	{
		int fixed_x = (x - m_posFixed.x) / m_scaleFixed.x;
		int fixed_y = (y - m_posFixed.y) / m_scaleFixed.y;
		if ((fixed_x >= 0 and fixed_x < (int)m_size.x) and (fixed_y >= 0 and fixed_y < (int)m_size.y)) {
			if (transparency)
				return table[fixed_x][fixed_y];
			else
				return false;

		}
		return true;
	}
	bool Button::mousePress(sf::Vector2i& pos) {
		if (!m_block and !isTansparent(pos.x, pos.y)) {
			changeStatus(ButtonStatus::Pressed);
			return true;
		}
		else {
			return false;
		}
	}
	bool Button::mouseRelease(sf::Vector2i& pos) {
		if (!m_block and !isTansparent(pos.x, pos.y)) {
			changeStatus(ButtonStatus::Active);
			return true;
		}
		else {
			return false;
		}
	}
	bool Button::mouseActivity(const sf::Vector2i& pos)
	{
		if (m_block)
			return false;
		if (!isTansparent(pos.x, pos.y)) {
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				changeStatus(ButtonStatus::Pressed);
				return true;
			}
			else {
				changeStatus(ButtonStatus::Active);
				return false;
			}
		}
		else {
			changeStatus(ButtonStatus::Base);
		}
		return false;
	}

	void Button::forceRelease()
	{
		m_status = ButtonStatus::Base;
	}

	bool Button::forceReleased()
	{
		if (isRunning)
			return false;
		m_status = ButtonStatus::Base;
		direction = Direction::Backwards;
		currentFrame = texture->begin();
		index_currentFrame = 0;
		updateSprite(**currentFrame);
		return true;
	}

	void Button::forcePress()
	{
		m_status = ButtonStatus::Pressed;
	}

	bool Button::forcePressed()
	{
		if (isRunning)
			return false;
		m_status = ButtonStatus::Pressed;
		direction = Direction::Forward;
		currentFrame = --texture->end();
		index_currentFrame = texture->size() - 1;
		updateSprite(**currentFrame);
		return true;
	}

	void Button::block()
	{
		m_block = true;
	}

	void Button::release()
	{
		m_block = false;
	}

	bool Button::isBlocked() const
	{
		return m_block;
	}
}