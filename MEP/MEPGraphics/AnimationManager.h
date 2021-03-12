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
#ifndef MEP_ANIMATION_MANAGER_H
#define MEP_ANIMATION_MANAGER_H

#include<MEPGraphics/AnimationColor.h>
#include<MEPGraphics/AnimationObject.h>
#include<MEPWindow/BaseWindow.h>
#include<MEPGraphics/GroupSet.h>
#include<list>

namespace MEP {
	/**
	* \brief Designed to control a set of animations.
	*/
	class AnimationManager: private MEPtools::GroupSet<AnimationPosition, AnimationColor, AnimationObject> {
		/**
		Pointer to a base window. It links the objects.
		*/
		BaseWindow& m_baseWindow;
	private:
		/**
		* Final case.
		*/
		void add() {}
	public:
		/**
		* Constructor with the automatic assignment of the values to the BaseWindow Drawable container.
		*/
		AnimationManager(BaseWindow& base): m_baseWindow(base) {}
		/**
		* Addition.
		*/
		template<typename X>
		void add(X* animation, MEP::U_int32 ID, MEP::U_int32 group = -1, MEP::U_int32 renderGroup = -1) {
			if (std::is_same<X, AnimationPosition>()) {
				GroupSet::insert<AnimationPosition>(ID, group, std::make_unique<AnimationPosition>(std::move(animation)));
			}
			else if (std::is_same<X, AnimationColor>()) {

			} else if(std::is_same<X, AnimationObject>())
			m_baseWindow.newObject(animation);
			
		}
		virtual void run(const Direction direc, sf::Time currentTime = sf::Time::Zero) override {

		}
	};
}

#endif