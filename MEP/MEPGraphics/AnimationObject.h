
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
		void updateSize();
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
			sf::Vector2f scale = { 1.f, 1.f });
		/**
		* On resize we want to update the position.
		*/
		void onResize() override;
		/**
		* Outputs the size of a master MEP::Object
		* @return sf:Vector2u size.
		*/
		virtual const sf::Vector2u& getSize() const;
		/**
		* Sets the scale.
		* @param[in] scale : Scale.
		*/
		void setScale(const sf::Vector2f scale) override;
		/**
		* Sets the scale.
		* @param[in] pos : MEP::Following object.
		*/
		void setScale(const Following& x) override;
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
		void entryUpdate(sf::Time& currentTime, bool low = false) override;
		/**
		* Override of a MEP::Drawable exitUpdate.
		*/
		void exitUpdate(sf::Time& currentTime, bool low = false) override;
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
		const AnimationObject& getAnimationObject();
		/**
		* Debug output of the class.
		*/
		virtual void debugOutput(std::ostream& out) const;
		/**
		* Overrdie of the << operator for diagnostic purposes.
		*/
		friend std::ostream& operator<<(std::ostream& out, const AnimationObject& x);
		/**
		* Default detructor.
		*/
		virtual ~AnimationObject() = default;
	};
}
#endif
