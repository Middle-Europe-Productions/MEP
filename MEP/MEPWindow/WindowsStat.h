
////////////////////////////////////////////////////////////
//
//	WindowStat.h created with the use of SFML
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
#include <SFML/System/Time.hpp>
namespace MEP {
	namespace Window {
		//Holds information about basic window statistics related to time in general. 
		//Avalible operations:
		//-Frame rate.
		//-Global time.
		class WindowStats {
			sf::Time globalTime = sf::Time::Zero;
			sf::Time mStatisticsUpdateTime = sf::Time::Zero;
			unsigned int mStatisticsNumFrames = 0;
		public:
			WindowStats() = default;
			//Updates statistics of a main code loop
			void updateStatistics(sf::Time dt) {
				mStatisticsUpdateTime += dt;
				mStatisticsNumFrames += 1;
				if (mStatisticsUpdateTime >= sf::seconds(1.0f))
				{
					mStatisticsUpdateTime -= sf::seconds(1.0f);
					mStatisticsNumFrames = 0;
				}
			}
			//Returns current number of frames.
			//if 0 == updateStatistics has not been called!
			unsigned int GetFrameRate() const { 
				return mStatisticsNumFrames; 
			}
			//Returns global time.
			sf::Time& GetGlobalTime() {
				return globalTime; 
			}
		};
	}
}
