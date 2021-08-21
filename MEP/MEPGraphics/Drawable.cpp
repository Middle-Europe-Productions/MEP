#include<MEPGraphics/Drawable.h>

namespace MEP
{
	void Drawable::notify() {
		if (link) {
			*link = false;
		}
	}

	void Drawable::drawTagDebug(std::ostream& out) const {
		out << "MEP::Drawable: { ";
		if (m_drawTag & Non)
			out << "Non ";
		if (m_drawTag & ViewLock)
			out << "ViewLock ";
		if (m_drawTag & Unactive)
			out << "Unactive ";
		if (m_drawTag & Resize_Pos)
			out << "Resize_Pos ";
		if (m_drawTag & Resize_Scale)
			out << "Resize_Scale ";
		if (m_drawTag & Resize_Rect)
			out << "Resize_Rect ";
		out << "}";
	}

	void Drawable::_link(std::shared_ptr<bool> _li) {
		link = _li;
	}

	std::shared_ptr<bool> Drawable::_linkAddr() {
		return link;
	}

	const std::shared_ptr<bool> Drawable::_linkAddr() const {
		return link;
	}

	bool Drawable::_isLinked() const {
		return link != nullptr;
	}

	U_int32 MEP::Drawable::getDrawTag() const {
		return m_drawTag;
	}

	void Drawable::setDrawTag(const U_int32 tag) {
		m_drawTag = tag;
	}

	bool Drawable::addDrawTag(const U_int32 tag) {
		if (tag & m_drawTag)
			return false;
		else
			m_drawTag |= tag;
		return true;
	}

	bool Drawable::removeDrawTag(const U_int32 tag) {
		if (!(tag & m_drawTag))
			return false;
		else
			m_drawTag ^= tag;
		return true;
	}

	void Drawable::onResize()
	{}

	bool Drawable::draw(sf::RenderWindow&)
	{
		return false;
	}

	void Drawable::update(sf::Time&)
	{};

	void Drawable::entryUpdate(sf::Time& currentTime, bool low)
	{
		update(currentTime);
	};

	void Drawable::exitUpdate(sf::Time& currentTime, bool low)
	{
		update(currentTime);
	};

	bool Drawable::isActive() const
	{
		return false;
	};

	void Drawable::debugOutput(std::ostream& out) const {
		drawTagDebug(out);
	}

	Drawable::~Drawable() {
		notify();
	}

	std::ostream& operator<<(std::ostream& out, const Drawable& x) {
		x.debugOutput(out);
		return out;
	}
}