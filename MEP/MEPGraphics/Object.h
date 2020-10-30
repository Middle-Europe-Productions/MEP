
////////////////////////////////////////////////////////////
//
//	Object.h created with the use of SFML
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
#include<SFML/Graphics.hpp>
#include"Drawable.h"
#include<list>
#include<string>
#include<iostream>
namespace MEP {
	class Object: public Drawable {
	public:
		//types on an object
		enum class ObjectType {
			NotInit,
			Single,
			Multi,
			Text
		};
	private:
		//number of copies 
		int nufC = 0;
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
	public:
		Object() = default;
		Object(const Object& x) : m_name(x.m_name), transparency(x.transparency), table(x.table), m_size(x.m_size), texture(x.texture), m_type(x.m_type) { nufC++; }
		Object(const std::string& path, const std::string& filename, bool transparencyM = false);
		Object(const std::string& path, const std::string& filename, unsigned int frames, bool transparencyM = false);
		Object(std::list<sf::Image>& images, const std::string& filename, unsigned int frames, bool transparencyM = false);
		//returning size of an object
		const sf::Vector2u& getSize() const { return m_size; };
		//number of frames in the array 
		unsigned long GetNufTextures() const { return texture.size(); }
		//virtual draw function
		void draw(sf::RenderWindow& window);
		//virtual update functions
		void update(sf::Time& currentTime) {};
		void entryUpdate(sf::Time& currentTime) { update(currentTime); };
		void exitUpdate(sf::Time& currentTime) { update(currentTime);  };
		//new copy of the element
		Object* GetObjectPoint() { nufC++;  return this; }
		//reference to an object
		Object& GetObjectRef() { return *this; }
		//id verification and processing
		const std::string& GetName() const { return m_name; }
		//checks the transparency of an object  for the default SDL_Rect
		virtual bool isTansparent(unsigned int x, unsigned int y);
		//returns activity of an object it is mainly related to the associated animations
		bool IsActive() const { return false; };
		//returns a type of an object
		const ObjectType& GetType() const { return m_type; }
		bool operator==(const std::string& x) const { return x == m_name; }
		bool operator==(const Object& x) const { return x.GetName() == m_name; }
		virtual ~Object();
	}; 
	
	inline void MEP::Object::loadTransparancy(sf::Image& surface)
	{
		//allocate table
		table = new bool* [surface.getSize().x];
		for (int i = 0; i < surface.getSize().x; ++i)
			table[i] = new bool[surface.getSize().y];
		//fill table
		for (int i = 0; i < surface.getSize().x; i++) {
			for (int j = 0; j < surface.getSize().y; j++) {
				table[i][j] = surface.getPixel(i, j).a < 100;
			}
		}
		transparency = true;
	}

	inline void MEP::Object::load(const std::string& fulladdress, bool transparencyM, bool masterSize) {
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

	inline bool MEP::Object::isTansparent(unsigned int x, unsigned int y)
	{
		if (transparency and x < m_size.x and y < m_size.y)
			return table[x][y];
		return true;
	}

	inline MEP::Object::Object(const std::string& path, const std::string& filename, bool transparencyM) : m_name(filename),
		m_type(ObjectType::Single)
	{
		load(path + filename + ".png", transparencyM, true);
	}

	inline MEP::Object::Object(const std::string& path, const std::string& filename, unsigned int frames, bool transparencyM) :
		m_name(filename), 
		m_type(ObjectType::Multi)
	{
		for (int i = 0; i < frames; i++) {
			load(path + filename + std::to_string(i) + ".png", transparencyM and i == 0, i == 0);
		}
	}

	inline Object::Object(std::list<sf::Image>& images, const std::string& filename, unsigned int frames, bool transparencyM):
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

	inline void MEP::Object::draw(sf::RenderWindow& window)
	{
		if (m_type == MEP::Object::ObjectType::Single or m_type == MEP::Object::ObjectType::Multi)
			window.draw(sf::Sprite(*texture.front()));
	}

	inline MEP::Object::~Object()
	{
		if (transparency and nufC == 0 and table != nullptr) {
			delete[] table;
			for (auto x = texture.begin(); x != texture.end(); x++)
				delete* x;
		}
		else {
			nufC--;
		}
	}
}