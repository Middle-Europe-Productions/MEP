////////////////////////////////////////////////////////////
//
//	AnimationPosition.cpp created with the use of SFML
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
#include<MEPGraphics/AnimationPosition.h>

namespace MEP
{
	void AnimationPosition::init()
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

	void AnimationPosition::update(sf::Time& currentTime)
	{
		updatePositionAnimation(currentTime);
	}

	void AnimationPosition::updatePositionAnimation(sf::Time& currentTime) {
		if (isRunning) {
			if (updateDelay(currentTime) and isInit == AnimationInit::PositionAnimation) {
				if (currentTime - updateTime >= toWait) {
					if (direction == Direction::Forward) {
						if (currentFrame == --frames.end()) {
							isRunning = false;
							newCycle();
						}
						else {
							currentFrame++;
							current_frame++;
						}
					}
					else if (direction == Direction::Backwards) {
						if (currentFrame == frames.begin()) {
							isRunning = false;
							newCycle();
						}
						else {
							currentFrame--;
							current_frame--;
						}
					}
					updateTime = currentTime;
				}
			}
		}
	}

	AnimationPosition::AnimationPosition(const AnimationPosition& x) :
		Animation(x),
		m_function(x.m_function),
		nofFrames(x.nofFrames),
		frames(x.frames),
		currentFrame(frames.begin()),
		m_begin(x.m_begin),
		m_end(x.m_end),
		m_entry(x.m_entry),
		m_exit(x.m_exit)
	{}

	AnimationPosition::AnimationPosition(const double entry,
		const double exit,
		sf::Time length,
		const float frameRate,
		const double begin,
		const double end,
		std::function<double(double x)> function
	) :
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

	void AnimationPosition::run(const Direction direc, sf::Time currentTime) {
		direction = direc;
		updateTime = currentTime;
		isRunning = true;
	};

	const double& AnimationPosition::getFixedVariable() const {
		return *currentFrame;
	}

	unsigned int AnimationPosition::getFixedUintVariable() const {
		return (unsigned int)round(*currentFrame);
	}

	const double& AnimationPosition::getEntry() const {
		return m_entry;
	}

	const double& AnimationPosition::getExit() const {
		return m_exit;
	}

	bool AnimationPosition::draw(sf::RenderWindow&) {
		return true;
	}

	void AnimationPosition::entryUpdate(sf::Time& currentTime, bool low)
	{
		if (low) {
			if (m_tag & AdditionalTag::RunAtLowEntry) {
				changeState(State::LowEntry);
				run(Direction::Forward);
			}
		}
		else {
			if (m_tag & AdditionalTag::RunAtEntry) {
				changeState(State::Entry);
				run(Direction::Forward);
			}
		}
		update(currentTime);
	}

	void AnimationPosition::exitUpdate(sf::Time& currentTime, bool low)
	{
		if (low) {
			if (m_tag & AdditionalTag::RunAtLowEnd) {
				changeState(State::LowExit);
				run(Direction::Backwards);
			}
		}
		else {
			if (m_tag & AdditionalTag::RunAtEnd) {
				changeState(State::Exit);
				run(Direction::Backwards);
			}
		}
		update(currentTime);
	}

	bool AnimationPosition::AnimationPosition::isActive() const
	{
		return isRunning;
	}

	bool AnimationPosition::AnimationPosition::reset()
	{
		if (isRunning)
			return false;
		if (direction == Direction::Forward) {
			currentFrame = frames.begin();
			current_frame = 0;
		}
		else {
			currentFrame = --frames.end();
			current_frame = frames.size() - 1;
		}
		return true;
	}

	sf::Color AnimationPosition::getFrameAsColor() const {
		return sf::Color(std::round(*currentFrame));
	}
	void AnimationPosition::delayOutput(std::ostream& out) const {
		if (delay() != sf::Time::Zero)
			out << ", Delay: [" << delay().asSeconds() << "]";
	}

	void AnimationPosition::debugOutput(std::ostream& out) const {
		out << "MEP::AnimationPosition { Start: [" << m_entry
			<< "], End: [" << m_exit
			<< "], Current: [" << current_frame << "]";
		delayOutput(out);
		out << "}";
		animationDebug(out);
	}

	std::ostream& operator<<(std::ostream& out, const AnimationPosition& x) {
		x.debugOutput(out);
		return out;
	}

	AnimationPosition::~AnimationPosition() {
		notify();
	}
}