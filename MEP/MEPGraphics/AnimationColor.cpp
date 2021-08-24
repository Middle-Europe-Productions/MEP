
////////////////////////////////////////////////////////////
//
//	AnimationColor.cpp created with the use of SFML
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
#include<MEPGraphics/AnimationColor.h>

namespace MEP
{
	sf::Uint8 AnimationColor::value(sf::Uint8 r, const sf::Uint8& entry, const sf::Uint8& exit) const {
		if (entry - exit < 0) {
			return entry + *currentFrame * abs(entry - exit) / 100;
		}
		else if (entry - exit > 0) {
			return entry - *currentFrame * abs(entry - exit) / 100;
		}
		return r;
	}

	void AnimationColor::updateRGBA() {
		r = value(r, entry_r, exit_r);
		g = value(g, entry_g, exit_g);
		b = value(b, entry_b, exit_b);
		a = value(a, entry_a, exit_a);
	}

	AnimationColor::AnimationColor(sf::Color entry,
		sf::Color exit,
		sf::Time length,
		const float frameRate,
		const double begin,
		const double end,
		std::function<double(double x)> function) :
		AnimationPosition(0, 100, length, frameRate, begin, end, function),
		entry_r(entry.r),
		entry_g(entry.g),
		entry_b(entry.b),
		entry_a(entry.a),
		exit_r(exit.r),
		exit_g(exit.g),
		exit_b(exit.b),
		exit_a(exit.a),
		r(entry.r),
		g(entry.g),
		b(entry.b),
		a(entry.a)
	{}

	bool  AnimationColor::changeExitColor(const sf::Color& newColor) {
		if (!isRunning) {
			exit_r = newColor.r;
			exit_g = newColor.g;
			exit_b = newColor.b;
			exit_a = newColor.a;
			return true;
		}
		else {
			return false;
		}
	}

	bool AnimationColor::changeEntryColor(const sf::Color& newColor) {
		if (!isRunning) {
			entry_r = newColor.r;
			entry_g = newColor.g;
			entry_b = newColor.b;
			entry_a = newColor.a;
			return true;
		}
		else {
			return false;
		}
	}

	bool AnimationColor::changeEndPointColor(const sf::Color& newColor) {
		if (!isRunning) {
			if (*currentFrame == frames.front()) {
				changeExitColor(newColor);
			}
			else {
				changeEntryColor(newColor);
			}
		}
		else {
			return false;
		}
	}

	void AnimationColor::update(sf::Time& currentTime) {
		updatePositionAnimation(currentTime);
		updateRGBA();
	}

	sf::Color AnimationColor::getFrameAsColor() const {
		return sf::Color(r, g, b, a);
	}

	void  AnimationColor::debugOutput(std::ostream& out) const {
		out << "MEP::AnimationColor {[R,G,B,A]  Entry: ["
			<< (int)entry_r << "," << (int)entry_g << "," << (int)entry_b << "," << (int)entry_a << "]" <<
			", Exit: ["
			<< (int)exit_r << "," << (int)exit_g << "," << (int)exit_b << "," << (int)exit_a << "]" <<
			", Current: ["
			<< (int)r << "," << (int)g << "," << (int)b << "," << (int)a << "]";
		delayOutput(out);
		out << "}";
		animationDebug(out);
	}
}