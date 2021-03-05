
////////////////////////////////////////////////////////////
//
//	AnimationPosition.h created with the use of SFML
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
#ifndef MEP_ANIMATION_POSITION_H
#define MEP_ANIMATION_POSITION_H

#include<functional>
#include<list>
#include<iostream>
#include<cmath>
#include<MEPGraphics/AnimationBase.h>
#include<MEPGraphics/Drawable.h>
namespace MEP {
	/**
	* The idea here is simple. We take a function f.
	* Then min(<f(begin), ..., f(end)>) where min is a minimal value. Becomes our entry position.
	* And max(<f(begin), ..., f(end)>) where max is a maximal value. Becomes our exit position.
	* Please keep in mind that f(begin) and minimal value are 2 seperate things, but of course f(begin) can be equal to minimal value.
	* After all of that we generate points according to the given framerate and animation lenght.
	* \brief MEP::AnimationPosition provides a basic implementation of a modification of the position.
	*/
	class AnimationPosition : public Drawable, public Animation {
	protected:
		std::function<double(double x)> m_function;
		//all frames information
		unsigned int nofFrames;
		std::list<double> frames;
		std::list<double>::iterator currentFrame;

		unsigned int current_frame = 0;
		//begin and end on a graph
		const double m_begin = 0;
		const double m_end = 0;
		//position
		double m_entry = 0;
		double m_exit = 0;
		void init();
		//run with the delay
		sf::Time m_delay = sf::Time::Zero;
		bool delayInit = false;
		/**
		* Core updates for position animation.
		* This method is needed in order to avoid CTRL-C/V.
		*/
		void updatePositionAnimation(sf::Time& currentTime);
	public:
		AnimationPosition() = default;
		/**
		* Vopy constructor of an animation.
		* @param[in] x : MEP::AnimationPosition object
		*/
		AnimationPosition(const AnimationPosition& x) :
			Animation(x),
			m_function(x.m_function),
			nofFrames(x.nofFrames),
			frames(x.frames),
			currentFrame(frames.begin()),
			m_begin(x.m_begin),
			m_end(x.m_end),
			m_entry(x.m_entry),
			m_exit(x.m_exit) {}
		/**
		* Contructor of an animation. It is taking a part of a from f(begin) to f(end) then calculation the position accoring to the formula.
		* Fmax(F(begin), F(end)) = exit, and Fmin(F(begin), F(end) = min.
		* @param[in] begin : Begining point on a graph,
		* @param[in] end : End point of a graph.
		* @param[in] length : Animation lenght in ms.
		* @param[in] frameRate : Frame rate of an animation.
		* @param[in] entry : Entry position of an Object (before the animation)
		* @param[in] exit : Exit position of an Object (after the animation)
		* @param[in] fun : Function graph. Method with the return type double. 
		*/
		AnimationPosition(const double entry, const double exit, sf::Time length, const float frameRate = 120, const double begin = 0, const double end = 100, std::function<double(double x)> function = [](double x)->double{ return x; }) :
			Animation(AnimationInit::PositionAnimation, sf::Time(sf::milliseconds(1000) / frameRate)),
			m_function(function),
			nofFrames(length / toWait),
			m_begin(begin),
			m_end(end),
			m_entry(entry),
			m_exit(exit)
		{
			init();
			if (nofFrames <= 0 or end - begin <= 0)
				throw "[AnimationPosition] Number of frames lower then zero! Check entry variables!";
			if (end - begin <= 0)
				throw "[AnimationPosition] end point needs to be grater than begin point";
		}
		/**
		* Sets the delay of an animation. Delay is a time to wait from starting the animation.
		*/
		void setDelay(const sf::Time& delay, const Direction& dir = Direction::Backwards);
		/**
		* Outputs the current position of an animation.
		* @return Current position.
		*/
		const double& GetFixedVariable() const { return *currentFrame; }
		/**
		* Outputs the current position of an animation.
		* @return Current position as unsigned int.
		*/
		unsigned int GetFixedUintVariable() const { 
			return (unsigned int)round(*currentFrame); 
		}
		/**
		* Outputs the entry position of an animation.
		* @return Entry position.
		*/
		const double& getEntry() const { return m_entry; }
		/**
		* Outputs the exit position of an animation.
		* @return Exit position.
		*/
		const double& getExit() const { return m_exit; }
		/**
		* Override of a MEP::Drawable draw.
		*/
		bool draw(sf::RenderWindow&) override { return true; }
		/**
		* Override of a MEP::Drawable update.
		*/
		virtual void update(sf::Time& currentTime);
		/**
		* Override of a MEP::Drawable entryUpdate.
		*/
		void entryUpdate(sf::Time& currentTime) override;
		/**
		* Override of a MEP::Drawable exitUpate.
		*/
		void exitUpdate(sf::Time& currentTime) override;
		/**
		* Outputs the activation status of an animation.
		* @return True - active, False - unactive
		*/
		bool isActive() const override;
		/**
		* Resets the parameters of the animation if the animation is not active.
		* Reset means changing it's current frame to begin or end depending of the direction.
		* If direction is forward changes to begin otherwise to end.
		*/
		bool reset();
		/**
		* Outputs the current frame as a Color
		* *Warning* For color animation it is recommended to use MEP::AnimationColor
		* @return : sf::Color
		*/
		virtual sf::Color getFrameAsColor() const { 
			return sf::Color(std::round(*currentFrame)); 
		}
		virtual ~AnimationPosition() {
			notify();
		}
	};
	inline void MEP::AnimationPosition::init()
	{
		double jump = (m_end - m_begin) / nofFrames;
		double min = sizeof(double), max = 0;
		for (double x = m_begin; x < m_end; x += jump) {
			frames.push_back(m_function(x));
			if (frames.back() > max)
				max = frames.back();
			if (frames.back() < min)
				min = frames.back();
		}
		if (min < 0)
			for (auto& x : frames)
				x += abs(min);
		double multiplication = (m_exit - m_entry) / (max - min);
		for (auto& x : frames) {
			x = (m_entry + ((x)*multiplication));
		}
		currentFrame = frames.begin();
	}

	inline void MEP::AnimationPosition::setDelay(const sf::Time& delay, const Direction& dir)
	{
		if (isRunning)
			throw "[AnimationPosition]You cannot delay running animation!";
		m_delay = delay;
		direction = dir;
	}

	inline void MEP::AnimationPosition::update(sf::Time& currentTime)
	{
		updatePositionAnimation(currentTime);
	}
	/**
	* Core updates for position animation.
	* This method is needed in order to avoid CTRL-C/V.
	*/
	inline void MEP::AnimationPosition::updatePositionAnimation(sf::Time& currentTime) {
		if (isRunning and (isInit == AnimationInit::PositionAnimation)) {
			if (currentTime - updateTime >= toWait) {
				if (direction == Direction::Forward) {
					if (currentFrame == --frames.end()) {
						isRunning = false;
					}
					else {
						currentFrame++;
						current_frame++;
					}
				}
				else if (direction == Direction::Backwards) {
					if (currentFrame == frames.begin()) {
						isRunning = false;
					}
					else {
						currentFrame--;
						current_frame--;
					}
				}
				updateTime = currentTime;
			}
		}
		else if (m_delay != sf::Time::Zero) {
			if (!delayInit) {
				updateTime = currentTime;
				delayInit = true;
			}
			else if (currentTime - updateTime > m_delay) {
				run(direction);
				m_delay = sf::Time::Zero;
				delayInit = false;
			}
		}
	}
	inline void MEP::AnimationPosition::entryUpdate(sf::Time& currentTime)
	{
		if (m_tag == Animation::AdditionalTag::RunAtEntry or m_tag == Animation::AdditionalTag::RunAtEntryAndEnd)
			run(Direction::Forward);
		update(currentTime);
	}

	inline void MEP::AnimationPosition::exitUpdate(sf::Time& currentTime)
	{
		if (m_tag == Animation::AdditionalTag::RunAtEnd or m_tag == Animation::AdditionalTag::RunAtEntryAndEnd)
			run(Direction::Backwards);
		update(currentTime);
	}

	inline bool MEP::AnimationPosition::isActive() const
	{
		return getStatus();
	}

	inline bool AnimationPosition::reset()
	{
		if(isRunning)
			return false;
		if (direction == Direction::Forward) {
			currentFrame = frames.begin();
			current_frame = 0;
		}
		else {
			currentFrame = --frames.end();
			current_frame = frames.size()-1;
		}
		return true;
	}

};

#endif
