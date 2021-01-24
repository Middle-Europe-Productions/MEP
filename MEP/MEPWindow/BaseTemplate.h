
////////////////////////////////////////////////////////////
//
//	BaseTemplate.h created with the use of SFML
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
#ifndef MEP_BASE_TEMPLATE_H
#define MEP_BASE_TEMPLATE_H

#include"Base.h"

#pragma once
namespace MEP {
	namespace Window {
		namespace Template {
			/**
			* I do recommend to use it with all of the template windows.
			* It provides two additional methods:
			* additinalEvents() - it is recommended to override the method in case of additional out of MEP::Window::Template events.
			* additinalInit() - it is recommended to override the method in case of additional initialization objects.
			* \brief A class with the additional methods for the MEP::Window::Template
			*/
			class BaseTemplate {
			public:
				BaseTemplate() = default;				
				/**
				* Method handling additional events defined by the user.
				* It is recommended to use it with any Template window.
				*/
				virtual void additionalEvents(sf::RenderWindow& Window, sf::Event& Event) {}
				/**
				* Method handling initialization of the objects defined by the user.
				* It is recommended to use it with any Template window.
				*/
				virtual void additionalInit() {};
			};
		}
	}
}
				
#endif