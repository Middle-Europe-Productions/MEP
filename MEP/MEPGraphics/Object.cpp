////////////////////////////////////////////////////////////
//
//	Object.cpp created with the use of SFML
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
#include<MEPGraphics/Object.h>
#include<MEPTools/Log.h>
namespace MEP
{
	void Object::allocateTable(const sf::Vector2u& size)
	{
		Log(3) << "Allocating transparency table";
		table = new bool* [size.x];
		for (unsigned int i = 0; i < size.x; ++i)
			table[i] = new bool[size.y];
	}
	template<typename X>
	void Object::createTable(const sf::Vector2u& size, X method)
	{
		Log(1) << "Creating transparency table";
		if (table) {
			for (unsigned int i = 0; i < size.x; i++) {
				for (unsigned int j = 0; j < size.y; j++) {
					table[i][j] = method(i, j);//surface.getPixel(i, j).a < 100;
				}
			}
			transparency = true;
		}
	}
	void Object::loadTransparancy(const sf::Image& surface)
	{
		//allocate table
		allocateTable(surface.getSize());
		//fill table
		createTable(surface.getSize(), [&surface](const auto& x, const auto& y) {
			return surface.getPixel(x, y).a < 100;
			});
	}

	void Object::load(const std::string& fulladdress, bool transparencyM, bool masterSize) {
		Log(3) << "Loading texture from address: " << fulladdress;
		texture->push_back(new sf::Texture());
		if (!texture->back()->loadFromFile(fulladdress)) {
			Log(Fatal) << "Could not load a texture! Address: " << fulladdress;
			throw "Texture not loaded!";
		}
		texture->back()->setSmooth(true);
		if (transparencyM) {
			sf::Image x;
			if (!x.loadFromFile(fulladdress)) {
				Log(Fatal) << "Could not load a transparency mask! Address: " << fulladdress;
				throw "Transparency mask not loaded!";
			}
			loadTransparancy(x);
		}
		if (masterSize) {
			m_size.x = texture->front()->getSize().x;
			m_size.y = texture->front()->getSize().y;
		}
	}

	const sf::Vector2u& Object::getSize() const {
		return m_size;
	};

	unsigned long Object::getNufTextures() const {
		if (!texture)
			return 0;
		return texture->size();
	}

	void Object::deleteObject()
	{
		Log(3) << "Object deleting process, Name: " << m_name << ", ID: " << m_ID;
		if (m_nufC)
		{
			if (*m_nufC == 0) {
				if (table != nullptr) {
					for (unsigned int i = 0; i < m_size.x; i++) {
						delete[] table[i];
					}
					delete[] table;
				}
				for (auto x = texture->begin(); x != texture->end(); x++)
					delete* x;
				delete m_nufC;
				delete texture;
			}
			else {
				*m_nufC -= 1;
			}
		}
		else
		{
			Log(5) << "Object, Name: " << m_name << ", ID: " << m_ID << " does not own any copies, probably a shallow copy";
		}
	}

	void Object::update(sf::Time&)
	{};

	void Object::entryUpdate(sf::Time& currentTime, bool low) {
		update(currentTime);
	};

	void Object::exitUpdate(sf::Time& currentTime, bool low) {
		update(currentTime);
	};

	Object* Object::getObjectPoint()
	{
		*m_nufC += 1;
		return this;
	}

	Object& Object::getObjectRef()
	{
		return *this;
	}

	const MEP::U_int32& Object::getID() const
	{
		return m_ID;
	}

	const std::string& Object::getName() const
	{
		return m_name;
	}

	bool Object::isTansparent(unsigned int x, unsigned int y)
	{
		if (transparency and x < m_size.x and y < m_size.y)
			return table[x][y];
		Log(Warning) << "Transparency table was not created for this object.";
		return true;
	}

	Object::Object(Object&& x) noexcept:
		m_ID(x.m_ID),
		m_name(x.m_name),
		transparency(x.transparency),
		table(x.table),
		m_size(x.m_size),
		texture(std::move(x.texture)),
		m_type(x.m_type)
	{
		Log(3) << "Creating MEP::Object, ID: " << m_ID << ", Name: " << m_name << ", move constructor. ";
		m_nufC = x.m_nufC;
		*m_nufC = 1;
		x.table = nullptr;
		x.m_nufC = nullptr;
	}

	Object::Object(const Object& x) :
		m_ID(x.m_ID),
		m_name(x.m_name),
		transparency(x.transparency),
		table(x.table),
		m_size(x.m_size),
		texture(x.texture),
		m_type(x.m_type)
	{
		Log(3) << "Creating MEP::Object, ID: " << m_ID << ", Name: " << m_name << ", copy constructor. ";
		m_nufC = x.m_nufC;
		*m_nufC += 1;
	}

	Object::Object(const U_int32 ID, const std::string& path, const std::string& filename, bool transparencyM) :
		m_nufC(new int(0)),
		m_ID(ID),
		m_name(filename),
		texture(nullptr),
		m_type(ObjectType::Single)
	{
		Log(3) << "Creating MEP::Object, ID: " << m_ID << ", Name: " << m_name << ", single constructor. ";
		texture = new std::list<sf::Texture*>;
		load(path + filename + ".png", transparencyM, true);
	}

	Object::Object(const U_int32 ID, const std::string& path, const std::string& filename, unsigned int frames, bool transparencyM) :
		m_nufC(new int(0)),
		m_ID(ID),
		m_name(filename),
		texture(nullptr),
		m_type(ObjectType::Multi)
	{
		Log(3) << "Creating MEP::Object, ID: " << m_ID << ", Name: " << m_name << ", multi constructor. ";
		texture = new std::list<sf::Texture*>;
		for (unsigned int i = 0; i < frames; i++) {
			load(path + filename + std::to_string(i) + ".png", transparencyM and i == 0, i == 0);
		}
	}

	Object::Object(const U_int32 ID, std::list<sf::Image>& images, const std::string& filename, bool transparencyM) :
		m_nufC(new int(0)),
		m_ID(ID),
		m_name(filename),
		transparency(false),
		texture(nullptr)
	{
		Log(3) << "Creating MEP::Object, ID: " << m_ID << ", Name: " << m_name << ", images table ready constructor. ";
		texture = new std::list<sf::Texture*>;
		for (auto& i : images) {
			texture->push_back(new sf::Texture());
			if (!texture->back()->loadFromImage(i)) {
				throw "Texture not loaded!";
			}
			texture->back()->setSmooth(true);
		}
		if (transparencyM)
			loadTransparancy(images.front());
		if (images.size() >= 2)
			m_type = ObjectType::Multi;
		else
			m_type = ObjectType::Single;
		m_size.x = texture->front()->getSize().x;
		m_size.y = texture->front()->getSize().y;
	}

	Object::Object(const U_int32 ID, const sf::Image& image, const std::string& filename, bool transparencyM) :
		m_nufC(new int(0)),
		m_ID(ID),
		m_name(filename),
		transparency(false),
		texture(nullptr)
	{
		Log(3) << "Creating MEP::Object, ID: " << m_ID << ", Name: " << m_name << ", image ready constructor. ";
		texture = new std::list<sf::Texture*>;
		texture->push_back(new sf::Texture());
		if (!texture->back()->loadFromImage(image)) {
			throw "Texture not loaded!";
		}
		texture->back()->setSmooth(true);
		if (transparencyM)
			loadTransparancy(image);
		m_type = ObjectType::Single;
		m_size.x = texture->front()->getSize().x;
		m_size.y = texture->front()->getSize().y;
	}

	bool Object::draw(sf::RenderWindow& window)
	{
		if (m_type == MEP::Object::ObjectType::Single or m_type == MEP::Object::ObjectType::Multi)
			window.draw(sf::Sprite(*texture->front()));
		return true;
	}

	bool Object::isActive() const {
		return false;
	};

	const Object::ObjectType& MEP::Object::getType() const {
		return m_type;
	}

	unsigned int Object::nufC() const {
		return *m_nufC;
	}

	bool Object::operator==(const std::string& x) const {
		return x == m_name;
	}

	bool Object::operator==(const Object& x) const {
		return x.getName() == m_name;
	}

	void Object::debugOutput(std::ostream& out) const {
		out << "MEP::Object, ID: " << getID() << ", name : " << getName();
	}

	std::ostream& operator<<(std::ostream& out, const Object& x) {
		x.debugOutput(out);
		return out;
	}

	Object::~Object()
	{
		deleteObject();
		notify();
	}
}