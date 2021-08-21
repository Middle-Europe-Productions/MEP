
////////////////////////////////////////////////////////////
//
//	Hub.h created with the use of SFML
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
#ifndef MEP_HUB_H
#define MEP_HUB_H

#include <MEPWindow/HubAssets.h>
#include <MEPGraphics/Config.h>
#include <MEPGraphics/AnimationObject.h>
#include <MEPGraphics/AnimationColor.h>

namespace MEP {
	namespace Template {
			enum HubElements : MEP::U_int32 {
				TopLine = 1 << 1,
				MEPLogo = 1 << 2,
				ExitButton = 1 << 3,
				MiniButton = 1 << 4,
				All = TopLine | MEPLogo | ExitButton | MiniButton
			};
			/**
			* Functionalities: \n
			* Exit button. \n
			* Minimization button. \n
			* MEP logo :)
			* \brief Template of a custom Middle Europe Productions hub.
			*/
			class Hub : private Assets::HubAssets, public BaseTemplate, public BaseWindow {
				MEP::TextureObject* textures[4];
				MEP::Button* buttons[2];
			public:
				/**
				* Constructor of a MEP::Template::Hub
				* @param[in] ID : Window identifier
				* @param[in] base : Reference to a MEP::Window::Template::Application
				* @param[in] color : Color of the elements.
				*/
				Hub(unsigned int ID, MEP::Template::Application& base, const sf::Color& color = sf::Color::White);
				/**
				* Destructor
				*/
				~Hub();
				/**
				* Changes the color of a HUB.
				* @param[in] event : sf::Color
				*/
				void changeColor(const sf::Color& color);
				void setFollow(const MEP::AnimationColor& animation, HubElements element, MEP::U_int32 x);
				void setFollow(const MEP::AnimationPosition& base, const MEP::Following::FollowType type, HubElements element);
				/**
				* Handles the events of the Hub
				* *Warning* If you want to add your own events just ovveride the additionalEvents() method from MEP::Window::Template::BaseWindow
				* @param[in] Window : sf::RenderWindow 
				* @param[in] event : sf::Event& event
				*/
				void handleEvent(sf::RenderWindow& Window, sf::Event& event) override;
			};
		}
}

#endif
