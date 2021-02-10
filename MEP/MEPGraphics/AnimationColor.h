
////////////////////////////////////////////////////////////
//
//	AnimationObject.h created with the use of SFML
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
#ifndef MEP_ANIMATION_COLOR_H
#define MEP_ANIMATION_COLOR_H

#include"AnimationPosition.h"
namespace MEP {
	/**
	* This class uses MEP::AnimationPosition. It changes color A to the color B (alpha channel is supported).
	* \brief Class is responsible for the sf::Color transitions.
	*/
	class AnimationColor : public AnimationPosition {
		/**
		* Entry values.
		*/
		sf::Uint8 entry_r, entry_g, entry_b, entry_a;
		/**
		* Exit values.
		*/
		sf::Uint8 exit_r, exit_g, exit_b, exit_a;
		/**
		* Current values.
		*/
		sf::Uint8 r, g, b, a;
		sf::Uint8 value(sf::Uint8 r, const sf::Uint8& entry, const sf::Uint8& exit) const {
			if (entry - exit < 0) {
				return entry + *currentFrame * abs(entry - exit) / 100;
			}
			else if (entry - exit > 0) {
				return entry - *currentFrame * abs(entry - exit) / 100;
			}
			return r;
		}
		void updateRGBA() {
			r = value(r, entry_r, exit_r);
			g = value(g, entry_g, exit_g);
			b = value(b, entry_b, exit_b);
			a = value(a, entry_a, exit_a);
		}
	public:
		/**
		* Constructor of an animation color.
		* @param[in] entry : Entry color. Before the iterations.
		* @param[in] exit : Exit color. After the iterations.
		* @param[in] frameRate : Frame rate of an animation.
		* @param[in] begin : Begining point on a graph,
		* @param[in] end : End point of a graph.
		* @param[in] lenght : Animation lenght in ms.
		* @param[in] fun : Function graph. Method with the return type double. 
		*/
		AnimationColor(sf::Color entry,
			sf::Color exit,
			sf::Time lenght,
			const float frameRate = 120,
			const double begin = 0,
			const double end = 10,
			std::function<double(double x)> function = [](double x)->double { return x; }) :
			AnimationPosition(0, 100, lenght, frameRate, begin, end, function),
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
		/**
		* Changes the exit color. Exit means targeted color (after the iterations).
		* @param[in] newColor : sf::Color
		* @return : True - if changes were applied. False - if they were rejected.
		*/
		bool changeExitColor(const sf::Color& newColor) {
			if (!isRunning) {
				exit_r = newColor.r;
				exit_g = newColor.g;
				exit_b = newColor.b;
				exit_a = newColor.a;
			}
			else {
				return false;
			}
		}
		/**
		* Changes the entry color. Entry means basic color (before the iterations).
		* @param[in] newColor : sf::Color
		* @return : True - if changes were applied. False - if they were rejected.
		*/
		bool changeEntryColor(const sf::Color& newColor) {
			if (!isRunning) {
				entry_r = newColor.r;
				entry_g = newColor.g;
				entry_b = newColor.b;
				entry_a = newColor.a;
			}
			else {
				return false;
			}
		}
		/**
		* Changes the current endpoint color. Current endpoint is defined as the opposite of a current color.
		* @param[in] newColor : sf::Color
		* @return : True - if changes were applied. False - if they were rejected.
		*/
		bool changeEndPointColor(const sf::Color& newColor) {
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
		/**
		* Override of a MEP::Drawable update.
		*/
		void update(sf::Time& currentTime) override {
			updatePositionAnimation(currentTime);
			updateRGBA();
		}
		/**
		* Outputs the current sf::Color.
		* @return : Current sf::Color
		*/
		virtual sf::Color getFrameAsColor() const override {	
			return sf::Color(r, g, b, a);
		}
	};
}

#endif
