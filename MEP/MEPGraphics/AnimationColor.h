
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

#include<MEPGraphics/AnimationPosition.h>
namespace MEP {
	/**
	* @enum MEP::ColorChannel
	* Types of the color channels.
	*/
	enum ColorChannel : MEP::U_int32 {
		/** Non of the channels is being blocked.*/
		NON = 0,
		/** Red color channel.*/
		R = 1 << 1,
		/** Green color channel.*/
		G = 1 << 2,
		/** Blue color channel.*/
		B = 1 << 3,
		/** Alpha color channel.*/
		A = 1 << 4,
		/** All color channels.*/
		ALL = R | G | B | A
	};
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
		sf::Uint8 value(sf::Uint8 r, const sf::Uint8& entry, const sf::Uint8& exit) const;
		void updateRGBA();
	public:
		/**
		* Constructor of an animation color.
		* @param[in] entry : Entry color. Before the iterations.
		* @param[in] exit : Exit color. After the iterations.
		* @param[in] frameRate : Frame rate of an animation.
		* @param[in] begin : Begining point on a graph,
		* @param[in] end : End point of a graph.
		* @param[in] length : Animation lenght in ms.
		* @param[in] fun : Function graph. Method with the return type double. 
		*/
		AnimationColor(sf::Color entry,
			sf::Color exit,
			sf::Time length,
			const float frameRate = 120,
			const double begin = 0,
			const double end = 10,
			std::function<double(double x)> function = [](double x)->double { return x; });
		/**
		* Changes the exit color. Exit means targeted color (after the iterations).
		* @param[in] newColor : sf::Color
		* @return : True - if changes were applied. False - if they were rejected.
		*/
		bool changeExitColor(const sf::Color& newColor);
		/**
		* Changes the entry color. Entry means basic color (before the iterations).
		* @param[in] newColor : sf::Color
		* @return : True - if changes were applied. False - if they were rejected.
		*/
		bool changeEntryColor(const sf::Color& newColor);
		/**
		* Changes the current endpoint color. Current endpoint is defined as the opposite of a current color.
		* @param[in] newColor : sf::Color
		* @return : True - if changes were applied. False - if they were rejected.
		*/
		bool changeEndPointColor(const sf::Color& newColor);
		/**
		* Override of a MEP::Drawable update.
		*/
		void update(sf::Time& currentTime) override;
		/**
		* Outputs the current sf::Color.
		* @return : Current sf::Color
		*/
		virtual sf::Color getFrameAsColor() const override;
		/**
		* Debug output of the class.
		*/
		virtual void debugOutput(std::ostream& out) const;
	};
}

#endif
