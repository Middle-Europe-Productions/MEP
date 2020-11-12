
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
//	Created by Piotr Skibiñski
//	Copyright © Middle Europe Productions. All rights reserved.
//
////////////////////////////////////////////////////////////

#pragma once
#include"AnimationPosition.h"
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
			/** Following with o change of X scale*/
			X_Scale,
			/** Following with o change of Y scale*/
			Y_Scale,
			/** Following with o change of X position*/
			X_Pos,
			/** Following with o change of Y position*/
			Y_Pos
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
			void CheckVariables(sf::Vector2f& m_pos, sf::Vector2f& m_posFixed, sf::Vector2f& m_scale, sf::Vector2f& m_scaleFixed);
		};
	protected:
		std::list<std::unique_ptr<Follow>> followingList;
		//texture position and scale
		sf::Vector2f m_pos = {0.f, 0.f};
		sf::Vector2f m_posFixed = { 0.f, 0.f };
		sf::Vector2f m_scale = { 1.f, 1.f };
		sf::Vector2f m_scaleFixed = { 1.f, 1.f };
	public:
		/**
		* Default contructor.
		*/
		Following() = default;
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
		Following(sf::Vector2f pos,
			sf::Vector2f posFixed,
			sf::Vector2f scale,
			sf::Vector2f scaleFixed) :
			m_pos(pos),
			m_posFixed(posFixed),
			m_scale(scale),
			m_scaleFixed(scaleFixed)
		{};
		/**
		* Sets the object to follow using another MEP::AnimationPosition instance.
		* @param[in] base : MEP::AnimationPosition object to follow.
		* @param[in] type : Type of a follow.
		*/
		void SetFollow(const AnimationPosition& base, const FollowType type) {
			for (auto& x : followingList)
				if (type == x->m_followType)
					throw "This type of follow already exists!";
			followingList.push_back(std::make_unique<Follow>(base, type));
		}
		/**
		* Sets the position and fixed position of an MEP::Following.
		* @param[in] pos : Position.
		*/
		virtual void SetPosition(const sf::Vector2f pos) { 
			m_pos = pos; 
			m_posFixed = pos; 
		}
		/**
		* Sets the position and fixed position of an MEP::Following.
		* @param[in] x : MEP::Following object.
		*/
		virtual void SetPosition(const Following& x) { 
			m_pos = x.m_pos; 
			m_posFixed = x.m_posFixed; 
		}
		/**
		* Sets the scale and fixed scale of the MEP::Following.
		* @param[in] scale : Scale.
		*/
		virtual void SetScale(const sf::Vector2f scale) { 
			m_scale = scale; 
			m_scaleFixed = scale; 
		}
		/**
		* Sets the scale and fixed scale of the MEP::Following.
		* @param[in] x : MEP::Following object.
		*/
		virtual void SetScale(const Following& x) { 
			m_scale = x.m_scale; 
			m_scaleFixed = x.m_scaleFixed; 
		}
		/**
		* Outputs the current position of the MEP::Folowing
		* @return Fixed position.
		*/
		sf::Vector2f GetPosition() const { 
			return m_posFixed; 
		}
		/**
		* Outputs the current scale of the MEP::Folowing
		* @return Fixed scale.
		*/
		sf::Vector2f GetScale() const { 
			return m_scaleFixed; 
		}
		/**
		* Outputs the position of the MEP::Folowing
		* @return Position.
		*/
		sf::Vector2f GetOriginPosition() const { 
			return m_pos; 
		}
		/**
		* Outputs the scale of the MEP::Folowing
		* @return Scale.
		*/
		sf::Vector2f GetOriginScale() const { 
			return m_scale; 
		}
		/**
		* Outputs the information about MEP::Following activity.
		* @return true - if atleast one istance of the Follwer is active, false - otherwise.
		*/
		bool isFollowerActive() const {
			for (auto& a : followingList)
				if (a->m_animation.IsActive())
					return true;
			return false;
		}
		/**
		* Clears the follower list.
		*/
		void ClearFollow() { 
			followingList.clear(); 
		}
	};
};