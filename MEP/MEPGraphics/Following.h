
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
#ifndef MEP_FOLLOWING_H
#define MEP_FOLLOWING_H

#include<MEPGraphics/Config.h>
#include<MEPGraphics/AnimationPosition.h>
#include<MEPGraphics/AnimationColor.h>
#include<MEPGraphics/Group.h>
namespace MEP {
	/**
	* \brief MEP::Following keeps track of a MEP::Object position.
	*/
	class Following {
	public:
		/**
		* @enum MEP::Following::FollowType
		* Types of the following.
		*/
		enum class FollowType {
			/** Following not initialized.*/
			NotInit = 0,
			/** Following other Objects.*/
			Objects = 1,
			/** Following with a change of X scale*/
			X_Scale = 2,
			/** Following with a change of Y scale*/
			Y_Scale = 3,
			/** Following with a change of X position*/
			X_Pos = 4,
			/** Following with a change of Y position*/
			Y_Pos = 5,
			/** Following with a change of a color.*/
			Color = 6
		};
	private:
		//type of a following
		FollowType m_followType = FollowType::NotInit;
		class Follow {
			const char* __FollowType[7] = { "NotInit", "Objects", "X_Scale", "Y_Scale", "X_Pos", "Y_Pos", "Color" };
			//Mute status
			bool m_mute = false;
			//Blocking color channels 
			MEP::U_int32 m_colorsFollow;
			//Reference to the animation
			std::shared_ptr<bool> link = nullptr;
			const AnimationPosition* m_animation;
			//Followtype of an object.
			FollowType m_followType = FollowType::NotInit;
		public:
			//Constructor
			Follow(const AnimationPosition& animation,
				FollowType followType = FollowType::NotInit,
				MEP::U_int32 colorsFollow = MEP::ColorChannel::ALL);
			/**
			* Is link active.
			*/
			bool isLinked() const;
			/**
			* Animation is active.
			*/
			bool isActive() const;
			/**
			* Mutes the follower. The output will not be taken into a consideration.
			*/
			void mute();
			/**
			* Unmutes the follower.
			*/
			void unMute();
			/**
			* Outputs the infromation about the mute.
			*/
			bool isMuted() const;
			/**
			* Updates the Variables.
			* @return: True - Update successful, False - Link does not exist. You might have deleted the base animation.
			*/
			bool updateVariables(Following& object, sf::Sprite& toUpdate);
			/**
			* Updates the Variables.
			* @return: True - Update successful, False - Link does not exist. You might have deleted the base animation.
			*/
			bool updateVariables(Following& object);
			/**
			* Outputs the info message.
			*/
			friend std::ostream& operator<<(std::ostream& out, const Follow& x) {
				out << "FollowType: {" << x.__FollowType[(unsigned int)x.m_followType] << "}";
				if (x.m_followType == FollowType::Color) {
					out << ", Channel: { ";
					if (x.m_colorsFollow & R)
						out << "R ";
					if (x.m_colorsFollow & G)
						out << "G ";
					if (x.m_colorsFollow & B)
						out << "B ";
					if (x.m_colorsFollow & A)
						out << "A ";
					out << "}";
				}
				out << ", Muted:";
				if (x.isMuted()) {
					out << " True";
				}
				else {
					out << " False";
				}
				return out;
			}
			/**
			* Assignment operator. Relative to the address on an animation.
			*/
			bool operator==(const Follow& x) const;
		};
	protected:
		//[optional] formula for calculation of the position
		std::function<sf::Vector2f()> calc_position = [this]()->sf::Vector2f { return m_pos; };
		//[optional] formula for calculation of the scale.
		std::function<sf::Vector2f()> calc_scale = [this]()->sf::Vector2f { return m_scale; };

		MEPtools::GroupManager<Follow, std::unique_ptr<Follow>, std::list<std::unique_ptr<Follow>>> followingListv2;
		//Origin of an object.
		sf::Vector2f m_origin = { 0.f, 0.f };
		mutable bool m_originChange = true;
		//texture position and scale
		sf::Vector2f m_pos = { 0.f, 0.f };
		sf::Vector2f m_posMove = { 0.f, 0.f };
		sf::Vector2f m_posFixed = { 0.f, 0.f };
		mutable bool m_posChange = true;
		sf::Vector2f m_scale = { 1.f, 1.f };
		sf::Vector2f m_scaleFixed = { 1.f, 1.f };
		mutable bool m_scaleChange = true;
		sf::Color m_color = { 0, 0, 0, 0 };
		sf::Color m_colorFixed = { 0, 0, 0, 0 };
		mutable bool m_colorChange = true;
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
			sf::Vector2f scaleFixed = { 1.f, 1.f });
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
			sf::Vector2f scaleFixed = { 1.f, 1.f });
		/**
		* Warning list of the following objects is individual for every object.
		* **Copy constructor does not copy them.**
		* Copy constructor copy position, scale and color.
		* @param[in] x : Another MEP::Following instance.
		*/
		Following(const Following& x);
		/**
		* Updates the position of an object according the the given method.
		* If method is not specified does not change anything.
		*/
		void updatePosition();
		/**
		* Adds a method of calculation the position.
		* @param[in] method : A method of calculating the position.
		*/
		void addMethodPos(std::function<sf::Vector2f()> method);
		/**
		* Updates the scale of an object according the the given method.
		* If method is not specified does not change anything.
		*/
		void updateScale();
		/**
		* Adds a method of calculation the scale.
		* @param[in] method : A method of calculating the position.
		*/
		void addMethodScale(std::function<sf::Vector2f()> method);
		/**
		* Warning list of the following objects is indivdual for every object.
		* **Assign operator does not copy them.**
		* Assign operator copy position, scale and color.
		* @param[in] x : Another MEP::Following instance.
		*/
		Following& operator<<(const Following& x);
		/**
		* Sets the object to follow using another MEP::AnimationPosition instance.
		* @param[in] base : MEP::AnimationPosition object to follow.
		* @param[in] type : Type of a follow.
		*/
		void setFollow(const AnimationPosition& base, const FollowType type, MEP::U_int32 group = -1);
		/**
		* Sets the object to follow using another MEP::AnimationColor instance.
		* Use MEP::ColorChannel here.
		* @param[in] base : MEP::AnimationPosition object to follow.
		* @param[in] type : Type of a follow.
		* @param[in] toFollow : Channels to be followed.
		*/
		void setFollow(const AnimationColor& base, MEP::U_int32 toFollow = MEP::ColorChannel::ALL, MEP::U_int32 group = -1);
		/**
		* Mutes a group of objects.
		*/
		void muteFollowGroup(MEP::U_int32 group);
		/**
		* Unmutes a group of objects.
		*/
		void unMuteFollowGroup(MEP::U_int32 group);
		/**
		* Full mute of the following objects.
		*/
		void fullMuteFollow();
		/**
		* Full mute of the following objects.
		*/
		void fullUnMuteFollow();
		/**
		* Sets the origin of an object. Relative to the 0, 0 point.
		*/
		virtual void setOrigin(const sf::Vector2f& org);
		/**
		* Outputs the status of the origin.
		*/
		bool originStatus() const;
		/**
		* Resets the status of the origin.
		*/
		void resetOriginStatus() const;
		/**
		* Sets the position and fixed position of an MEP::Following.
		* @param[in] pos : Position.
		*/
		virtual void setPosition(const sf::Vector2f& pos);
		/**
		* Sets the position and fixed position of an MEP::Following.
		* @param[in] x : MEP::Following object.
		*/
		virtual void setPosition(const Following& x);
		/**
		* Ouputs information regarding position change status.
		*/
		bool positionStatus() const;
		/**
		* Resets status of the position.
		*/
		void resetPositionStatus() const;
		/**
		* Moves the position by given value.
		* @param[in] pos : Position change.
		*/
		virtual void movePosition(const sf::Vector2f& pos);
		/**
		* Sets the scale and fixed scale of the MEP::Following.
		* @param[in] scale : Scale.
		*/
		virtual void setScale(const sf::Vector2f& scale);
		/**
		* Sets the scale and fixed scale of the MEP::Following.
		* @param[in] x : MEP::Following object.
		*/
		virtual void setScale(const Following& x);
		/**
		* Ouputs information regarding scale change status.
		*/
		bool scaleStatus() const;
		/**
		* Resets status of the scale.
		*/
		void resetScaleStatus() const;
		/**
		* Changes the color of a master sprite.
		* @param[in] color : Color.
		*/
		virtual void setColor(const sf::Color& color);
		/**
		* Ouputs information regarding scale change color.
		*/
		bool colorStatus() const;
		/**
		* Resets status of the color.
		*/
		void resetColorStatus() const;
		/**
		* Outputs the color of a master sprite.
		* @return : Color.
		*/
		virtual const sf::Color& getColor() const;
		/**
		* Outputs the current position of the MEP::Folowing
		* @return Fixed position.
		*/
		const sf::Vector2f& getOrigin() const;
		/**
		* Outputs the current position of the MEP::Folowing
		* @return Fixed position.
		*/
		const sf::Vector2f& getPosition() const;
		/**
		* Outputs the current scale of the MEP::Folowing
		* @return Fixed scale.
		*/
		const sf::Vector2f& getScale() const;
		/**
		* Outputs the position of the MEP::Folowing
		* @return Position.
		*/
		const sf::Vector2f& getOriginPosition() const;
		/**
		* Outputs the scale of the MEP::Folowing
		* @return Scale.
		*/
		const sf::Vector2f& getOriginScale() const;
		/**
		* Outputs the information about MEP::Following activity.
		* @return true - if atleast one istance of the Follwer is active, false - otherwise.
		*/
		bool isFollowerActive() const;
		/**
		* Following debug message.
		*/
		void followingDebug(std::ostream& out, const char* skipLines = "") const;
		/**
		* Clears the follower list.
		*/
		void clearFollow();
	};
};

#endif
