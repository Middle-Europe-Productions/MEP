
////////////////////////////////////////////////////////////
//
//	AnimationPossition.h created with the use of SFML
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

#pragma once
#include<functional>
#include<list>
#include<iostream>
#include"AnimationBase.h"
#include"Drawable.h"
namespace MEP {
	class AnimationPossition : public Drawable, public Animation {
	private:
		std::function<double(double x)> m_function;
		//all frames information
		unsigned int nofFrames;
		std::list<double> frames;
		std::list<double>::iterator currentFrame;

		unsigned int current_frame = 0;
		//begin and end on a graph
		const double m_begin = 0;
		const double m_end = 0;
		//possition
		double m_entry = 0;
		double m_exit = 0;
		void init();
		//run with the delay
		sf::Time m_delay = sf::Time::Zero;
		bool delayInit = false;
	public:
		AnimationPossition() = default;
		AnimationPossition(const AnimationPossition& x) :
			Animation(x),
			m_function(x.m_function),
			nofFrames(x.nofFrames),
			frames(x.frames),
			currentFrame(frames.begin()),
			m_begin(x.m_begin),
			m_end(x.m_end),
			m_entry(x.m_entry),
			m_exit(x.m_exit) {}
		template<class Function>
		AnimationPossition(const float frameRate, const double begin, const double end, const double entry, const double exit, sf::Time lenght, Function fun) :
			Animation(AnimationInit::PossitionAnimation, sf::Time(sf::milliseconds(1000) / frameRate)),
			m_function(fun),
			nofFrames(lenght / toWait),
			m_begin(begin),
			m_end(end),
			m_entry(entry),
			m_exit(exit)
		{
			init();
			if (nofFrames <= 0 or end - begin <= 0)
				throw "[AnimationPossition] Number of frames lower then zero! Check entry variables!";
			if (end - begin <= 0)
				throw "[AnimationPossition] end point needs to be grater than begin point";
		}
		void SetDelay(const sf::Time& delay, const Direction& dir = Direction::Backwards);
		const float GetFixedVariable() const { return *currentFrame; }
		void draw(sf::RenderWindow& window) override {}
		void update(sf::Time& currentTime) override;
		void entryUpdate(sf::Time& currentTime) override;
		void exitUpdate(sf::Time& currentTime) override;
		//returns activity of an object it is mainly related to the associated animations
		bool IsActive() const override;
		~AnimationPossition() = default;
	};
	void MEP::AnimationPossition::init()
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
		for (auto& x : frames) {
			std::cout << x << std::endl;
		}
		currentFrame = frames.begin();
	}

	void MEP::AnimationPossition::SetDelay(const sf::Time& delay, const Direction& dir)
	{
		if (isRunning)
			throw "[AnimationPossition]You cannot delay running animation!";
		m_delay = delay;
		direction = dir;
	}

	void MEP::AnimationPossition::update(sf::Time& currentTime)
	{
		if (isRunning and (isInit == AnimationInit::PossitionAnimation)) {
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
				Run(direction);
				m_delay = sf::Time::Zero;
				delayInit = false;
			}
		}
	}

	void MEP::AnimationPossition::entryUpdate(sf::Time& currentTime)
	{
		if (m_tag == Animation::AdditionalTag::RunAtEntry or m_tag == Animation::AdditionalTag::RunAtEntryAndEnd)
			Run(Direction::Forward);
		update(currentTime);
	}

	void MEP::AnimationPossition::exitUpdate(sf::Time& currentTime)
	{
		if (m_tag == Animation::AdditionalTag::RunAtEnd or m_tag == Animation::AdditionalTag::RunAtEntryAndEnd)
			Run(Direction::Backwards);
		update(currentTime);

	}

	bool MEP::AnimationPossition::IsActive() const
	{
		return GetStatus();
	}

};
