#ifndef ANIMATION_DELAY_H
#define ANIMATION_DELAY_H
#include<SFML/System/Time.hpp>

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
		bool updateDelay(const sf::Time& currentTime, sf::Time& delay, bool permanentDelay);
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
		const sf::Time& delay() const;
		/**
		* Updates the delay.
		*/
		bool updateDelay(const sf::Time& currentTime);
		/**
		* Creates a new cycle.
		*/
		void newCycle();
		/**
		* Changes the protected state of the delay.
		*/
		void changeState(State newState);
	public:
		/**
		* Sets the delay of an animation. Delay is a time to wait from starting the animation.
		* @param[in] delay: Delay to be applied on the animation.
		* @param[in] premaDelay: If false the delay will be applied once otherwise it will be applied always when run() is called.
		*/
		void setDelay(const sf::Time& delay, bool permaDelay = false);
		/**
		* Sets the delay of an animation then Entrance state. Delay is a time to wait from starting the animation.
		* @param[in] delay: Delay to be applied on the animation on Entrance.
		*/
		void setEntryDelay(const sf::Time& delay);
		/**
		* Sets the delay of an animation then Exit state. Delay is a time to wait from starting the animation.
		* @param[in] delay: Delay to be applied on the animation on Exit.
		*/
		void setExitDelay(const sf::Time& delay);
		/**
		* Sets the delay of an animation then Entrance state. Delay is a time to wait from starting the animation.
		* @param[in] delay: Delay to be applied on the animation on Entrance.
		*/
		void setLowEntryDelay(const sf::Time& delay);
		/**
		* Sets the delay of an animation then Exit state. Delay is a time to wait from starting the animation.
		* @param[in] delay: Delay to be applied on the animation on Exit.
		*/
		void setLowExitDelay(const sf::Time& delay);
		/**
		* Sets the delay of an animation in every state of the window. Delay is a time to wait from starting the animation.
		* @param[in] delay: Delay to be applied on the animation on every state.
		* @param[in] premaDelay: If false the delay will be applied once otherwise it will be applied always when run() is called (Only in Base state).
		*/
		void setGeneralDelay(const sf::Time& delay, bool permaDelay = false);
		/**
		* Resetes the delays.
		*/
		void resetDelay();
	};
}

#endif