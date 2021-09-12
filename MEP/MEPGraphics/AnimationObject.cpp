
////////////////////////////////////////////////////////////
//
//	AnimationObject.cpp created with the use of SFML
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
#include<MEPGraphics/AnimationObject.h>

namespace MEP
{
	AnimationObject::AnimationObject(const float frameRate,
		const Object& x,
		sf::Vector2f pos,
		sf::Vector2f scale) :
		Animation(AnimationInit::ObjectAnimation, frameRate),
		Object(x),
		Sprite(pos, scale)
	{
		if (!correctObject(x))
			throw "[AnimationObject] Incorrect object type!";
		init();
	}

	void AnimationObject::onResize() {
		if (getDrawTag() & DrawTag::Resize_Scale)
			updateScale();
		if (getDrawTag() & DrawTag::Resize_Pos)
			updatePosition();
		if (getDrawTag() & DrawTag::Resize_Rect)
			updateRect();
	}

	const sf::Vector2u& AnimationObject::getSize() const {
		return fixSize;
	};

	void AnimationObject::setScale(const sf::Vector2f& scale) {
		m_scale = scale;
		m_scaleFixed = scale;
		currentSprite.setScale(m_scaleFixed);
		updateSprite();
		updateSize();
	}

	void AnimationObject::setScale(const Following& x) {
		m_scale = x.getOriginScale();
		m_scaleFixed = x.getScale();
		currentSprite.setScale(m_scaleFixed);
		updateSprite();
		updateSize();
	}

	void AnimationObject::updateSize() {
		fixSize = { (unsigned int)(m_size.x * m_scale.x), (unsigned int)(m_size.y * m_scale.y) };
	}

	void AnimationObject::init()
	{
		currentFrame = texture->begin();
		currentSprite.setPosition(m_posFixed);
		currentSprite.setScale(m_scaleFixed);
		updateSprite(**currentFrame);
		updateSize();
	}

	bool AnimationObject::correctObject(const Object& x)
	{
		return x.getType() == ObjectType::Multi;
	}

	void AnimationObject::runForward(sf::Time& currentTime)
	{
		run(Direction::Forward, currentTime);
	}

	void AnimationObject::runBackward(sf::Time& currentTime)
	{
		run(Direction::Backwards, currentTime);
	}

	bool AnimationObject::draw(sf::RenderWindow& window)
	{
		if (isInit != AnimationInit::NotInit) {
			window.draw(currentSprite);
		}
		return true;
	}

	void AnimationObject::update(sf::Time& currentTime)
	{
		if (isRunning) {
			if (updateDelay(currentTime) and isInit == AnimationInit::ObjectAnimation) {
				if (currentTime - updateTime >= toWait) {
					if (direction == Direction::Forward) {
						if (currentFrame == --texture->end()) {
							isRunning = false;
							newCycle();
						}
						else {
							currentFrame++;
							index_currentFrame++;
						}
					}
					else if (direction == Direction::Backwards) {
						currentFrame--;
						index_currentFrame++;
						if (currentFrame == texture->begin()) {
							isRunning = false;
							newCycle();
						}
					}
					updateTime = currentTime;
					updateSprite(**currentFrame);
				}
			}
		}
		if (followingListv2._size() != 0) {
			updateSprite();
		}
	}

	void AnimationObject::entryUpdate(sf::Time& currentTime, bool low)
	{
		if (low) {
			if (m_tag & AdditionalTag::RunAtLowEntry) {
				changeState(State::LowEntry);
				run(Direction::Backwards, currentTime);
			}
		}
		else {
			if (m_tag & AdditionalTag::RunAtEntry) {
				changeState(State::Entry);
				run(Direction::Backwards, currentTime);
			}
		}
		update(currentTime);
	}

	void AnimationObject::exitUpdate(sf::Time& currentTime, bool low)
	{
		if (low) {
			if (m_tag & AdditionalTag::RunAtLowEnd) {
				changeState(State::LowExit);
				run(Direction::Backwards, currentTime);
			}
		}
		else {
			if (m_tag & AdditionalTag::RunAtEnd) {
				changeState(State::Exit);
				run(Direction::Backwards, currentTime);
			}
		}
		update(currentTime);
	}

	bool AnimationObject::isActive() const
	{
		return isRunning or isFollowerActive();
	}

	bool AnimationObject::isTansparent(unsigned int, unsigned int)
	{
		return false;
	}

	const AnimationObject& AnimationObject::getAnimationObject()
	{
		return *this;
	}

	void AnimationObject::debugOutput(std::ostream& out) const {
		out << "MEP::AnimationObject, Following:" << std::endl;
		followingDebug(out, "  ");
		out << "   \\MEP::Object, ID: " << getID() << ", name : " << getName() << std::endl;
		out << "     \\";
		drawTagDebug(out);
	}

	std::ostream& operator<<(std::ostream& out, const AnimationObject& x) {
		x.debugOutput(out);
		return out;
	}
}