
////////////////////////////////////////////////////////////
//
//	AnimationObject.h created with the use of SFML
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
//	Created by Piotr Skibi�ski
//	Copyright � Middle Europe Productions. All rights reserved.
//
////////////////////////////////////////////////////////////

#ifndef MEP_ANIMATION_OBJECT_H
#define MEP_ANIMATION_OBJECT_H

#include<MEPGraphics/AnimationBase.h>
#include<MEPGraphics/AnimationPosition.h>
#include<MEPGraphics/Sprite.h>
#include<MEPGraphics/Object.h>
namespace MEP {
	/**
	* \brief MEP::AnimationObject is a sprite with the ability to dislay an animation.
	*/
	class AnimationObject : public Animation, public Object, public Sprite {
	protected:
		//pointer to a current frame
		std::list<sf::Texture*>::iterator currentFrame;
		//index of a currently displayed sprite is a table of the frames
		unsigned int index_currentFrame = 0;
		//initialization
		void init();
		//checks the corretness of given object
		bool correctObject(const Object& x);
		//object which we are going to follow
		const AnimationObject* toFollowOBJ = nullptr;	
		//holds the actual size
		sf::Vector2u fixSize;
		//updates the actual size
		void updateSize() {
			fixSize = { (unsigned int)(m_size.x * m_scale.x), (unsigned int)(m_size.y * m_scale.y) };
		}
	public:
		/**
		* Constructor of an animation.
		* @param[in] frameRate : Frame rate of an animation.
		* @param[in] x : Object with the animation frames.
		* @param[in] pos : Position of an animation.
		* @param[in] scale : Scale of an animation.
		*/
		AnimationObject(const float frameRate, 
			const Object& x, 
			sf::Vector2f pos = { 0.f, 0.f }, 
			sf::Vector2f scale = { 1.f, 1.f }) :
			Animation(AnimationInit::ObjectAnimation, frameRate),
			Object(x),
			Sprite(pos, scale)
		{
			if (!correctObject(x))
				throw "[AnimationObject] Incorrect object type!";
			init();
		}
		/**
		* Constructor of an animation.
		* @param[in] x : Object with the animation frames.
		* @param[in] animation : Different instance of the animation whose movement will be followed.
		* @param[in] pos : Position of an animation.
		* @param[in] scale : Scale of an animation.
		*/
		AnimationObject(const Object& x, 
			const AnimationObject& animation, 
			sf::Vector2f pos = { 0.f, 0.f }, 
			sf::Vector2f scale = { 1.f, 1.f }) :
			Animation(AnimationInit::Follow, animation.getToWait()),
			Object(x),
			Sprite(FollowType::Objects, pos, scale),
			toFollowOBJ(&animation)
		{
			if (x.getNufTextures() != animation.getNufTextures())
				throw "[AnimationObject] Follow animation needs to have the same number of frames!";
			init();
		}
		/**
		* On resize we want to update the position.
		*/
		void onResize() override {
			if (getDrawTag() & DrawTag::Resize_Scale)
				updateScale();
			if (getDrawTag() & DrawTag::Resize_Pos)
				updatePosition();
			if (getDrawTag() & DrawTag::Resize_Rect)
				updateRect();
		}
		/**
		* Outputs the size of a master MEP::Object
		* @return sf:Vector2u size.
		*/
		virtual const sf::Vector2u& getSize() const {
			return fixSize;
		};
		/**
		* Sets the scale.
		* @param[in] scale : Scale.
		*/
		void setScale(const sf::Vector2f scale) override {
			m_scale = scale;
			m_scaleFixed = scale;
			currentSprite.setScale(m_scaleFixed);
			updateSprite();
			updateSize();
		}
		/**
		* Sets the scale.
		* @param[in] pos : MEP::Following object.
		*/
		void setScale(const Following& x) override {
			m_scale = x.getOriginScale();
			m_scaleFixed = x.getScale();
			currentSprite.setScale(m_scaleFixed);
			updateSprite();
			updateSize();
		}
		/**
		* Runs the animation in the forward direction.
		* @param[in] currentTime : Current global time.
		*/
		void runForward(sf::Time& currentTime);
		/**
		* Runs the animation in the backward direction.
		* @param[in] currentTime : Current global time.
		*/
		void runBackward(sf::Time& currentTime);
		/**
		* Override of a MEP::Drawable draw.
		*/
		bool draw(sf::RenderWindow& window) override;
		/**
		* Override of a MEP::Drawable update.
		*/
		void update(sf::Time& currentTime) override;
		/**
		* Override of a MEP::Drawable entryUpdate.
		*/
		void entryUpdate(sf::Time& currentTime) override;
		/**
		* Override of a MEP::Drawable exitUpdate.
		*/
		void exitUpdate(sf::Time& currentTime) override;
		/**
		* Outputs the activation status of an animation.
		* @return True - active, False - unactive
		*/
		bool isActive() const override;
		/**
		* Checks if a given position is Transparent.
		* MEP::Objects of a button needs to have transparency initialized.
		* @return true - position is transparent, false - there is a pixel witout alpha channel > 200
		*/
		bool isTansparent(unsigned int x, unsigned int y) override;
		/**
		* Outputs the animation object.
		* @return : MEP::AnimationObject.
		*/
		const AnimationObject& getAnimationObject() { return *this; }
		/**
		* Debug output of the class.
		*/
		virtual void debugOutput(std::ostream& out) const {
			out << "MEP::AnimationObject, Following:" << std::endl;
			followingDebug(out, "  ");
			out << "   \\MEP::Object, ID: " << getID() << ", name : " << getName() << std::endl;
			out << "     \\";
			drawTagDebug(out);
		}
		/**
		* Overrdie of the << operator for diagnostic purposes.
		*/
		friend std::ostream& operator<<(std::ostream& out, const AnimationObject& x) {
			x.debugOutput(out);
			return out;
		}
		virtual ~AnimationObject() = default;
	};

	inline void MEP::AnimationObject::init()
	{
		currentFrame = texture->begin();
		currentSprite.setPosition(m_posFixed);
		currentSprite.setScale(m_scaleFixed);
		updateSprite(**currentFrame);
		updateSize();
	}

	inline bool MEP::AnimationObject::correctObject(const Object& x)
	{
		return x.getType() == ObjectType::Multi;
	}

	inline void MEP::AnimationObject::runForward(sf::Time& currentTime)
	{
		run(Direction::Forward, currentTime);
	}

	inline void MEP::AnimationObject::runBackward(sf::Time& currentTime)
	{
		run(Direction::Backwards, currentTime);
	}

	inline bool MEP::AnimationObject::draw(sf::RenderWindow& window)
	{
		if (isInit != AnimationInit::NotInit) {
			window.draw(currentSprite);
		}
		return true;
	}

	inline void MEP::AnimationObject::update(sf::Time& currentTime)
	{
		if (isRunning and (isInit == AnimationInit::ObjectAnimation)) {
			if (currentTime - updateTime >= toWait) {
				if (direction == Direction::Forward) {
					if (currentFrame == --texture->end()) {
						isRunning = false;
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
					}
				}
				updateTime = currentTime;
				updateSprite(**currentFrame);
			}
		}
		if (isInit == AnimationInit::Follow) {
			if (toFollowOBJ->getInit() != AnimationInit::Follow) {
				while (toFollowOBJ->index_currentFrame != index_currentFrame) {
					if (toFollowOBJ->index_currentFrame > index_currentFrame) {
						if (currentFrame == --texture->end()) {
							break;
						}
						index_currentFrame++;
						currentFrame++;
					}
					else {
						if (currentFrame == texture->begin()) {
							break;
						}
						index_currentFrame--;
						currentFrame--;
					}
				}
				if (toFollowOBJ->getPosition() != getPosition()) {
					m_posFixed = toFollowOBJ->getPosition();
				}
				if (toFollowOBJ->getScale() != getScale()) {
					m_scaleFixed = toFollowOBJ->getScale();
				}
				updateSprite(**currentFrame);
			}
		}
		if (followingListv2._size() != 0) {
			updateSprite();
		}
	}

	inline void MEP::AnimationObject::entryUpdate(sf::Time& currentTime)
	{
		if (m_tag == Animation::AdditionalTag::RunAtEntry or m_tag == Animation::AdditionalTag::RunAtEntryAndEnd)
			run(Direction::Forward, currentTime);
		update(currentTime);
	}

	inline void MEP::AnimationObject::exitUpdate(sf::Time& currentTime)
	{
		if (m_tag == Animation::AdditionalTag::RunAtEnd or m_tag == Animation::AdditionalTag::RunAtEntryAndEnd)
			run(Direction::Backwards, currentTime);
		update(currentTime);
	}

	inline bool MEP::AnimationObject::isActive() const
	{
		return isRunning or isFollowerActive();
	}

	inline bool MEP::AnimationObject::isTansparent(unsigned int, unsigned int)
	{
		return false;
	}

}
#endif
