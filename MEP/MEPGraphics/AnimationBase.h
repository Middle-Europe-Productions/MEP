
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
//	Created by Piotr Skibi�ski
//	Copyright � Middle Europe Productions. All rights reserved.
//
////////////////////////////////////////////////////////////
#ifndef MEP_ANIMATION_H
#define MEP_ANIMATION_H

#include<SFML/Graphics.hpp>
#include<MEPGraphics/NonCopyable.h>
#include<MEPGraphics/AnimationDelay.h>

namespace MEP {
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
	* @enum MEP::Animation::AdditionalTag
	* Provides a support for automatic activation.
	*/
	enum AdditionalTag : MEP::U_int32 {
		/** There no additional tag.*/
		AdditionalTagDisabled = 0,
		/** Animation will be automatically activated at MEP::Window::BaseWindow entry.*/
		RunAtEntry = 1,
		/** Animation will be automatically activated at MEP::Window::BaseWindow LowEntry.*/
		RunAtLowEntry = 1 << 2,
		/** Animation will be automatically activated at MEP::Window::BaseWindow exit.*/
		RunAtEnd = 1 << 3,
		/** Animation will be automatically activated at MEP::Window::BaseWindow LowExit.*/
		RunAtLowEnd = 1 << 4,
		/** Animation will be automatically activated at MEP::Window::BaseWindow entry and exit.*/
		RunAtEntryAndEnd = RunAtEntry | RunAtEnd,
		/** Animation will be automatically activated at MEP::Window::BaseWindow lowEntry and lowExit.*/
		RunAtLowEntryAndEnd = RunAtLowEntry | RunAtLowEnd,
		/** Animation will be automatically activated at MEP::Window::BaseWindow entry, lowEntry, loeExit and exit.*/
		RunAlways = RunAtLowEntry | RunAtEntry | RunAtEnd | RunAtLowEnd
	};
	/**
	* \brief MEP::Animation base definition of an animation. 
	*/
	class Animation : public MEPtools::AnimationDelay {
		/**
		* Tags to char for the debug purposes.
		*/
		const char* __Direction[2] = { "Forward", "Backwards" };
		const char* __AnimationInit[4] = { "NotInit", "Follow", "ObjectAnimation", "PositionAnimation" };
		const char* __AdditionalTag[8] = {"Non", "RunAtEntry", "RunAtLowEntry", "RunAtEnd", "RunAtLowEnd", "RunAtEntryAndEnd", "RunAtLowEntryAndEnd", "RunAlways"};
	public:
		/**
		* @enum MEP::Animation::AnimationInit
		* Provides basic animation tags.
		*/
		enum class AnimationInit {
			/** Animation is not initialized.*/
			NotInit = 0,
			/** Animation will be animating Object type of variable.*/
			ObjectAnimation = 1,
			/** Animation will be animating Position type of variable.*/
			PositionAnimation = 2
		};
	protected:
		MEP::U_int32 m_tag = AdditionalTag::AdditionalTagDisabled;
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
		//Debug information about the class state
		void animationDebug(std::ostream& out) const {
			out << "\n  \\" << "MEP::AnimationBase { AnimationInit: " << __AnimationInit[(int)isInit]
				<< ", Direction: " << __Direction[(int)direction]
				<< ", AdditionalTag:";
			if (m_tag & RunAtLowEntry and m_tag & RunAtEntry and m_tag & RunAtEnd and m_tag & RunAtLowEnd) {
				out << " " << __AdditionalTag[7];
			}
			else {
				if (m_tag & RunAtLowEntry and m_tag & RunAtLowEnd) {
					out << " " << __AdditionalTag[6];
				}
				else {
					if (m_tag & RunAtLowEnd) {
						out << " " << __AdditionalTag[4];
					}
					if (m_tag & RunAtLowEntry) {
						out << " " << __AdditionalTag[3];
					}
				}
				if (m_tag & RunAtEntry and m_tag & RunAtEnd) {
					out << " " << __AdditionalTag[5];
				}
				else {
					if (m_tag & RunAtEnd) {
						out << " " << __AdditionalTag[2];
					}
					if (m_tag & RunAtEntry) {
						out << " " << __AdditionalTag[1];
					}
				}
				if (m_tag & AdditionalTagDisabled) {
					out << " " << __AdditionalTag[0];
				}
			}
			out << " }";
		}
	public:
		/**
		* Default constructor.
		*/
		Animation() = default;
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
		virtual void run(const Direction direc, sf::Time currentTime = sf::Time::Zero) {
			direction = direc;
			updateTime = currentTime;
			isRunning = true;
		};
		/**
		* Changes current status to !status
		*/
		void changeStatus() { 
			isRunning = !isRunning; 
		}
		/**
		* Outputs a current status of an animation.
		* @return true - animation is active, false - animation is unactive.
		*/
		bool getStatus() const { 
			return isRunning; 
		}
		/**
		* Changes the additional tag of an animation.
		* @param[in] tag MEP::Animation::AdditionalTag.
		*/
		void changeTag(MEP::U_int32 tag) {
			m_tag = tag; 
		}
		/**
		* Outputs time to wait between animation frames.
		* @return sf::Time
		*/
		sf::Time getToWait() const { 
			return toWait; 
		}
		/**
		* Outputs animation initialization tag.
		* @return MEP::Animation::AnimationInit
		*/
		AnimationInit getInit() const { 
			return isInit; 
		}
		/**
		* Outputs animation direction.
		* @return MEP::Animation::Direction
		*/
		const Direction& getDirection() const { 
			return direction; 
		}
		/**
		* Sets the direction of an animation.
		*/
		void setDirection(MEP::Direction dir) {
			direction = dir;
		}
		/**
		* Resets the parameters of the animation if the animation is not active.
		* Reset means changing it's current frame to begin or end depending of the direction.
		* If direction is forward changes to begin otherwise to end.
		*/
		virtual bool reset() { return false; };
	};
};

#endif
