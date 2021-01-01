
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

#pragma once
#include<SFML/Graphics.hpp>
#include"Drawable.h"
#include"Config.h"
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
		std::list<sf::Texture*> texture;
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
		Object(const Object& x) : 
			m_ID(x.m_ID),
			m_name(x.m_name), 
			transparency(x.transparency), 
			table(x.table), 
			m_size(x.m_size), 
			texture(x.texture), 
			m_type(x.m_type) 
		{ 
			std::cout << "Copy constructor: Name: " <<x.m_name;
			m_nufC = x.m_nufC;
			*m_nufC += 1;
			std::cout << ", copy: " << *m_nufC << std::endl;
		}
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
		virtual const sf::Vector2u& getSize() const { 
			return m_size; 
		};
		/**
		* Outputs the number of frames of a MEP::Object
		* @return sf:Vector2u size.
		*/
		unsigned long getNufTextures() const {
			return texture.size(); 
		}
		/**
		* Override of a MEP::Drawable draw.
		*/
		bool draw(sf::RenderWindow& window) override;
		/**
		* Override of a MEP::Drawable update.
		*/
		void update(sf::Time& currentTime) override {};
		/**
		* Override of a MEP::Drawable entryUpdate.
		*/
		void entryUpdate(sf::Time& currentTime) override { 
			update(currentTime); 
		};
		/**
		* Override of a MEP::Drawable exitUpdate.
		*/
		void exitUpdate(sf::Time& currentTime) override { 
			update(currentTime);  
		};
		/**
		* Outputs the pointer to the MEP::Object
		* @return MEP::Object
		*/
		Object* getObjectPoint() { *m_nufC += 1;  return this; }
		/**
		* Outputs the reference to the MEP::Object
		* @return MEP::Object
		*/
		Object& getObjectRef() { return *this; }
		/**
		* Outputs the ID of the MEP::Object
		* @return MEP::Object
		*/
		const U_int32 getID() const { return m_ID; }
		/**
		* Outputs the name of the MEP::Object
		* @return MEP::Object
		*/
		const std::string& getName() const { return m_name; }
		/**
		* Checks the transparency of an object for the default SDL_Rect
		* @return true - position has an alpha channel > 100, false - position has an alpha chanel < 100 
		*/
		virtual bool isTansparent(unsigned int x, unsigned int y);
		/**
		* Checks the activity of an object it is mainly related to the associated animations
		*/
		bool isActive() const { 
			return false; 
		};
		/**
		* Outputs the type of an MEP::Object
		* @return MEP::Object::ObjectType 
		*/
		const ObjectType& getType() const { 
			return m_type; 
		}
		/**
		* Outputs the number of copies of the MEP::Object
		* @return Number of copies.
		*/
		const unsigned int nufC() const {
			return *m_nufC;
		}
		/**
		* Operator == operates on MEP::Object name.
		*/
		bool operator==(const std::string& x) const { 
			return x == m_name; 
		}
		/**
		* Operator == operates on MEP::Object name.
		*/
		bool operator==(const Object& x) const { 
			return x.getName() == m_name; 
		}
		~Object() override;
	}; 
	
	inline void Object::loadTransparancy(sf::Image& surface)
	{
		//allocate table
		table = new bool* [surface.getSize().x];
		for (int i = 0; i < surface.getSize().x; ++i)
			table[i] = new bool[surface.getSize().y];
		//fill table
		if (table) {
			for (int i = 0; i < surface.getSize().x; i++) {
				for (int j = 0; j < surface.getSize().y; j++) {
					table[i][j] = surface.getPixel(i, j).a < 100;
				}
			}
			transparency = true;
		}
	}

	inline void Object::load(const std::string& fulladdress, bool transparencyM, bool masterSize) {
		texture.push_back(new sf::Texture());
		if (!texture.back()->loadFromFile(fulladdress)) {
			throw "Texture not loaded!";
		}
		texture.back()->setSmooth(true);
		if (transparencyM) {
			sf::Image x;
			if (!x.loadFromFile(fulladdress)) {
				throw "Transparency mask not loaded!";
			}
			loadTransparancy(x);
		}
		if (masterSize) {
			m_size.x = texture.front()->getSize().x;
			m_size.y = texture.front()->getSize().y;
		}
	}

	inline void Object::deleteObject()
	{
		if (*m_nufC == 0) {
			if (table != nullptr) {
				delete[] table;
			}
			for (auto x = texture.begin(); x != texture.end(); x++)
				delete* x;
			std::cout << ", object has been permanently deleted.";
			delete m_nufC;
		}
		else {
			*m_nufC -= 1;
		}
	}

	inline bool Object::isTansparent(unsigned int x, unsigned int y)
	{
		if (transparency and x < m_size.x and y < m_size.y)
			return table[x][y];
		return true;
	}

	inline Object::Object(const U_int32 ID, const std::string& path, const std::string& filename, bool transparencyM) :
		m_ID(ID),
		m_nufC(new int(0)), 
		m_name(filename),
		m_type(ObjectType::Single)
	{
		load(path + filename + ".png", transparencyM, true);
	}

	inline Object::Object(const U_int32 ID, const std::string& path, const std::string& filename, unsigned int frames, bool transparencyM) :
		m_ID(ID),
		m_nufC(new int(0)),
		m_name(filename), 
		m_type(ObjectType::Multi)
	{
		for (int i = 0; i < frames; i++) {
			load(path + filename + std::to_string(i) + ".png", transparencyM and i == 0, i == 0);
		}
	}

	inline Object::Object(const U_int32 ID, std::list<sf::Image>& images, const std::string& filename, bool transparencyM):
		m_ID(ID),
		m_nufC(new int(0)),
		m_name(filename),
		transparency(false)
	{
		for (auto& i : images) {
			texture.push_back(new sf::Texture());
			if (!texture.back()->loadFromImage(i)) {
				throw "Texture not loaded!";
			}
			texture.back()->setSmooth(true);
		}
		if (transparencyM)
			loadTransparancy(images.front());
		if (images.size() >= 2)
			m_type = ObjectType::Multi;
		else
			m_type = ObjectType::Single;
		m_size.x = texture.front()->getSize().x;
		m_size.y = texture.front()->getSize().y;
	}

	inline bool Object::draw(sf::RenderWindow& window)
	{
		if (m_type == MEP::Object::ObjectType::Single or m_type == MEP::Object::ObjectType::Multi)
			window.draw(sf::Sprite(*texture.front()));
		return true;
	}

	inline Object::~Object()
	{
		deleteObject();
	}
}