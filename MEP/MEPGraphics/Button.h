
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
#ifndef MEP_BUTTON_H
#define MEP_BUTTON_H

#include"AnimationObject.h"
#include"NonCopyable.h"
namespace MEP {
	/**
	* \brief MEP::Button provides a basic implementation of an object with the ability of display it on a screen.
	*/
	class Button : public AnimationObject {
	public:
		/**
		* @enum MEP::Button::ButtonStatus
		*/
		enum class ButtonStatus {
			/** Mouse is away.*/
			Base = (int)0,
			/** Mouse is pointing.*/
			Active = (int)1,
			/** Mouse is pointing and left mouse button is pressed.*/
			Pressed = (int)2
		};
	private:
		unsigned int m_base;
		unsigned int m_active;
		unsigned int m_pressed;
		ButtonStatus m_status = ButtonStatus::Base;
	public:
		/**
		* Constructor of a Button
		* @param[in] x : MEP::Object
		* @param[in] active_breakpoint : State in which button is fully activeated (mouse is pointing).
		* @param[in] pos : position of a button.
		* @param[in] scale : scale of a button
		*/
		Button(const Object& x,
			unsigned int active_breakpoint,
			sf::Vector2f pos = { 0, 0 },
			sf::Vector2f scale = { 1, 1 });
		/**
		* Constructor of a Button
		* @param[in] x : frame rate of an animation.
		* @param[in] x : MEP::Object
		* @param[in] active_breakpoint : State in which button is fully activeated (mouse is pointing).
		* @param[in] pos : position of a button.
		* @param[in] scale : scale of a button
		*/
		Button(const float frameRate,
			const Object& x,
			unsigned int active_breakpoint,
			sf::Vector2f pos = { 0, 0 },
			sf::Vector2f scale = { 1, 1 });
		/**
		* Constructor of a Button
		* @param[in] x : frame rate of an animation.
		* @param[in] x : MEP::Object
		* @param[in] base_breakpoint : Base State when mouse is away.
		* @param[in] active_breakpoint : Activeted state when mouse is pointing.
		* @param[in] pressed_breakpoint : Pressed state when mouse is poining and left button is pressed.
		* @param[in] pos : position of a button.
		* @param[in] scale : scale of a button
		*/
		Button(const float frameRate,
			const Object& x,
			unsigned int base_breakpoint,
			unsigned int active_breakpoint,
			unsigned int pressed_breakpoint,
			sf::Vector2f pos = { 0, 0 },
			sf::Vector2f scale = { 1, 1 });
		void update(sf::Time& currentTime) override;
		bool handleEvent(sf::Event& event, sf::Vector2i& pos);
		/**
		* Checks if a given position is Transparent.
		* MEP::Objects of a button needs to have transparency initialized.
		* @return true - position is transparent, false - there is a pixel witout alpha channel > 200
		*/
		bool isTansparent(unsigned int x, unsigned int y) override;
		/**
		* Changes the status of a button.
		* @param[in] status : A MEP::Button::ButtonStatus object
		*/
		void changeStatus(const ButtonStatus& status) { m_status = status; }
		/**
		* Outputs current status of a button.
		* @return Current status
		*/
		const ButtonStatus& getStatus() const { return m_status; }
	};
	inline MEP::Button::Button(const Object& x, unsigned int active_breakpoint, sf::Vector2f pos, sf::Vector2f scale) :
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

	inline MEP::Button::Button(const float frameRate, const Object& x, unsigned int active_breakpoint, sf::Vector2f pos, sf::Vector2f scale) :
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

	inline MEP::Button::Button(const float frameRate, const Object& x, unsigned int /*base_breakpoint*/, unsigned int active_breakpoint, unsigned int /*pressed_breakpoint*/, sf::Vector2f pos, sf::Vector2f scale) :
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

	inline void MEP::Button::update(sf::Time& currentTime)
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
		if (!followingList.empty()) {
			updateSprite();
		}
	}

	inline bool MEP::Button::handleEvent(sf::Event& event, sf::Vector2i& pos)
	{
		bool isTran = isTansparent(pos.x, pos.y);
		if (!followingList.empty()) {
			if (!isTran)
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
					changeStatus(ButtonStatus::Pressed);
				else
					changeStatus(ButtonStatus::Active);
			else
				changeStatus(ButtonStatus::Base);
		}
		if (event.type == sf::Event::MouseMoved) {
			if (!isTran)
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
					changeStatus(ButtonStatus::Pressed);
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

	inline bool MEP::Button::isTansparent(unsigned int x, unsigned int y)
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
}

#endif
