////////////////////////////////////////////////////////////
//
//	AnimationDelay.cpp created with the use of SFML
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
#include<MEPGraphics/AnimationDelay.h>

namespace MEPtools
{
	bool AnimationDelay::updateDelay(const sf::Time& currentTime, sf::Time& delay, bool permanentDelay) {
		//Delay not set.
		if (delay == sf::Time::Zero) {
			return true;
		}
		//Delay cycle.
		else if (!cycleDone) {
			if (updateTime == sf::Time::Zero) {
				updateTime = currentTime;
				return false;
			}
			else if (currentTime - updateTime > delay) {
				if (!permanentDelay) {
					delay = sf::Time::Zero;
				}
				cycleDone = true;
				state = State::Base;
				return true;
			}
			else {
				return false;
			}
		}
		else {
			return true;
		}
	}

	const sf::Time& AnimationDelay::delay() const {
		return m_delay;
	}

	bool AnimationDelay::updateDelay(const sf::Time& currentTime) {
		if (state == State::Base) {
			return updateDelay(currentTime, m_delay, permanentDelay);
		}
		else if (state == State::Exit) {
			return updateDelay(currentTime, exit_delay, true);
		}
		else if (state == State::LowExit) {
			return updateDelay(currentTime, L_exit_delay, true);
		}
		else if (state == State::Entry) {
			return updateDelay(currentTime, entry_delay, true);
		}
		else {
			return updateDelay(currentTime, L_entry_delay, true);
		}
	}

	void AnimationDelay::newCycle() {
		cycleDone = false;
		updateTime = sf::Time::Zero;
	}

	void AnimationDelay::changeState(State newState) {
		state = newState;
	}

	void AnimationDelay::setDelay(const sf::Time& delay, bool permaDelay) {
		m_delay = delay;
		permanentDelay = permaDelay;
		newCycle();
	}

	void AnimationDelay::setEntryDelay(const sf::Time& delay) {
		entry_delay = delay;
		newCycle();
	}

	void AnimationDelay::setExitDelay(const sf::Time& delay) {
		exit_delay = delay;
		newCycle();
	}

	void AnimationDelay::setLowEntryDelay(const sf::Time& delay) {
		L_entry_delay = delay;
		newCycle();
	}

	void AnimationDelay::setLowExitDelay(const sf::Time& delay) {
		L_exit_delay = delay;
		newCycle();
	}

	void AnimationDelay::setGeneralDelay(const sf::Time& delay, bool permaDelay) {
		entry_delay = delay;
		exit_delay = delay;
		L_entry_delay = delay;
		L_exit_delay = delay;
		m_delay = delay;
		permanentDelay = permaDelay;
		newCycle();
	}

	void AnimationDelay::resetDelay() {
		m_delay = sf::Time::Zero;
		exit_delay = sf::Time::Zero;
		entry_delay = sf::Time::Zero;
		L_exit_delay = sf::Time::Zero;
		L_entry_delay = sf::Time::Zero;
		permanentDelay = false;
		newCycle();
	}
}