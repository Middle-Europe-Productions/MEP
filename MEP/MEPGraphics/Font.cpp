#include<MEPGraphics/Font.h>

namespace MEP
{
	Font::Font(U_int32 ID, const std::string& name, const std::string& path) : m_ID(ID), m_name(name)
	{
		if (!m_font.loadFromFile(path + name))
			throw ResourceException("path", "Could not load the font!", ResourceException::ExceptionType::CouldntLoadFont);
	}

	U_int32 Font::getID() const
	{
		return m_ID;
	}

	const std::string& Font::getName() const
	{
		return m_name;
	}

	sf::Font& Font::getFont()
	{
		return m_font;
	}
}