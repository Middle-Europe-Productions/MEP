
////////////////////////////////////////////////////////////
//
//	Drawable.h created with the use of SFML
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
#ifndef MEP_DRAWABLE_H
#define MEP_DRAWABLE_H
#include<MEPGraphics/Config.h>
#include<SFML/Graphics.hpp>
#include<iostream>
#include<memory>
namespace MEP {
	/**
	* @enum MEP::Button::DrawTag defines a draw tag.
	*/
	enum DrawTag : U_int32 {
		/** There is no draw tag.*/
		Non = 0,
		/** View lock tag. Objects will be rendered using master view if custom view is enabled.*/
		ViewLock = 1 << 1,
		/** Unactive tag. Objects will not be rendered. */
		Unactive = 1 << 2,
		/** When set changes the position on the resize.*/
		Resize_Pos = 1 << 3,
		/** When set changes the scale on the resize.*/
		Resize_Scale = 1 << 4,
		/** When set changes the rect. Works only with (MEP::TextureObject, MEP::AnimationObject, MEP::Button)*/
		Resize_Rect = 1 << 5
	};
	/**
	* \brief MEP::Drawable provides a basic implementation of an object with the ability of display it on a screen.
	*/
	class Drawable {
		std::shared_ptr<bool> link = std::make_shared<bool>(true);
		U_int32 m_drawTag = DrawTag::Non;
	protected:
		/**
		* Notify the link.
		*/
		void notify();
		/**
		* DrawTag output
		*/
		void drawTagDebug(std::ostream& out) const;
	public:
		/**
		* Links the notification link.
		* Boolean value output true when resource is active.
		*/
		void _link(std::shared_ptr<bool> _li);
		/**
		* Outputs the notification link.
		* Boolean value output true when resource is active.
		*/
		std::shared_ptr<bool> _linkAddr();
		/**
		* Outputs the notification link.
		* Boolean value output true when resource is active.
		*/
		const std::shared_ptr<bool> _linkAddr() const;
		/**
		* Outputs the information about the activity of the link.
		* Boolean value output true when resource is active.
		*/
		bool _isLinked() const;
		/**
		* Outputs draw tag of a MEP::Drawable
		* Use MEP::DrawTag here.
		* @return : MEP::Drawable::DrawTag.
		*/
		U_int32 getDrawTag() const;
		/**
		* Sets the draw tag of a MEP::Drawable.
		* Use MEP::DrawTag here.
		* @param[in] : MEP::Drawable::DrawTag.
		*/
		void setDrawTag(const U_int32 tag);
		/**
		* Adds the draw tag of a MEP::Drawable.
		* Use MEP::DrawTag here.
		* @param[in] : MEP::Drawable::DrawTag.
		* @return : True - draw tag was added. False - draw tag is already added.
		*/
		bool addDrawTag(const U_int32 tag);
		/**
		* Removes the draw tag of a MEP::Drawable.
		* Use MEP::DrawTag here.
		* @param[in] : MEP::Drawable::DrawTag.
		* @return : True - draw tag was deleted. False - draw tag was not set.
		*/
		bool removeDrawTag(const U_int32 tag);
		/**
		* Instructions on what to do when window is being resized.
		*/
		virtual void onResize();
		/**
		* Default contructor.
		*/
		Drawable() = default;
		/**
		* Default virtual draw function.
		* @param[in] window : Reference to a window.
		* @return True if the drawing was successful, or false if there is something wrong with an object and it must be redrawn.
		*/
		virtual bool draw(sf::RenderWindow&);
		/**
		* Default virtual update function.
		* @param[in] currentTime : Current global time.
		*/
		virtual void update(sf::Time&);
		/**
		* Default virtual entry update function.
		* @param[in] currentTime : Current global time.
		*/
		virtual void entryUpdate(sf::Time& currentTime, bool low = false);
		/**
		* Default virtual exit update function.
		* @param[in] currentTime : Current global time.
		*/
		virtual void exitUpdate(sf::Time& currentTime, bool low = false);
		/**
		* Default virtual activation status method.
		* @param[in] currentTime : Current global time.
		*/
		virtual bool isActive() const;
		/**
		* Debug output of the class.
		*/
		virtual void debugOutput(std::ostream& out) const;
		/**
		* Overrdie of the << operator for diagnostic purposes.
		*/
		virtual ~Drawable();
		
		friend std::ostream& operator<<(std::ostream & out, const Drawable & x);
	};
};

#endif
