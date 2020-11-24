
////////////////////////////////////////////////////////////
//
//	Drawable.h created with the use of SFML
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
#include<SFML/Graphics.hpp>
namespace MEP {
	/**
	* \brief MEP::Drawable provides a basic implementation of an object with the ability of display it on a screen.
	*/
	class Drawable {
	public:
		/**
		* @enum MEP::Button::DrawTag defines a draw tag.
		*/
		enum class DrawTag {
			/** There is no draw tag.*/
			Non,
			/** View lock tag. Objects will be rendered using master view if custom view is enabled.*/
			ViewLock,
			/** Unactive tag. Objects will not be rendered. */
			Unactive
		};
		/**
		* Outputs draw tag of a MEP::Drawable.
		* @return : MEP::Drawable::DrawTag.
		*/
		const DrawTag& getDrawTag() const { return m_drawTag; }
		/**
		* Sets the draw tag of a MEP::Drawable.
		* @param[in] : MEP::Drawable::DrawTag.
		*/
		void setDrawTag(const DrawTag& tag) { m_drawTag = tag; }
	private:
		DrawTag m_drawTag = DrawTag::Non;
	public:
		/**
		* Default contructor.
		*/
		Drawable() = default;
		/**
		* Default virtual draw function.
		* @param[in] window : Reference to a window.
		* @return True if the drawing was successful, or false if there is something wrong with an object and it must be redrawn.
		*/
		virtual bool draw(sf::RenderWindow& window) { return false; };
		/**
		* Default virtual update function.
		* @param[in] currentTime : Current global time.
		*/
		virtual void update(sf::Time& currentTime) {};
		/**
		* Default virtual entry update function.
		* @param[in] currentTime : Current global time.
		*/
		virtual void entryUpdate(sf::Time& currentTime) { update(currentTime); };
		/**
		* Default virtual exit update function.
		* @param[in] currentTime : Current global time.
		*/
		virtual void exitUpdate(sf::Time & currentTime) { update(currentTime); };
		/**
		* Default virtual activation status method.
		* @param[in] currentTime : Current global time.
		*/
		virtual bool isActive() const { return false; };
		virtual ~Drawable() {};
	};
};
