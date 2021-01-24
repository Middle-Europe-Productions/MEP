
////////////////////////////////////////////////////////////
//
//	MEPWindow.h created with the use of SFML
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
#ifndef MEP_WINDOW_H
#define MEP_WINDOW_H
#include "Application.h"

#include "Loading.h"
/*
Deffinition of a base window HUB with a exit minimalize and MEP trademark buttons.
*/
#include "Hub.h"
/*
Inharitance: Resources <MEP/MEPGraphics/ResourcesManager.h> , WindowStats
Manager of an application provides virtual definition af a base sf::Window functionallities.
*/
#include "BaseManager.h"
/*
Deffinition of a base MEP Window
*/
#include "Base.h"
/*
Provides definitions of a cross plaftorm functions not included in the SFML 2 lib.
Namespace PLATFORM
*/
#include "WindowCrossPlatform.h"
/*
Base window functionalities time and FPS handler.
*/
#include "WindowStat.h"
/*
Deffinition of a loading Window which handles given methods on a different thread.
*/

#endif