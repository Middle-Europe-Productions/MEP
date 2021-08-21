
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
#ifndef MEP_HUB_ASSETS_H
#define MEP_HUB_ASSETS_H

#include <MEPWindow/BaseTemplate.h>
#include <MEPWindow/Application.h>
#include <MEPGraphics/Assets.h>
namespace MEP {
	namespace Assets {
			/**
			* \brief Holds hub assets.
			*/
			class HubAssets : public NonCopyable {
			protected:
				//64x26 MEP logo
				const sf::Uint8 *imageArray;
				//simple box
				const sf::Uint8 *topArray;
				//58x28 exit button
				const sf::Uint8 *exitArray;
				//58x28 background
				const sf::Uint8 *iB1;
				//58x28 background
				const sf::Uint8 *iB2;
				//58x28 minimize button
				const sf::Uint8 *minArray;
			public:
				HubAssets();
				~HubAssets();
			};
		}
}

#endif
