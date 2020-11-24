
////////////////////////////////////////////////////////////
//
//	Following.h created with the use of SFML
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

#pragma once
#include"AnimationPosition.h"
#include"AnimationColor.h"
namespace MEP {
	/**
	* \brief MEP::Following keeps track of a MEP::Object position.
	*/
	class Following {
	public:
		/**
		* @enum MEP::Button::FollowType
		* Types of the following.
		*/
		enum class FollowType {
			/** Following not initialized.*/
			NotInit,
			/** Following other Objects.*/
			Objects,
			/** Following with a change of X scale*/
			X_Scale,
			/** Following with a change of Y scale*/
			Y_Scale,
			/** Following with a change of X position*/
			X_Pos,
			/** Following with a change of Y position*/
			Y_Pos,
			/** Following with a change of a color.*/
			Color
		};
	private:		
		//type of a following
		FollowType m_followType = FollowType::NotInit;
		struct Follow {
			const AnimationPosition& m_animation;
			FollowType m_followType = FollowType::NotInit;
			Follow(const AnimationPosition& animation, FollowType followType = FollowType::NotInit) :
				m_animation(animation),
				m_followType(followType) {}
			void updateVariables(Following& object, sf::Sprite& toUpdate) {
				if (m_followType == FollowType::X_Pos) {
					object.m_posFixed.x = object.m_pos.x + m_animation.GetFixedVariable();
					toUpdate.setPosition(object.m_posFixed);
				}
				else if (m_followType == FollowType::Y_Pos) {
					object.m_posFixed.y = object.m_pos.y + m_animation.GetFixedVariable();
					toUpdate.setPosition(object.m_posFixed);
				}
				else if (m_followType == FollowType::X_Scale) {
					object.m_scaleFixed.x = object.m_scale.x + m_animation.GetFixedVariable();
					toUpdate.setScale(object.m_scaleFixed);
				}
				else if (m_followType == FollowType::Y_Scale) {
					object.m_scaleFixed.y = object.m_scale.y + m_animation.GetFixedVariable();
					toUpdate.setScale(object.m_scaleFixed);
				}
				else if (m_followType == FollowType::Color) {
					toUpdate.setColor(m_animation.getFrameAsColor());
				}
			}
			void updateVariables(Following& object) {
				if (m_followType == FollowType::X_Pos) {
					object.m_posFixed.x = object.m_pos.x + m_animation.GetFixedVariable();
				}
				else if (m_followType == FollowType::Y_Pos) {
					object.m_posFixed.y = object.m_pos.y + m_animation.GetFixedVariable();
				}
				else if (m_followType == FollowType::X_Scale) {
					object.m_scaleFixed.x = object.m_scale.x + m_animation.GetFixedVariable();
				}
				else if (m_followType == FollowType::Y_Scale) {
					object.m_scaleFixed.y = object.m_scale.y + m_animation.GetFixedVariable();
				}
				else if (m_followType == FollowType::Color) {
					object.setColor(m_animation.getFrameAsColor());
				}
			}
		};
	protected:
		std::list<std::unique_ptr<Follow>> followingList;
		//texture position and scale
		sf::Vector2f m_pos = {0.f, 0.f};
		sf::Vector2f m_posFixed = { 0.f, 0.f };
		sf::Vector2f m_scale = { 1.f, 1.f };
		sf::Vector2f m_scaleFixed = { 1.f, 1.f };
		sf::Color m_color;
		sf::Color m_colorFixed;
	public:
		/**
		* Constructor of a following type.
		* @param[in] followType : MEP::Following::FollowType type of an animation.
		* @param[in] pos : Position of the follower.
		* @param[in] posFixed : Fixed position of the follower.
		* @param[in] scale : Scale of the follower.
		* @param[in] scaleFixed : Fixed scale of the follower.
		*/
		Following(const FollowType& followType,
			sf::Vector2f pos = { 0.f, 0.f },
			sf::Vector2f posFixed = { 0.f, 0.f }, 
			sf::Vector2f scale = { 1.f, 1.f }, 
			sf::Vector2f scaleFixed = { 1.f, 1.f }) : 
			m_followType(followType), 
			m_pos(pos), 
			m_posFixed(posFixed), 
			m_scale(scale), 
			m_scaleFixed(scaleFixed)
		{};
		/**
		* Constructor of a following type.
		* @param[in] pos : Position of the follower.
		* @param[in] posFixed : Fixed position of the follower.
		* @param[in] scale : Scale of the follower.
		* @param[in] scaleFixed : Fixed scale of the follower.
		*/
		Following(sf::Vector2f pos = { 0.f, 0.f },
			sf::Vector2f posFixed = { 0.f, 0.f },
			sf::Vector2f scale = { 1.f, 1.f },
			sf::Vector2f scaleFixed = { 1.f, 1.f }) :
			m_pos(pos),
			m_posFixed(posFixed),
			m_scale(scale),
			m_scaleFixed(scaleFixed)
		{};
		/**
		* Warning list of the following objects is indivdual for every object.
		* **Copy constructor does not copy them.**
		* Copy constructor copy position, scale and color.
		* @param[in] x : Another MEP::Following instance.
		*/
		Following(const Following& x) :
			m_pos(x.m_pos),
			m_posFixed(x.m_posFixed),
			m_scale(x.m_scale),
			m_scaleFixed(x.m_scaleFixed),
			m_color(x.m_color),
			m_colorFixed(x.m_colorFixed)
		{};
		/**
		* Warning list of the following objects is indivdual for every object.
		* **Assign operator does not copy them.**
		* Assign operator copy position, scale and color.
		* @param[in] x : Another MEP::Following instance.
		*/
		Following& operator<<(const Following& x) {
			if (this != &x) {
				m_pos = x.m_pos;
				m_posFixed = x.m_posFixed;
				m_scale = x.m_scale;
				m_scaleFixed = x.m_scaleFixed;
				m_color = x.m_color;
				m_colorFixed = x.m_colorFixed;
			}
			return *this;
		}
		/**
		* Sets the object to follow using another MEP::AnimationPosition instance.
		* @param[in] base : MEP::AnimationPosition object to follow.
		* @param[in] type : Type of a follow.
		*/
		void setFollow(const AnimationPosition& base, const FollowType type) {
			for (auto& x : followingList)
				if (type == x->m_followType)
					throw "This type of follow already exists!";
			followingList.push_back(std::make_unique<Follow>(base, type));
		}
		/**
		* Sets the object to follow using another MEP::AnimationColor instance.
		* @param[in] base : MEP::AnimationPosition object to follow.
		* @param[in] type : Type of a follow.
		*/
		void setFollow(const AnimationColor& base) {
			for (auto& x : followingList)
				if (FollowType::Color == x->m_followType)
					throw "This type of follow already exists!";
			followingList.push_back(std::make_unique<Follow>(base, MEP::Following::FollowType::Color));
		}
		/**
		* Sets the position and fixed position of an MEP::Following.
		* @param[in] pos : Position.
		*/
		virtual void setPosition(const sf::Vector2f pos) { 
			m_pos = pos; 
			m_posFixed = pos; 
		}
		/**
		* Sets the position and fixed position of an MEP::Following.
		* @param[in] x : MEP::Following object.
		*/
		virtual void setPosition(const Following& x) { 
			m_pos = x.m_pos; 
			m_posFixed = x.m_posFixed; 
		}
		/**
		* Moves the position by given value.
		* @param[in] pos : Position change.
		*/
		virtual void movePosition(const sf::Vector2f pos) {
			m_pos += pos;
			m_posFixed = m_pos;
		}
		/**
		* Sets the scale and fixed scale of the MEP::Following.
		* @param[in] scale : Scale.
		*/
		virtual void setScale(const sf::Vector2f scale) { 
			m_scale = scale; 
			m_scaleFixed = scale; 
		}
		/**
		* Sets the scale and fixed scale of the MEP::Following.
		* @param[in] x : MEP::Following object.
		*/
		virtual void setScale(const Following& x) { 
			m_scale = x.m_scale; 
			m_scaleFixed = x.m_scaleFixed; 
		}
		/**
		* Changes the color of a master sprite.
		* @param[in] color : Color.
		*/
		virtual void setColor(const sf::Color& color) {
			m_color = color;
		}
		/**
		* Outputs the color of a master sprite.
		* @return : Color.
		*/
		virtual const sf::Color& getColor() const {
			return m_color;
		}
		/**
		* Outputs the current position of the MEP::Folowing
		* @return Fixed position.
		*/
		sf::Vector2f getPosition() const { 
			return m_posFixed; 
		}
		/**
		* Outputs the current scale of the MEP::Folowing
		* @return Fixed scale.
		*/
		sf::Vector2f getScale() const { 
			return m_scaleFixed; 
		}
		/**
		* Outputs the position of the MEP::Folowing
		* @return Position.
		*/
		sf::Vector2f getOriginPosition() const { 
			return m_pos; 
		}
		/**
		* Outputs the scale of the MEP::Folowing
		* @return Scale.
		*/
		sf::Vector2f getOriginScale() const { 
			return m_scale; 
		}
		/**
		* Outputs the information about MEP::Following activity.
		* @return true - if atleast one istance of the Follwer is active, false - otherwise.
		*/
		bool isFollowerActive() const {
			for (auto& a : followingList)
				if (a->m_animation.isActive())
					return true;
			return false;
		}
		/**
		* Clears the follower list.
		*/
		void clearFollow() { 
			followingList.clear(); 
		}
	};
};