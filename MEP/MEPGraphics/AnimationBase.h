
////////////////////////////////////////////////////////////
//
//	AnimationBase created with the use of SFML
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

#include<SFML/Graphics.hpp>
#pragma once
namespace MEP {
	class Animation {
	public:
		//direction of an animation
		enum class Direction {
			Forward = 0,
			Backwards = 1
		};
		//initialization type of an animation
		enum class AnimationInit {
			NotInit,
			Follow,
			ObjectAnimation,
			PossitionAnimation
		};
		//additional tags
		enum class AdditionalTag {
			Non,
			RunAtEntry,
			RunAtEnd,
			RunAtEntryAndEnd
		};
	protected:
		AdditionalTag m_tag = AdditionalTag::Non;
		//initialization of a current object
		AnimationInit isInit = AnimationInit::NotInit;
		//time of a last update
		sf::Time updateTime = sf::Time::Zero;
		//wait between frames
		sf::Time toWait = sf::Time::Zero;
		//info about animation status
		bool isRunning = false;
		//direction of an animation movement
		Direction direction = Direction::Backwards;
	public:
		Animation(const AnimationInit initType, const float frameRate):
			isInit(initType),
			toWait(sf::milliseconds(1000) / frameRate) {}
		Animation(const AnimationInit initType, const sf::Time towait) :
			isInit(initType),
			toWait(towait) {}
		Animation(const Animation& x) :
			isInit(x.isInit),
			updateTime(x.updateTime),
			toWait(x.toWait),
			isRunning(x.isRunning),
			direction(x.direction) {}
		//Ests the running tag to true and changes the direction of a movement, furthermore,
		//it is capable of setting a current time.
		virtual void Run(const Direction direc, sf::Time currentTime = sf::Time::Zero) {
			direction = direc;
			updateTime = currentTime;
			isRunning = true;
		};
		//Changes current status to !status
		void ChangeStatus() { isRunning = !isRunning; }
		//Returns a status of an animation
		bool GetStatus() const { return isRunning; }
		//changing a tag of an animation
		void ChangeTag(const AdditionalTag& tag) { m_tag = tag; }
		//toWait information
		sf::Time GetToWait() const { return toWait; }
		//Returns an animation initialization type
		const AnimationInit GetInit() const { return isInit; }
		//current direction of an animation
		const Direction& GetDirection() const { return direction; }
	};
};