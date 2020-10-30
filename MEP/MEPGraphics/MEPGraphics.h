
////////////////////////////////////////////////////////////
//
//	MEPGraphics created with the use of SFML
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
//core classes
#include"Drawable.h"
/*
Pure virtual class.
Provides core attributes designed to provide basic and easy to use rendering and updathing mechanisms.
*/
#include"Object.h"
/*
Inheritance: Drawable
Provides basic object definition. 
It is also capable of creating alpha channel map as well as storage of memory limited number of sf::Texture objects.
*/
#include"Following.h"
/*
Provides following definition.
*/
#include"AnimationBase.h"
/*
Defines basic animation attributes and time control with the use of sf::Time
*/
//to use classes
#include"AnimationObject.h"
/*
Inheritance: Animation, Object, Following
Enables animation and display of a set of the objects.
Simple animation displaying.
*/
#include"TextureObject.h"
/*
Inheritance: Object, Following
Enables display of a single texture. 
*/
#include"Button.h"
/*
Inheritance: AnimationObject
Defines simple button with the use of at least a set o three objects with the MEP::Object.
*/
#include"AnimationPossition.h"
/*
Inheritance: Drawable, Animation
Simple definition of a possition animation with the use of lambda function.
Possition is beeing defined following the shape of a given function. 
f(x) or -f(x) according to the given values
*/
//management classes
#include"ResourceManager.h"
/*
Enables automation data loading. Using MEP::Object and sf::Texture
*/
