
////////////////////////////////////////////////////////////
//
//	OSSetUp.h created with the use of SFML
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

#define MEP_STATE "Alpha";
#define MEP_STATE_VERSION 3;

#if defined(_WIN32)
//Windows
	#define MEP_WINDOWS
	#ifndef NOMINMAX
		#define NOMINMAX
	#endif
#elif defined(__APPLE__) and defined(__MACH__)
	#error __APPLE__ curently not supported!
#elif defined(__UNIX__)
	#error __UNIX__ currently not supported!
#else
	#error Operating system not supported!
#endif