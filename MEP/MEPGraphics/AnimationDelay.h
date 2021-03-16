#ifndef ANIMATION_DELAY_H
#define ANIMATION_DELAY_H

namespace MEPtools {
	class AnimationDelay {
		/**
		* Delay of the aniamtion.
		*/
		sf::Time m_delay = sf::Time::Zero;
		sf::Time exit_delay = sf::Time::Zero;
		sf::Time entry_delay = sf::Time::Zero;
		sf::Time L_exit_delay = sf::Time::Zero;
		sf::Time L_entry_delay = sf::Time::Zero;
		/**
		* Local update time
		*/
		sf::Time updateTime = sf::Time::Zero;
		/**
		* Is delay permanent.
		*/
		bool permanentDelay = false;
		/**
		* Delay cycle.
		*/
		bool cycleDone = false;
		/**
		* Local delay update.
		*/
		bool updateDelay(const sf::Time& currentTime, sf::Time& delay, bool permanentDelay) {
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
	protected:
		enum class State {
			Entry,
			Exit,
			Base,
			LowExit,
			LowEntry
		};
		/**
		* Delay state.
		*/
		State state = State::Base;
		/**
		* Outputs the delay.
		*/
		const sf::Time& delay() const {
			return m_delay;
		}
		/**
		* Updates the delay.
		*/
		bool updateDelay(const sf::Time& currentTime) {
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
		/**
		* Creates a new cycle.
		*/
		void newCycle() {
			cycleDone = false;
			updateTime = sf::Time::Zero;
		}
		/**
		* Changes the protected state of the delay.
		*/
		void changeState(State newState) {
			state = newState;
		}
	public:
		/**
		* Sets the delay of an animation. Delay is a time to wait from starting the animation.
		* @param[in] delay: Delay to be applied on the animation.
		* @param[in] premaDelay: If false the delay will be applied once otherwise it will be applied always when run() is called.
		*/
		void setDelay(const sf::Time& delay, bool permaDelay = false) {
			m_delay = delay;
			permanentDelay = permaDelay;
			newCycle();
		}
		/**
		* Sets the delay of an animation then Entrance state. Delay is a time to wait from starting the animation.
		* @param[in] delay: Delay to be applied on the animation on Entrance.
		*/
		void setEntryDelay(const sf::Time& delay) {
			entry_delay = delay;
			newCycle();
		}
		/**
		* Sets the delay of an animation then Exit state. Delay is a time to wait from starting the animation.
		* @param[in] delay: Delay to be applied on the animation on Exit.
		*/
		void setExitDelay(const sf::Time& delay) {
			exit_delay = delay;
			newCycle();
		}
		/**
		* Sets the delay of an animation then Entrance state. Delay is a time to wait from starting the animation.
		* @param[in] delay: Delay to be applied on the animation on Entrance.
		*/
		void setLowEntryDelay(const sf::Time& delay) {
			L_entry_delay = delay;
			newCycle();
		}
		/**
		* Sets the delay of an animation then Exit state. Delay is a time to wait from starting the animation.
		* @param[in] delay: Delay to be applied on the animation on Exit.
		*/
		void setLowExitDelay(const sf::Time& delay) {
			L_exit_delay = delay;
			newCycle();
		}
		/**
		* Sets the delay of an animation in every state of the window. Delay is a time to wait from starting the animation.
		* @param[in] delay: Delay to be applied on the animation on every state.
		* @param[in] premaDelay: If false the delay will be applied once otherwise it will be applied always when run() is called (Only in Base state).
		*/
		void setGeneralDelay(const sf::Time& delay, bool permaDelay = false) {
			entry_delay = delay;
			exit_delay = delay;
			L_entry_delay = delay;
			L_exit_delay = delay;
			m_delay = delay;
			permanentDelay = permaDelay;
			newCycle();
		}
		/**
		* Resetes the delays.
		*/
		void resetDelay() {
			m_delay = sf::Time::Zero;
			exit_delay = sf::Time::Zero;
			entry_delay = sf::Time::Zero;
			L_exit_delay = sf::Time::Zero;
			L_entry_delay = sf::Time::Zero;
			permanentDelay = false; 
			newCycle();
		}
	};
}

#endif