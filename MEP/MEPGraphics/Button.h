
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

#include<MEPGraphics/AnimationObject.h>

namespace MEP {
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
	/**
	* \brief MEP::Button provides a basic implementation of an object with the ability of display it on a screen.
	*/
	class Button : public AnimationObject {
	private:
		bool m_block = false;

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
		void update(sf::Time& currentTime) override;
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
		/**
		* Automatically handles the events.	
		* This method is not recommended because of the complexity.	
		* (When executed automatically checks all of the events. Mouse activity, movement etc.)
		*/
		bool handleEvent(sf::Event& event, sf::Vector2i& pos);
		/**
		* Delivers an information that there is a possible press event tied with the button.
		* True - if button is pressed, False - otherwise.
		*/
		bool mousePress(sf::Vector2i& pos);
		/**
		* Delivers an information that there is a possible release event tied with the button.
		* True - if button is released, False - otherwise.
		*/
		bool mouseRelease(sf::Vector2i& pos);
		/**
		* Inform the button that the statue of .
		* @return: True - there was an activity on a Button, False - otherwise.
		*/
		bool mouseActivity(const sf::Vector2i& pos);
		/**
		* Forces to releases the button.
		*/
		void forceRelease();
		/**
		* Forces the button to be released. Ignores the animation.
		* @return: True - Button was released, False - animation is active.
		*/
		bool forceReleased();
		/**
		* Forces to press the button. Not ignoring the animation.
		*/
		void forcePress();
		/**
		* Forces the button to be pressed. Ignores the animation.
		* @return: True - Button was pressed, False - animation is active.
		*/
		bool forcePressed();
		/**
		* Block any activity in the button.
		*/
		void block();
		/**
		* Unlocks activity among the button.
		*/
		void release();
		/**
		* Checks the activity of the button.
		*/
		bool isBlocked() const;
	};
}
#endif
