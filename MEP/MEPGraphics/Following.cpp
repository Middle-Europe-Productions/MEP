////////////////////////////////////////////////////////////
//
//	Following.cpp created with the use of SFML
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
#include<MEPGraphics/Following.h>

namespace MEP
{
	Following::Follow::Follow(const AnimationPosition& animation,
		FollowType followType,
		MEP::U_int32 colorsFollow) :
		m_colorsFollow(colorsFollow),
		m_animation(&animation),
		m_followType(followType)
	{
		if (animation._isLinked()) {
			link = animation._linkAddr();
			*link = true;
		}
		else {
			link = std::make_shared<bool>(false);
		}
	}

	bool Following::Follow::isLinked() const {
		return link and *link == true and m_animation;
	}

	bool Following::Follow::isActive() const {
		if (isLinked()) {
			return m_animation->isActive();
		}
		return false;
	}

	void Following::Follow::mute() {
		m_mute = true;
	}

	void Following::Follow::unMute() {
		m_mute = false;
	}

	bool Following::Follow::isMuted() const {
		return m_mute;
	}

	bool Following::Follow::updateVariables(Following& object, sf::Sprite& toUpdate) {
		if (!isLinked() or isMuted()) {
			return false;
		}
		else if (m_followType == FollowType::X_Pos) {
			object.m_posFixed.x = object.m_pos.x + m_animation->getFixedVariable();
			toUpdate.setPosition(object.m_posFixed);
		}
		else if (m_followType == FollowType::Y_Pos) {
			object.m_posFixed.y = object.m_pos.y + m_animation->getFixedVariable();
			toUpdate.setPosition(object.m_posFixed);
		}
		else if (m_followType == FollowType::X_Scale) {
			object.m_scaleFixed.x = object.m_scale.x + m_animation->getFixedVariable();
			toUpdate.setScale(object.m_scaleFixed);
		}
		else if (m_followType == FollowType::Y_Scale) {
			object.m_scaleFixed.y = object.m_scale.y + m_animation->getFixedVariable();
			toUpdate.setScale(object.m_scaleFixed);
		}
		else if (m_followType == FollowType::Color) {
			if (m_colorsFollow == MEP::ColorChannel::ALL)
				toUpdate.setColor(m_animation->getFrameAsColor());
			else {
				if (m_colorsFollow != 0) {
					sf::Uint8 RGBA[4];
					if (m_colorsFollow & MEP::ColorChannel::R)
						RGBA[0] = m_animation->getFrameAsColor().r;
					else
						RGBA[0] = toUpdate.getColor().r;
					if (m_colorsFollow & MEP::ColorChannel::G)
						RGBA[1] = m_animation->getFrameAsColor().g;
					else
						RGBA[1] = toUpdate.getColor().g;
					if (m_colorsFollow & MEP::ColorChannel::B)
						RGBA[2] = m_animation->getFrameAsColor().b;
					else
						RGBA[2] = toUpdate.getColor().b;
					if (m_colorsFollow & MEP::ColorChannel::A)
						RGBA[3] = m_animation->getFrameAsColor().a;
					else
						RGBA[3] = toUpdate.getColor().a;
					toUpdate.setColor({ RGBA[0],RGBA[1],RGBA[2],RGBA[3] });
				}
			}
		}
		return true;
	}

	bool Following::Follow::updateVariables(Following& object) {
		if (!isLinked() or isMuted()) {
			return false;
		}
		else if (m_followType == FollowType::X_Pos) {
			object.m_posFixed.x = object.m_pos.x + m_animation->getFixedVariable();
		}
		else if (m_followType == FollowType::Y_Pos) {
			object.m_posFixed.y = object.m_pos.y + m_animation->getFixedVariable();
		}
		else if (m_followType == FollowType::X_Scale) {
			object.m_scaleFixed.x = object.m_scale.x + m_animation->getFixedVariable();
		}
		else if (m_followType == FollowType::Y_Scale) {
			object.m_scaleFixed.y = object.m_scale.y + m_animation->getFixedVariable();
		}
		else if (m_followType == FollowType::Color) {
			if (m_colorsFollow == MEP::ColorChannel::ALL)
				object.setColor(m_animation->getFrameAsColor());
			else {
				if (m_colorsFollow != 0) {
					sf::Uint8 RGBA[4];
					if (m_colorsFollow & MEP::ColorChannel::R)
						RGBA[0] = m_animation->getFrameAsColor().r;
					else
						RGBA[0] = object.getColor().r;
					if (m_colorsFollow & MEP::ColorChannel::G)
						RGBA[1] = m_animation->getFrameAsColor().g;
					else
						RGBA[1] = object.getColor().g;
					if (m_colorsFollow & MEP::ColorChannel::B)
						RGBA[2] = m_animation->getFrameAsColor().b;
					else
						RGBA[2] = object.getColor().b;
					if (m_colorsFollow & MEP::ColorChannel::A)
						RGBA[3] = m_animation->getFrameAsColor().a;
					else
						RGBA[3] = object.getColor().a;
					object.setColor({ RGBA[0],RGBA[1],RGBA[2],RGBA[3] });
				}
			}
		}
		return true;
	}

	bool Following::Follow::operator==(const Follow& x) const {
		return &m_animation == &x.m_animation;
	}

	Following::Following(const FollowType& followType,
		sf::Vector2f pos,
		sf::Vector2f posFixed,
		sf::Vector2f scale,
		sf::Vector2f scaleFixed) :
		m_followType(followType),
		m_pos(pos),
		m_posFixed(posFixed),
		m_scale(scale),
		m_scaleFixed(scaleFixed)
	{};

	Following::Following(sf::Vector2f pos,
		sf::Vector2f posFixed,
		sf::Vector2f scale,
		sf::Vector2f scaleFixed) :
		m_pos(pos),
		m_posFixed(posFixed),
		m_scale(scale),
		m_scaleFixed(scaleFixed)
	{};

	Following::Following(const Following& x) :
		calc_position(x.calc_position),
		m_pos(x.m_pos),
		m_posFixed(x.m_posFixed),
		m_scale(x.m_scale),
		m_scaleFixed(x.m_scaleFixed),
		m_color(x.m_color),
		m_colorFixed(x.m_colorFixed)
	{};

	void Following::updatePosition() {
		setPosition(calc_position() + m_posMove);
	}

	void Following::addMethodPos(std::function<sf::Vector2f()> method) {
		calc_position = method;
	}

	void Following::updateScale() {
		setScale(calc_scale());
	}

	void Following::addMethodScale(std::function<sf::Vector2f()> method) {
		calc_scale = method;
	}

	Following& MEP::Following::operator<<(const Following& x) {
		if (this != &x) {
			m_pos = x.m_pos;
			m_posFixed = x.m_posFixed;
			m_scale = x.m_scale;
			m_scaleFixed = x.m_scaleFixed;
			m_color = x.m_color;
			m_colorFixed = x.m_colorFixed;
			calc_position = x.calc_position;
			calc_scale = x.calc_scale;
		}
		return *this;
	}

	void Following::setFollow(const AnimationPosition& base, const FollowType type, MEP::U_int32 group) {
		followingListv2._insert(0, group, std::make_unique<Follow>(base, type));
	}

	void Following::setFollow(const AnimationColor& base, MEP::U_int32 toFollow, MEP::U_int32 group) {
		followingListv2._insert(0, group, std::make_unique<Follow>(base, MEP::Following::FollowType::Color, toFollow));
	}

	void Following::muteFollowGroup(MEP::U_int32 group) {
		followingListv2._execute([](auto& x) {
			x.get()->mute();
			}, group);
	}

	void Following::unMuteFollowGroup(MEP::U_int32 group) {
		followingListv2._execute([](auto& x) {
			x.get()->unMute();
			}, group);
	}

	void Following::fullMuteFollow() {
		followingListv2._execute([](auto& x) {
			x.get()->mute();
			});
	}

	void Following::fullUnMuteFollow() {
		followingListv2._execute([](auto& x) {
			x.get()->unMute();
			});
	}

	void Following::setPosition(const sf::Vector2f pos) {
		m_pos = pos;
		m_posFixed = pos;
		m_posMove = { 0.f,0.f };
	}

	void Following::setPosition(const Following& x) {
		m_pos = x.m_pos;
		m_posFixed = x.m_posFixed;
		m_posMove = { 0.f,0.f };
	}

	void Following::movePosition(const sf::Vector2f pos) {
		m_pos += pos;
		m_posFixed = m_pos;
		m_posMove = pos;
	}

	void Following::setScale(const sf::Vector2f scale) {
		m_scale = scale;
		m_scaleFixed = scale;
	}

	void Following::setScale(const Following& x) {
		m_scale = x.m_scale;
		m_scaleFixed = x.m_scaleFixed;
	}

	void Following::setColor(const sf::Color& color) {
		m_color = color;
	}

	const sf::Color& Following::getColor() const {
		return m_color;
	}

	sf::Vector2f Following::getPosition() const {
		return m_posFixed;
	}

	sf::Vector2f Following::getScale() const {
		return m_scaleFixed;
	}

	sf::Vector2f Following::getOriginPosition() const {
		return m_pos;
	}

	sf::Vector2f Following::getOriginScale() const {
		return m_scale;
	}

	bool Following::isFollowerActive() const {
		bool active = false;
		followingListv2._execute([&active](const auto& x) {
			if (x.get()->isLinked()) {
				if (x.get()->isActive())
					active = true;
			}
			});
		return active;
	}

	void Following::followingDebug(std::ostream& out, const char* skipLines) const {
		followingListv2._debugOutput(out, [](auto& x, std::ostream& out) { out << "  " << *x << std::endl; });
	}

	void Following::clearFollow() {
		followingListv2._clear();
	}
}