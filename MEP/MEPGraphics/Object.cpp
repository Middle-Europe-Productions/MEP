#include<MEPGraphics/Object.h>

namespace MEP
{
	void Object::loadTransparancy(sf::Image& surface)
	{
		//allocate table
		table = new bool* [surface.getSize().x];
		for (unsigned int i = 0; i < surface.getSize().x; ++i)
			table[i] = new bool[surface.getSize().y];
		//fill table
		if (table) {
			for (unsigned int i = 0; i < surface.getSize().x; i++) {
				for (unsigned int j = 0; j < surface.getSize().y; j++) {
					table[i][j] = surface.getPixel(i, j).a < 100;
				}
			}
			transparency = true;
		}
	}

	void Object::load(const std::string& fulladdress, bool transparencyM, bool masterSize) {
		texture->push_back(new sf::Texture());
		if (!texture->back()->loadFromFile(fulladdress)) {
			throw "Texture not loaded!";
		}
		texture->back()->setSmooth(true);
		if (transparencyM) {
			sf::Image x;
			if (!x.loadFromFile(fulladdress)) {
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
		return true;
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