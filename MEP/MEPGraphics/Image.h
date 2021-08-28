////////////////////////////////////////////////////////////
//
//	Image created with the use of SFML
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
#ifndef MEP_IMAGE_H
#define MEP_IMAGE_H
#include<MEPGraphics/NonCreatable.h>
#include<SFML/Graphics/Image.hpp>
namespace MEP
{
	/**
	* \brief This class will represent an image class.
	* *Warning* Currently the class is not an individual component.
	* In is an extension of the sf::Image class.
	*/
	class Image: NonCreatable
	{
	public:
		static sf::Image createBox(sf::Vector2u size, sf::Color color = { 0, 0, 0, 0 });
	};
}

#endif