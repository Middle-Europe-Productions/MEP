////////////////////////////////////////////////////////////
//
//	AnimationManager.cpp created with the use of SFML
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
#include<MEPGraphics/AnimationManager.h>

namespace MEP
{
	AnimationManager::AnimationManager(BaseWindow& base) : m_baseWindow(base)
	{}


	void AnimationManager::runGroup(const Direction direc, MEP::U_int32 group, sf::Time currentTime) {
		execute(
			[&]() { position._execute([&direc, &currentTime](auto& x) { x.second->run(direc, currentTime); }, group); },
			[&]() { color._execute([&direc, &currentTime](auto& x) { x.second->run(direc, currentTime); }, group); },
			[&]() { object._execute([&direc, &currentTime](auto& x) { x.second->run(direc, currentTime); }, group); }
		);
	}

	void AnimationManager::debugOutput(std::ostream& out) {
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
}