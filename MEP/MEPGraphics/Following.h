
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
#include"AnimationPossition.h"
namespace MEP {
	class Following {
	public:
		enum class FollowType {
			NotInit,
			Objects,
			X_Scale,
			Y_Scale,
			X_Poss,
			Y_Poss
		};
	private:		
		//type of a following
		FollowType m_followType = FollowType::NotInit;
		struct Follow {
			const AnimationPossition& m_animation;
			FollowType m_followType = FollowType::NotInit;
			Follow(const AnimationPossition& animation, FollowType followType = FollowType::NotInit) :
				m_animation(animation),
				m_followType(followType) {}
			void CheckVariables(sf::Vector2f& m_poss, sf::Vector2f& m_possFixed, sf::Vector2f& m_scale, sf::Vector2f& m_scaleFixed);
		};
	protected:
		std::list<Follow*> followingList;
		//texture possition and scale
		sf::Vector2f m_poss = {0.f, 0.f};
		sf::Vector2f m_possFixed = { 0.f, 0.f };
		sf::Vector2f m_scale = { 1.f, 1.f };
		sf::Vector2f m_scaleFixed = { 1.f, 1.f };
	public:
		Following() = default;
		Following(const FollowType& followType,
			sf::Vector2f poss = { 0.f, 0.f },
			sf::Vector2f possFixed = { 0.f, 0.f }, 
			sf::Vector2f scale = { 1.f, 1.f }, 
			sf::Vector2f scaleFixed = { 1.f, 1.f }) : 
			m_followType(followType), 
			m_poss(poss), 
			m_possFixed(possFixed), 
			m_scale(scale), 
			m_scaleFixed(scaleFixed)
		{};
		Following(sf::Vector2f poss,
			sf::Vector2f possFixed,
			sf::Vector2f scale,
			sf::Vector2f scaleFixed) :
			m_poss(poss),
			m_possFixed(possFixed),
			m_scale(scale),
			m_scaleFixed(scaleFixed)
		{};
		//setting following animation
		void SetFollow(const AnimationPossition& base, const FollowType type);
		//possition and sclae setting
		virtual void SetPossition(const sf::Vector2f poss) { m_poss = poss; m_possFixed = poss; }
		virtual void SetPossition(const Following& x) { m_poss = x.m_poss; m_possFixed = x.m_possFixed; }
		virtual void SetScale(const sf::Vector2f scale) { m_scale = scale; m_scaleFixed = scale; }
		virtual void SetScale(const Following& x) { m_scale = x.m_scale; m_scaleFixed = x.m_scaleFixed; }
		//gets info about possition and scale
		sf::Vector2f GetPossition() const { return m_possFixed; }
		sf::Vector2f GetScale() const { return m_scaleFixed; }
		sf::Vector2f GetOriginPossition() const { return m_poss; }
		sf::Vector2f GetOriginScale() const { return m_scale; }
		//returns an information about an activity of at least one follower
		bool isFollowerActive() const;
		void ClearFollow() { followingList.clear(); }
	};

	void MEP::Following::SetFollow(const AnimationPossition& base, const FollowType type)
	{
		for (auto& x : followingList)
			if (type == x->m_followType)
				throw "This type of follow already exists!";
		followingList.push_back(new Follow(base, type));
	}

	bool MEP::Following::isFollowerActive() const
	{
		for (auto& a : followingList)
			if (a->m_animation.IsActive())
				return true;
		return false;
	}

};