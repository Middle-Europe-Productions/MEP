
////////////////////////////////////////////////////////////
//
//	AnimationPosition.h created with the use of SFML
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
#ifndef MEP_ANIMATION_POSITION_H
#define MEP_ANIMATION_POSITION_H

#include<functional>
#include<list>
#include<iostream>
#include<cmath>
#include<MEPGraphics/AnimationBase.h>
#include<MEPGraphics/Drawable.h>
namespace MEP {
	/**
	* The idea here is simple. We take a function f.
	* Then min(<f(begin), ..., f(end)>) where min is a minimal value. Becomes our entry position.
	* And max(<f(begin), ..., f(end)>) where max is a maximal value. Becomes our exit position.
	* Please keep in mind that f(begin) and minimal value are 2 seperate things, but of course f(begin) can be equal to minimal value.
	* After all of that we generate points according to the given framerate and animation lenght.
	* \brief MEP::AnimationPosition provides a basic implementation of a modification of the position.
	*/
	class AnimationPosition : public Drawable, public Animation {
	protected:
		std::function<double(double x)> m_function;
		//all frames information
		unsigned int nofFrames;
		std::list<double> frames;
		std::list<double>::iterator currentFrame;

		unsigned int current_frame = 0;
		//begin and end on a graph
		const double m_begin = 0;
		const double m_end = 0;
		//position
		double m_entry = 0;
		double m_exit = 0;
		void init();
		/**
		* Core updates for position animation.
		*/
		void updatePositionAnimation(sf::Time& currentTime);
	public:
		AnimationPosition() = default;
		/**
		* Vopy constructor of an animation.
		* @param[in] x : MEP::AnimationPosition object
		*/
		AnimationPosition(const AnimationPosition& x);
		/**
		* Contructor of an animation. It is taking a part of a from f(begin) to f(end) then calculation the position accoring to the formula.
		* Fmax(F(begin), F(end)) = exit, and Fmin(F(begin), F(end) = min.
		* @param[in] begin : Begining point on a graph,
		* @param[in] end : End point of a graph.
		* @param[in] length : Animation lenght in ms.
		* @param[in] frameRate : Frame rate of an animation.
		* @param[in] entry : Entry position of an Object (before the animation)
		* @param[in] exit : Exit position of an Object (after the animation)
		* @param[in] fun : Function graph. Method with the return type double. 
		*/
		AnimationPosition(const double entry,
			const double exit,
			sf::Time length,
			const float frameRate = 120,
			const double begin = 0,
			const double end = 100,
			std::function<double(double x)> function = [](double x)->double { return x; });
		/**
		* Sets the running tag to true and changes the direction of a movement, furthermore,
		* it is capable of setting a current time.
		* @param[in] direc : MEP::Animation::Direction.
		* @param[in] currentTime : sf::Time = sf::Time::Zero.
		*/
		virtual void run(const Direction direc, sf::Time currentTime = sf::Time::Zero);
		/**
		* Outputs the current position of an animation.
		* @return Current position.
		*/
		const double& getFixedVariable() const;
		/**
		* Outputs the current position of an animation.
		* @return Current position as unsigned int.
		*/
		unsigned int getFixedUintVariable() const;
		/**
		* Outputs the entry position of an animation.
		* @return Entry position.
		*/
		const double& getEntry() const;
		/**
		* Outputs the exit position of an animation.
		* @return Exit position.
		*/
		const double& getExit() const;
		/**
		* Override of a MEP::Drawable draw.
		*/
		bool draw(sf::RenderWindow&) override;
		/**
		* Override of a MEP::Drawable update.
		*/
		virtual void update(sf::Time& currentTime);
		/**
		* Override of a MEP::Drawable entryUpdate.
		*/
		void entryUpdate(sf::Time& currentTime, bool low = false) override;
		/**
		* Override of a MEP::Drawable exitUpate.
		*/
		void exitUpdate(sf::Time& currentTime, bool low = false) override;
		/**
		* Outputs the activation status of an animation.
		* @return True - active, False - unactive
		*/
		bool isActive() const override;
		/**
		* Resets the parameters of the animation if the animation is not active.
		* Reset means changing it's current frame to begin or end depending of the direction.
		* If direction is forward changes to begin otherwise to end.
		*/
		bool reset() override;
		/**
		* Outputs the current frame as a Color
		* *Warning* For color animation it is recommended to use MEP::AnimationColor
		* @return : sf::Color
		*/
		virtual sf::Color getFrameAsColor() const;

		void delayOutput(std::ostream& out) const;
		/**
		* Debug output of the class.
		*/
		virtual void debugOutput(std::ostream& out) const;
		/**
		* Overrdie of the << operator for diagnostic purposes.
		*/
		friend std::ostream& operator<<(std::ostream & out, const AnimationPosition & x);
		/**
		* Destructor.
		*/
		virtual ~AnimationPosition();
	};
};

#endif
