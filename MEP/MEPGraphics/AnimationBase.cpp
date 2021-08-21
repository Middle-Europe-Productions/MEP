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
#include<MEPGraphics/AnimationBase.h>
namespace MEP
{
	void Animation::animationDebug(std::ostream& out) const {
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
	Animation::Animation(const AnimationInit initType, const float frameRate) :
		isInit(initType),
		toWait(sf::milliseconds(1000) / frameRate) 
	{}

	Animation::Animation(const AnimationInit initType, const sf::Time towait) :
		isInit(initType),
		toWait(towait) 
	{}

	Animation::Animation(const Animation& x) :
		isInit(x.isInit),
		updateTime(x.updateTime),
		toWait(x.toWait),
		isRunning(x.isRunning),
		direction(x.direction) {}

	void Animation::run(const Direction direc, sf::Time currentTime) {
		direction = direc;
		updateTime = currentTime;
		isRunning = true;
	};

	void Animation::changeStatus() {
		isRunning = !isRunning;
	}

	bool Animation::getStatus() const {
		return isRunning;
	}

	void Animation::changeTag(U_int32 tag) {
		m_tag = tag;
	}

	sf::Time Animation::getToWait() const {
		return toWait;
	}

	Animation::AnimationInit Animation::getInit() const {
		return isInit;
	}

	const Direction& Animation::getDirection() const {
		return direction;
	}

	void Animation::setDirection(Direction dir) {
		direction = dir;
	}

	bool Animation::reset() { return false; };
}