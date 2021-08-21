
////////////////////////////////////////////////////////////
//
//	Object.h created with the use of SFML.
//	MEP - Middle Europe Productions.
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
#ifndef MEP_OBJECT_H
#define MEP_OBJECT_H

#include<SFML/Graphics.hpp>
#include<MEPGraphics/ResourceException.h>
#include<MEPGraphics/Drawable.h>
#include<list>
#include<string>
#include<iostream>
namespace MEP {
	/**
	* MEP::Object keeps a track of all of the shared instances of itself. In will only be possible to delete a MEP::Object when all of the 
	* instances are deleted and MEP::Resources deleteObject() method is called.
	* \brief MEP::Object is a container of a sf::Texture it also have built in memory management.
	*/
	class Object: public Drawable {
	public:
		/**
		* @enum MEP::Object::ObjectType
		* Type of an MEP::Object
		*/
		enum class ObjectType {
			/** Object not initialized.*/
			NotInit,
			/** Object is a single texture.*/
			Single,
			/** Object is a list of textures.*/
			Multi
		};
	private:
		//number of copies 
		int* m_nufC = nullptr;
		//an ID of a file
		const U_int32 m_ID;
		//name of an object
		const std::string m_name;
		//function creats transparency table
		void loadTransparancy(sf::Image& surface);
		//function which loads single texture
		void load(const std::string& fulladdress, bool transparencyM, bool masterSize);
	protected:
		//transparency data (mainly used for the buttons)
		bool transparency = false;
		bool** table = nullptr;
		//master texture size
		sf::Vector2u m_size = {0, 0};
		//textures inside of the Object
		std::list<sf::Texture*>* texture;
		//type on an object
		ObjectType m_type = Object::ObjectType::NotInit;
		//deletes the MEP::Object
		void deleteObject();
	public:
		/**
		* Default constructor.
		*/
		Object() = delete;
		/**
		* Copy constructor.
		*/
		Object(const Object& x);
		/**
		* Constructor of an object.
		* @param[in] path : Path to the resources.
		* @param[in] name : Name of a resource.
		* @param[in] transparencyM : Transparency of a resource.
		*/
		Object(const U_int32 ID,
			const std::string& path,
			const std::string& filename, 
			bool transparencyM = false);
		/**
		* Constructor of an object.
		* @param[in] path : Path to the resources.
		* @param[in] name : Name of a resource.
		* @param[in] frames : Number of textures. Loading starts from the texture name0 to nameN where N is a number of frames - 1. 
		* @param[in] transparencyM : Transparency of a resource.
		*/
		Object(const U_int32 ID,
			const std::string& path,
			const std::string& filename, 
			unsigned int frames, 
			bool transparencyM = false);
		/**
		* Constructor of an object.
		* @param[in] path : Path to the resources.
		* @param[in] name : Name of a resource.
		* @param[in] frames : Number of textures. Loading starts from the texture name0 to nameN where N is a number of frames - 1.
		* @param[in] transparencyM : Transparency of a resource.
		*/
		Object(const U_int32 ID,
			std::list<sf::Image>& images,
			const std::string& filename,
			bool transparencyM = false);
		/**
		* Outputs the size of a master MEP::Object
		* @return sf:Vector2u size.
		*/
		virtual const sf::Vector2u& getSize() const;
		/**
		* Outputs the number of frames of a MEP::Object
		* @return sf:Vector2u size.
		*/
		unsigned long getNufTextures() const;
		/**
		* Override of a MEP::Drawable draw.
		*/
		bool draw(sf::RenderWindow& window) override;
		/**
		* Override of a MEP::Drawable update.
		*/
		void update(sf::Time&) override;
		/**
		* Override of a MEP::Drawable entryUpdate.
		*/
		void entryUpdate(sf::Time& currentTime, bool low = false) override;
		/**
		* Override of a MEP::Drawable exitUpdate.
		*/
		void exitUpdate(sf::Time& currentTime, bool low = false) override;
		/**
		* Outputs the pointer to the MEP::Object
		* @return MEP::Object
		*/
		Object* getObjectPoint();
		/**
		* Outputs the reference to the MEP::Object
		* @return MEP::Object
		*/
		Object& getObjectRef();
		/**
		* Outputs the ID of the MEP::Object
		* @return MEP::Object
		*/
		const U_int32& getID() const;
		/**
		* Outputs the name of the MEP::Object
		* @return MEP::Object
		*/
		const std::string& getName() const;
		/**
		* Checks the transparency of an object for the default SDL_Rect
		* @return true - position has an alpha channel > 100, false - position has an alpha chanel < 100 
		*/
		virtual bool isTansparent(unsigned int x, unsigned int y);
		/**
		* Checks the activity of an object it is mainly related to the associated animations
		*/
		bool isActive() const;
		/**
		* Outputs the type of an MEP::Object
		* @return MEP::Object::ObjectType 
		*/
		const ObjectType& getType() const;
		/**
		* Outputs the number of copies of the MEP::Object
		* @return Number of copies.
		*/
		unsigned int nufC() const;
		/**
		* Operator == operates on MEP::Object name.
		*/
		bool operator==(const std::string& x) const;
		/**
		* Operator == operates on MEP::Object name.
		*/
		bool operator==(const Object& x) const;
		/**
		* Debug output of the class.
		*/
		virtual void debugOutput(std::ostream& out) const;
		/**
		* Overrdie of the << operator for diagnostic purposes.
		*/
		friend std::ostream& operator<<(std::ostream& out, const Object& x);
		/**
		* Destructor.
		*/
		~Object() override;
	}; 
}

#endif
