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
#include<list>

namespace MEP {
	/**
	* \brief Designed to control a set of animations.
	*/
	class AnimationManager {
		/**
		Pointer to a base window. It links the objects.
		*/
		BaseWindow& m_baseWindow;
		/**
		* Containers
		*/
		MEPtools::GroupManager<AnimationPosition, std::shared_ptr<AnimationPosition>> position;
		MEPtools::GroupManager<AnimationColor, std::shared_ptr<AnimationColor>> color;
		MEPtools::GroupManager<AnimationObject, std::shared_ptr<AnimationObject>> object;
		/**
		* Outputs the element.
		*/
		template<typename X, typename A, typename B, typename C>
		X* get(A a, B b, C c) {
			if (std::is_same<X, AnimationPosition>()) {
				return dynamic_cast<X*>(a());
			}
			else if ((std::is_same<X, AnimationColor>())) {
				return dynamic_cast<X*>(b());
			}
			else if ((std::is_same<X, AnimationObject>())) {
				return dynamic_cast<X*>(c());
			}
			else {
				throw MEP::ResourceException("AnimationManager", "Incorrect type", MEP::ResourceException::ExceptionType::IncorrectType);
			}
		}
		template<typename A, typename B, typename C>
		void execute(A a, B b, C c) {
			a();
			b();
			c();
		}
	public:
		/**
		* Constructor with the automatic assignment of the values to the BaseWindow Drawable container.
		*/
		AnimationManager(BaseWindow& base) : m_baseWindow(base) {}
		/**
		* Addition.
		*/
		template<typename X>
		void add(X* animation, MEP::U_int32 ID, MEP::U_int32 group = -1, MEP::U_int32 renderGroup = -1) {
			if (std::is_same<X, AnimationPosition>()) {
				position._insert(ID, group, std::shared_ptr<AnimationPosition>(std::move(dynamic_cast<AnimationPosition*>(animation))));
			}
			else if ((std::is_same<X, AnimationColor>())) {
				color._insert(ID, group, std::shared_ptr<AnimationColor>(std::move(dynamic_cast<AnimationColor*>(animation))));
			}
			else if ((std::is_same<X, AnimationObject>())) {
				object._insert(ID, group, std::shared_ptr<AnimationObject>(std::move(dynamic_cast<AnimationObject*>(animation))));
			}
			else {
				throw MEP::ResourceException("AnimationManager", "Incorrect type", MEP::ResourceException::ExceptionType::IncorrectType);
			}
			m_baseWindow.newObject(static_cast<MEP::Drawable*>(animation));
		}
		/**
		* Outputs the animation.
		*/
		template<typename X>
		X& get(MEP::U_int32 ID, MEP::U_int32 group = -1) {
			return *get<X>(
				[this, &ID, &group]() { return &position._get(ID, group); },
				[this, &ID, &group]() { return &color._get(ID, group); },
				[this, &ID, &group]() { return &object._get(ID, group); }
			);
		}
		/**
		* Run the animation.
		*/
		template<typename X>
		void run(const Direction direc, MEP::U_int32 ID, MEP::U_int32 group = -1, sf::Time currentTime = sf::Time::Zero) {
			get<X>(
				[this, &ID, &group]() { return &position._get(ID, group); },
				[this, &ID, &group]() { return &color._get(ID, group); },
				[this, &ID, &group]() { return &object._get(ID, group); }
				  )->run(direc, currentTime);
		}
		/**
		* Runs a a group of animations.
		*/
		void runGroup(const Direction direc, MEP::U_int32 group = -1, sf::Time currentTime = sf::Time::Zero) {
			execute(
				[&]() { position._execute([&direc, &currentTime](auto& x) { x.second->run(direc, currentTime); }, group); },
				[&]() { color._execute([&direc, &currentTime](auto& x) { x.second->run(direc, currentTime); }, group); },
				[&]() { object._execute([&direc, &currentTime](auto& x) { x.second->run(direc, currentTime); }, group); }
			);
		}
		/**
		* Execute a method for a group of objects.
		* Example: [&direc, &currentTime](auto& x) { x.second->run(direc, currentTime); }, group); },
		* will run the animation.
		*/
		template<typename Method>
		void executeGroup(Method method, MEP::U_int32 group = -1) {
			execute(
				[&]() { position._execute(method, group); },
				[&]() { color._execute(method, group); },
				[&]() { object._execute(method, group); }
			);
		}
		/**
		* Outputs the debug information.
		*/
		void debugOutput(std::ostream& out) {
			out << "Animation Manager owned by Window ID:" << m_baseWindow.getID() << std::endl;
			if (!position._empty()) {
				out << "]--AnimationPosition elements:" << std::endl;
				position._debugOutput(out, [](auto& x, std::ostream& out) { out << *x.second.get() << std::endl; });
			}
			if (!color._empty()) {
				out << "]--AnimationColor elements:" << std::endl;
				color._debugOutput(out, [](auto& x, std::ostream& out) { out << *x.second.get() << std::endl; });
			}
			if (!object._empty()) {
				out << "]--AnimationColor elements:" << std::endl;
				object._debugOutput(out, [](auto& x, std::ostream& out) { out << *x.second.get() << std::endl; });
			}
		}
	};
}

#endif