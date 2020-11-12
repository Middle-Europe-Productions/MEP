
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
	/**
	* \brief MEP::Animation base definition of an animation. 
	*/
	class Animation {
	public:
		/**
		* @enum MEP::Animation::Direction
		* Provides basic movement definition.
		*/
		enum class Direction {
			/** Basic animation movement.*/
			Forward = 0,
			/** Reversed animation movement.*/
			Backwards = 1
		};
		/**
		* @enum MEP::Animation::AnimationInit
		* Provides basic animation tags.
		*/
		enum class AnimationInit {
			/** Animation is not initialized.*/
			NotInit,
			/** Animation will be following the Animation.*/
			Follow,
			/** Animation will be animating Object type of variable.*/
			ObjectAnimation,
			/** Animation will be animating Position type of variable.*/
			PositionAnimation
		};
		/**
		* @enum MEP::Animation::AdditionalTag
		* Provides a support for automatic activation. 
		*/
		enum class AdditionalTag {
			/** There no additional tag.*/
			Non,
			/** Animation will be automatically activated at MEP::Window::BaseWindow entry.*/
			RunAtEntry,
			/** Animation will be automatically activated at MEP::Window::BaseWindow exit.*/
			RunAtEnd,
			/** Animation will be automatically activated at MEP::Window::BaseWindow entry and exit.*/
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
		/**
		* Constructor of an base animation.
		* @param[in] initType : Initialization type.
		* @param[in] frameRate : Frame rate of an animation.
		*/
		Animation(const AnimationInit initType, const float frameRate):
			isInit(initType),
			toWait(sf::milliseconds(1000) / frameRate) {}
		/**
		* Constructor of an base animation.
		* @param[in] initType : Initialization type.
		* @param[in] towait : Time to wait between aniamtion frames.
		*/
		Animation(const AnimationInit initType, const sf::Time towait) :
			isInit(initType),
			toWait(towait) {}
		/**
		* Copy constructor of an base animation.
		* @param[in] x : MEP::Animation.
		*/
		Animation(const Animation& x) :
			isInit(x.isInit),
			updateTime(x.updateTime),
			toWait(x.toWait),
			isRunning(x.isRunning),
			direction(x.direction) {}
		/**
		* Sets the running tag to true and changes the direction of a movement, furthermore,
		* it is capable of setting a current time.
		* @param[in] direc : MEP::Animation::Direction.
		* @param[in] currentTime : sf::Time = sf::Time::Zero.
		*/
		virtual void Run(const Direction direc, sf::Time currentTime = sf::Time::Zero) {
			direction = direc;
			updateTime = currentTime;
			isRunning = true;
		};
		/**
		* Changes current status to !status
		*/
		void ChangeStatus() { 
			isRunning = !isRunning; 
		}
		/**
		* Outputs a current status of an animation.
		* @return true - animation is active, false - animation is unactive.
		*/
		bool GetStatus() const { 
			return isRunning; 
		}
		/**
		* Changes the additional tag of an animation.
		* @param[in] tag MEP::Animation::AdditionalTag.
		*/
		void ChangeTag(const AdditionalTag& tag) { 
			m_tag = tag; 
		}
		/**
		* Outputs time to wait between animation frames.
		* @return sf::Time
		*/
		sf::Time GetToWait() const { 
			return toWait; 
		}
		/**
		* Outputs animation initialization tag.
		* @return MEP::Animation::AnimationInit
		*/
		const AnimationInit GetInit() const { 
			return isInit; 
		}
		/**
		* Outputs animation direction.
		* @return MEP::Animation::Direction
		*/
		const Direction& GetDirection() const { 
			return direction; 
		}
	};
};