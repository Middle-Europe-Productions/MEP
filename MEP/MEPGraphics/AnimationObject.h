
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
//	Created by Piotr Skibiñski
//	Copyright © Middle Europe Productions. All rights reserved.
//
////////////////////////////////////////////////////////////

#pragma once
#include"AnimationBase.h"
#include"AnimationPosition.h"
#include"Following.h"
#include"Object.h"
namespace MEP {
	/**
	* \brief MEP::AnimationObject is a sprite with the ability to dislay an animation.
	*/
	class AnimationObject : public Animation, public Object, public Following {
	protected:
		//current sprite ready to bo rendered
		sf::Sprite currentSprite;
		void updateSprite();
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
	public:
		/**
		* Constructor of an animation.
		* @param[in] frameRate : Frame rate of an animation.
		* @param[in] x : Object with the animation frames.
		* @param[in] pos : Position of an animation.
		* @param[in] scale : Scale of an animation.
		*/
		AnimationObject(const float frameRate, const Object& x, sf::Vector2f pos = { 0.f, 0.f }, sf::Vector2f scale = { 1.f, 1.f }) :
			Animation(AnimationInit::ObjectAnimation, frameRate),
			Object(x),
			Following(pos, pos, scale, scale)
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
		AnimationObject(const Object& x, const AnimationObject& animation, sf::Vector2f pos = { 0.f, 0.f }, sf::Vector2f scale = { 1.f, 1.f }) :
			Animation(AnimationInit::Follow, animation.GetToWait()),
			Object(x),
			Following(FollowType::Objects, pos, pos, scale, scale),
			toFollowOBJ(&animation)
		{
			if (x.GetNufTextures() != animation.GetNufTextures())
				throw "[AnimationObject] Follow animation needs to have the same number of frames!";
			init();
		}
		/**
		* Sets the position
		* @param[in] pos : Possition.
		*/
		void SetPosition(const sf::Vector2f pos) override { m_pos = pos; m_posFixed = pos; updateSprite(); }
		/**
		* Sets the position
		* @param[in] x : MEP::Following object.
		*/
		void SetPosition(const Following& x) override { m_pos = x.GetOriginPosition(); m_posFixed = x.GetPosition(); updateSprite(); }
		/**
		* Sets the scale.
		* @param[in] scale : Scale.
		*/
		void SetScale(const sf::Vector2f scale) override { m_scale = scale; m_scaleFixed = scale; updateSprite(); }
		/**
		* Sets the scale.
		* @param[in] pos : MEP::Following object.
		*/
		void SetScale(const Following& x) override { m_scale = x.GetOriginScale(); m_scaleFixed = x.GetScale(); updateSprite(); }
		/**
		* Runs the animation in the forward direction.
		* @param[in] currentTime : Current global time.
		*/
		void RunForward(sf::Time& currentTime);
		/**
		* Runs the animation in the backward direction.
		* @param[in] currentTime : Current global time.
		*/
		void RunBackward(sf::Time& currentTime);
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
		bool IsActive() const override;
		/**
		* Checks if a given position is Transparent.
		* MEP::Objects of a button needs to have transparency initialized.
		* @return true - position is transparent, false - there is a pixel witout alpha channel > 200
		*/
		bool isTansparent(unsigned int x, unsigned int y) override;
		/**
		* Changes the color of a master sprite.
		* @param[in] color : Color.
		*/
		void SetColor(const sf::Color& color) { currentSprite.setColor(color); }
		/**
		* Outputs the color of a master sprite.
		* @return : Color.
		*/
		const sf::Color& GetColor() const { return currentSprite.getColor(); }
		/**
		* Outputs the animation object.
		* @return : MEP::AnimationObject.
		*/
		const AnimationObject& GetAnimationObject() { return *this; }
		~AnimationObject() = default;
	};

	void MEP::AnimationObject::updateSprite()
	{
		currentSprite.setTexture(**currentFrame);
		for (auto& x : followingList)
			x->CheckVariables(m_pos, m_posFixed, m_scale, m_scaleFixed);
		currentSprite.setPosition(m_posFixed);
		currentSprite.setScale(m_scaleFixed);
	}

	void MEP::AnimationObject::init()
	{
		currentFrame = texture.begin();
		updateSprite();
	}

	bool MEP::AnimationObject::correctObject(const Object& x)
	{
		return x.GetType() == ObjectType::Multi;
	}

	void MEP::AnimationObject::RunForward(sf::Time& currentTime)
	{
		Run(Direction::Forward, currentTime);
	}

	void MEP::AnimationObject::RunBackward(sf::Time& currentTime)
	{
		Run(Direction::Backwards, currentTime);
	}

	bool MEP::AnimationObject::draw(sf::RenderWindow& window)
	{
		if (isInit != AnimationInit::NotInit) {
			window.draw(currentSprite);
		}
		return true;
	}

	void MEP::AnimationObject::update(sf::Time& currentTime)
	{
		if (isRunning and (isInit == AnimationInit::ObjectAnimation)) {
			if (currentTime - updateTime >= toWait) {
				if (direction == Direction::Forward) {
					if (currentFrame == --texture.end()) {
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
					if (currentFrame == texture.begin()) {
						isRunning = false;
					}
				}
				updateTime = currentTime;
				updateSprite();
			}
		}
		if (isInit == AnimationInit::Follow) {
			if (toFollowOBJ->GetInit() != AnimationInit::Follow) {
				while (toFollowOBJ->index_currentFrame != index_currentFrame) {
					if (toFollowOBJ->index_currentFrame > index_currentFrame) {
						if (currentFrame == --texture.end()) {
							break;
						}
						index_currentFrame++;
						currentFrame++;
					}
					else {
						if (currentFrame == texture.begin()) {
							break;
						}
						index_currentFrame--;
						currentFrame--;
					}
				}
				if (toFollowOBJ->GetPosition() != GetPosition()) {
					m_posFixed = toFollowOBJ->GetPosition();
				}
				if (toFollowOBJ->GetScale() != GetScale()) {
					m_scaleFixed = toFollowOBJ->GetScale();
				}
				updateSprite();
			}
		}
		if (!followingList.empty()) {
			updateSprite();
		}
	}

	void MEP::AnimationObject::entryUpdate(sf::Time& currentTime)
	{
		if (m_tag == Animation::AdditionalTag::RunAtEntry or m_tag == Animation::AdditionalTag::RunAtEntryAndEnd)
			Run(Direction::Forward, currentTime);
		update(currentTime);
	}

	void MEP::AnimationObject::exitUpdate(sf::Time& currentTime)
	{
		if (m_tag == Animation::AdditionalTag::RunAtEnd or m_tag == Animation::AdditionalTag::RunAtEntryAndEnd)
			Run(Direction::Backwards, currentTime);
		update(currentTime);
	}

	bool MEP::AnimationObject::IsActive() const
	{
		return GetStatus() or isFollowerActive();
	}

	bool MEP::AnimationObject::isTansparent(unsigned int x, unsigned int y)
	{
		return false;
	}

	void MEP::AnimationObject::Follow::CheckVariables(sf::Vector2f& m_pos, sf::Vector2f& m_posFixed, sf::Vector2f& m_scale, sf::Vector2f& m_scaleFixed)
	{
		if (m_followType == FollowType::X_Pos) {
			m_posFixed.x = m_pos.x + m_animation.GetFixedVariable();
		}
		else if (m_followType == FollowType::Y_Pos) {
			m_posFixed.y = m_pos.y + m_animation.GetFixedVariable();
		}
		else if (m_followType == FollowType::X_Scale) {
			m_scaleFixed.x = m_scale.x + m_animation.GetFixedVariable();
			std::cout << m_scaleFixed.x;
		}
		else if (m_followType == FollowType::Y_Scale) {
			m_scaleFixed.y = m_scale.y + m_animation.GetFixedVariable();
		}
	}

}