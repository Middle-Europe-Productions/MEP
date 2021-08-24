////////////////////////////////////////////////////////////
//
//	WindowStat.cpp created with the use of SFML
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
#include<MEPWindow/WindowStat.h>

namespace MEP
{
	void WindowStats::updateStatistics(sf::Time dt) {
		mStatisticsUpdateTime += dt;
		mStatisticsNumFrames += 1;
		if (mStatisticsUpdateTime >= sf::seconds(1.0f))
		{
			mStatisticsUpdateTime -= sf::seconds(1.0f);
			mStatisticsNumFrames = 0;
		}
	}

	unsigned int WindowStats::getFrameRate() const {
		return mStatisticsNumFrames;
	}

	sf::Time& WindowStats::getGlobalTime() {
		return globalTime;
	}
}