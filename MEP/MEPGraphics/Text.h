////////////////////////////////////////////////////////////
//
// WARNING
// This file is a SLIGHTLY modified version of the SFML/Text module.
// I do not own any rights for that file.
//
////////////////////////////////////////////////////////////
// Here is the license on the original file:
//
// SFML - Simple and Fast Multimedia Library
// Copyright (C) 2007-2021 Laurent Gomila (laurent@sfml-dev.org)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
////////////////////////////////////////////////////////////

#ifndef MEP_TEXT_2_H
#define MEP_TEXT_2_H
#include<SFML/Graphics/Drawable.hpp>
#include<SFML/Graphics/Color.hpp>
#include<SFML/Graphics/VertexArray.hpp>
#include<SFML/Graphics/Rect.hpp>

#include<MEPGraphics/Following.h>
#include<MEPGraphics/Drawable.h>
#include<MEPGraphics/Config.h>									
#include<MEPWindow/Log.h>

namespace MEPdev
{
    namespace
    {
        // Add an underline or strikethrough line to the vertex array
        void addLine(sf::VertexArray& vertices, float lineLength, float lineTop, const sf::Color& color, float offset, float thickness, float outlineThickness = 0)
        {
            float top = std::floor(lineTop + offset - (thickness / 2) + 0.5f);
            float bottom = top + std::floor(thickness + 0.5f);

            vertices.append(sf::Vertex(sf::Vector2f(-outlineThickness, top - outlineThickness), color, sf::Vector2f(1, 1)));
            vertices.append(sf::Vertex(sf::Vector2f(lineLength + outlineThickness, top - outlineThickness), color, sf::Vector2f(1, 1)));
            vertices.append(sf::Vertex(sf::Vector2f(-outlineThickness, bottom + outlineThickness), color, sf::Vector2f(1, 1)));
            vertices.append(sf::Vertex(sf::Vector2f(-outlineThickness, bottom + outlineThickness), color, sf::Vector2f(1, 1)));
            vertices.append(sf::Vertex(sf::Vector2f(lineLength + outlineThickness, top - outlineThickness), color, sf::Vector2f(1, 1)));
            vertices.append(sf::Vertex(sf::Vector2f(lineLength + outlineThickness, bottom + outlineThickness), color, sf::Vector2f(1, 1)));
        }

        // Add a glyph quad to the vertex array
        void addGlyphQuad(sf::VertexArray& vertices, sf::Vector2f position, const sf::Color& color, const sf::Glyph& glyph, float italicShear, float outlineThickness = 0)
        {
            float padding = 1.0;

            float left = glyph.bounds.left - padding;
            float top = glyph.bounds.top - padding;
            float right = glyph.bounds.left + glyph.bounds.width + padding;
            float bottom = glyph.bounds.top + glyph.bounds.height + padding;

            float u1 = static_cast<float>(glyph.textureRect.left) - padding;
            float v1 = static_cast<float>(glyph.textureRect.top) - padding;
            float u2 = static_cast<float>(glyph.textureRect.left + glyph.textureRect.width) + padding;
            float v2 = static_cast<float>(glyph.textureRect.top + glyph.textureRect.height) + padding;

            vertices.append(sf::Vertex(sf::Vector2f(position.x + left - italicShear * top - outlineThickness, position.y + top - outlineThickness), color, sf::Vector2f(u1, v1)));
            vertices.append(sf::Vertex(sf::Vector2f(position.x + right - italicShear * top - outlineThickness, position.y + top - outlineThickness), color, sf::Vector2f(u2, v1)));
            vertices.append(sf::Vertex(sf::Vector2f(position.x + left - italicShear * bottom - outlineThickness, position.y + bottom - outlineThickness), color, sf::Vector2f(u1, v2)));
            vertices.append(sf::Vertex(sf::Vector2f(position.x + left - italicShear * bottom - outlineThickness, position.y + bottom - outlineThickness), color, sf::Vector2f(u1, v2)));
            vertices.append(sf::Vertex(sf::Vector2f(position.x + right - italicShear * top - outlineThickness, position.y + top - outlineThickness), color, sf::Vector2f(u2, v1)));
            vertices.append(sf::Vertex(sf::Vector2f(position.x + right - italicShear * bottom - outlineThickness, position.y + bottom - outlineThickness), color, sf::Vector2f(u2, v2)));
        }
    }
	using namespace MEP;
	class Text : public sf::Drawable, public Drawable, public Following
	{
    public:
        /**
		* @enum MEP::Text::Style
        * Enumeration of the string drawing styles
        */
        enum Style {
            Regular = 0, /** Regular characters, no style */ 
            Bold = 1 << 0, /**Bold characters */
            Italic = 1 << 1, /** Italic characters */
            Underlined = 1 << 2, /** Underlined characters */
            StrikeThrough = 1 << 3,  /** Strike through characters */
            Background = 1 << 4 /** Enables background */
        };
		/**
		* @enum MEP::Text::PositionTag
		* Defines an additional tag to the position of a text.
		*/
		enum class PositionTag {
			/** Position.x and Position.y are the top left corner of the text.*/
			Non,
			/** Position.y is not changed while Position.x is in the middle of the text.*/
			XMiddle,
			/** Position.x is not changed while Position.y is in the middle of the text.*/
			YMiddle,
			/** Both Postition.x and Position.y are exactly in the middle of the text.*/
			Middle
		};
	private:
		/**
		* This is a m_tag guard.
		* When false it basically means that position tah has not been applied.
		*/
		bool tagApplied = false;
		/**
		* Position tag. It infuances the origin of the Text.
		*/
		PositionTag m_tag = PositionTag::Non;
        /**
        * String to display
        */
		sf::String m_string;
        /**
        * Font used to display the string
        */
		const sf::Font* m_font;
        /**
        * Base size of characters, in pixels
        */
		unsigned int m_characterSize;
        /**
        * Spacing factor between letters
        */
		float m_letterSpacingFactor;
        /**
        * Spacing factor between lines
        */
		float m_lineSpacingFactor;
        /**
        * Text style (see Style enum)
        */
        MEP::U_int32 m_style;
        /**
        * Text outline color.
        */
        sf::Color m_outlineColor;
        /**
        * Color of the background.
        */
        sf::Color m_fillColor;
        /**
        * Thickness of the text's outline
        */
        float m_outlineThickness;
        /**
        * Vertex array containing the fill geometry
        */
		mutable sf::VertexArray m_vertices;
        /**
        * Vertex array containing the outline geometry
        */
		mutable sf::VertexArray m_outlineVertices;
        /**
        * Vertex array containing the background geometry
        */
        mutable sf::VertexArray m_backgroundVertices;
		/**
        * Bounding rectangle of the text (in local coordinates)
        */
        mutable sf::FloatRect m_bounds;
		/**
        * Does the geometry need to be recomputed?
        */
        mutable bool m_geometryNeedUpdate;
        /**
        * The font texture id
        */
		mutable MEP::U_int64 m_fontTextureId;
        /**
        * Transform of an object.
        */
        mutable sf::Transform m_transform;
        /**
        * Increases the background bound.
        */
        float backgroundYBounds = 0;
        /**
        * Updates the origin status.
        */
        void updateTag()
        {
            if (m_tag == PositionTag::Middle) {
                setOrigin({ getLocalBounds().width / 2,
                     (float)getCharacterSize() / 2 + ((float)getCharacterSize() - getLocalBounds().height) / 2 });
            }
            else if (m_tag == PositionTag::XMiddle) {
                setOrigin({ getLocalBounds().width / 2,
                     0 });
            }
            else if (m_tag == PositionTag::YMiddle) {
                setOrigin({ 0,
                     (float)getCharacterSize() / 2 + ((float)getCharacterSize() - getLocalBounds().height) / 2 });
            }
            tagApplied = true;
        }
	public:
		/**
		* Constructor of a text.
		* @param[in] context : This goes on your screen.
		* @param[in] font : Font of a Text.
		* @param[in] fontSize : Size of the font.
		* @param[in] position : Position on the screen.
		* @param[in] tag : MEP::TextOboject::PositionTag
		*/
		Text(const sf::String& content,
			sf::Font& font,
			unsigned int fontSize = 40,
			sf::Vector2f position = { 0, 0 },
			PositionTag tag = PositionTag::Non):
            Following(position, position),
            m_tag(tag),
            m_string(content),
            m_font(&font),
            m_characterSize(fontSize),
            m_letterSpacingFactor(1.f),
            m_lineSpacingFactor(1.f),
            m_style(Regular),
            m_outlineColor(0, 0, 0),
            m_outlineThickness(0),
            m_vertices(sf::Triangles),
            m_outlineVertices(sf::Triangles),
            m_backgroundVertices(sf::Triangles),
            m_bounds(),
            m_geometryNeedUpdate(true),
            m_fontTextureId(0)
		{
            updateTag();
		}
		/**
		* Constructor of a text.
		* @param[in] context : This goes on your screen.
		* @param[in] font : Font of a Text.
		* @param[in] fontSize : Size of the font.
		* @param[in] position : Position on the screen.
		* @param[in] tag : MEP::TextOboject::PositionTag
		*/
		Text(const sf::String& content,
			sf::Font& font,
			const Following& follow,
			unsigned int fontSize = 40,
			PositionTag tag = PositionTag::Non):
            m_tag(tag),
            m_string(content),
            m_font(&font),
            m_characterSize(fontSize),
            m_letterSpacingFactor(1.f),
            m_lineSpacingFactor(1.f),
            m_style(Regular),
            m_outlineColor(0, 0, 0),
            m_outlineThickness(0),
            m_vertices(sf::Triangles),
            m_outlineVertices(sf::Triangles),
            m_backgroundVertices(sf::Triangles),
            m_bounds(),
            m_geometryNeedUpdate(true),
            m_fontTextureId(0)
		{
            updateTag();
		}
        Text& operator<<(const Sprite& x) {
            (Following&)(*this) << x;
            return *this;
        }
        Text& operator<<(const Text& x) {
            if (this != &x) {
                (Following&)(*this) << x;
            }
            return *this;
        }
        /**
        * Sets the text. 
        * @param[in] string : Input text.
        */
        void setString(const sf::String& string)
        {
            if (m_string != string)
            {
                m_string = string;
                m_geometryNeedUpdate = true;
            }
        }
        /**
        * Sets the font.
        * @param[in] font : sf::Font
        */
        void setFont(const sf::Font& font)
        {
            if (m_font != &font)
            {
                m_font = &font;
                m_geometryNeedUpdate = true;
            }
        }
        /**
        * Character size.
        */
        void setCharacterSize(unsigned int size)
        {
            if (m_characterSize != size)
            {
                m_characterSize = size;
                m_geometryNeedUpdate = true;
            }
        }

        /**
        * Custom spacing between lines.
        */
        void setLineSpacing(float spacingFactor)
        {
            if (m_lineSpacingFactor != spacingFactor)
            {
                m_lineSpacingFactor = spacingFactor;
                m_geometryNeedUpdate = true;
            }
        }
        /**
        * Custom spacing between letters.
        */
        void setLetterSpacing(float spacingFactor)
        {
            if (m_letterSpacingFactor != spacingFactor)
            {
                m_letterSpacingFactor = spacingFactor;
                m_geometryNeedUpdate = true;
            }
        }
        /**
        * Set the style of a text.
        */
        void setStyle(MEP::U_int32 style)
        {
            if (m_style != style)
            {
                m_style = style;
                m_geometryNeedUpdate = true;
            }
        }
        /**
        * On resize we want to update the position.
        */
        void onResize() override {
            if (getDrawTag() & DrawTag::Resize_Scale)
                updateScale();
            if (getDrawTag() & DrawTag::Resize_Pos)
                updatePosition();
        }
        /**
        * Sets the color of the text.
        */
        void setColor(const sf::Color& color) {
            if (color != Following::getColor())
            {
                Following::setColor(color);
                // Change vertex colors directly, no need to update whole geometry
                // (if geometry is updated anyway, we can skip this step)
                if (!m_geometryNeedUpdate)
                {
                    for (std::size_t i = 0; i < m_vertices.getVertexCount(); ++i)
                        m_vertices[i].color = Following::getColor();
                }
            }
        }
        /**
        * Sets the color of the background.
        */
        void setBackgroundColor(const sf::Color& color)
        {
            if (color != m_fillColor)
            {
                m_fillColor = color;

                // Change vertex colors directly, no need to update whole geometry
                // (if geometry is updated anyway, we can skip this step)
                if (!m_geometryNeedUpdate)
                {
                    for (std::size_t i = 0; i < m_backgroundVertices.getVertexCount(); ++i)
                        m_backgroundVertices[i].color = m_fillColor;
                }
            }
        }
        /**
        * Increases the size of the background Y bounds.
        * Value is a percentage increase in size.
        * For example, when font size is 60, and you set bound to 10 it will increase the size by 6.
        */
        void setBackgroundBoundsY(float bound)
        {
            if (bound != backgroundYBounds)
            {
                backgroundYBounds = bound;
                m_geometryNeedUpdate = true;
            }
        }
        /**
        * Sets the color of the outline.
        */
        void setOutlineColor(const sf::Color& color)
        {
            if (color != m_outlineColor)
            {
                m_outlineColor = color;

                // Change vertex colors directly, no need to update whole geometry
                // (if geometry is updated anyway, we can skip this step)
                if (!m_geometryNeedUpdate)
                {
                    for (std::size_t i = 0; i < m_outlineVertices.getVertexCount(); ++i)
                        m_outlineVertices[i].color = m_outlineColor;
                }
            }
        }
        /**
        * Sets the thickness of the ontline.
        */
        void setOutlineThickness(float thickness)
        {
            if (thickness != m_outlineThickness)
            {
                m_outlineThickness = thickness;
                m_geometryNeedUpdate = true;
            }
        }
        /**
        * Outputs the string.
        */
        const sf::String& getString() const
        {
            return m_string;
        }
        /**
        * Outputs the font.
        */
        const sf::Font* getFont() const 
        {
            return m_font;
        }
        /**
        * Outputs the size of the font.
        */
        unsigned int getCharacterSize() const
        {
            return m_characterSize;
        }
        /**
        * Outputs the letter spacing.
        */
        float getLetterSpacing() const
        {
            return m_letterSpacingFactor;
        }
        /**
        * Outputs the line spacing.
        */
        float getLineSpacing() const
        {
            return m_lineSpacingFactor;
        }
        /**
        * Outputs a style.
        * @return : MEP::Text::Style
        */
        MEP::U_int32 getStyle() const
        {
            return m_style;
        }
        /**
        * Outputs a color of the text.
        * @return : Color
        */
        const sf::Color& getColor() const
        {
            return Following::getColor();
        }
        /**
        * Outputs a outline color of the text.
        * @return : Color
        */
        const sf::Color& getOutlineColor() const {
            return m_outlineColor;
        }
        /**
        * Outputs a background color of the text.
        * @return : Color
        */
        const sf::Color& getFillColor() const {
            return m_fillColor;
        }
        /**
        * Ouputs the line thinckness.
        */
        float getOutlineThickness() const {
            return m_outlineThickness;
        }
        /**
        * Outputs the local bound of an object.
        */
        sf::FloatRect getLocalBounds() const {
            ensureGeometryUpdate();
            return m_bounds;
        }
        /**
        * Outputs the global bound of an object.
        */
        sf::FloatRect getGlobalBounds() const {
            return getTransform().transformRect(getLocalBounds());
        }
        /**
        * Override of the update method.
        */
        void update(sf::Time&) override
        {
            followingListv2._execute([&](auto& x) {
                x.get()->updateVariables(*this);
                });
        }
        /**
        * Set background.
        */
        bool backgroundStart(const sf::Vector2f& pos)
        {
            backgroundReset();
            // Make sure that we have a valid font
            if (!m_font)
                return false;

            // Precompute the variables needed by the algorithm
            bool  isBold = m_style & Bold;
            float whitespaceWidth = m_font->getGlyph(L' ', m_characterSize, isBold).advance;
            float letterSpacing = (whitespaceWidth / 3.f) * (m_letterSpacingFactor - 1.f);
            whitespaceWidth += letterSpacing;
            float lineSpacing = m_font->getLineSpacing(m_characterSize) * m_lineSpacingFactor;

            // Compute the position
            sf::Vector2f position;
            sf::Uint32 prevChar = 0;
            for (std::size_t i = 0; i < m_string.getSize(); ++i)
            {
                sf::Uint32 curChar = m_string[i];

                // Apply the kerning offset
                position.x += m_font->getKerning(prevChar, curChar, m_characterSize);
                prevChar = curChar;

                // Handle special characters
                switch (curChar)
                {
                case ' ':  position.x += whitespaceWidth;             continue;
                case '\t': position.x += whitespaceWidth * 4;         continue;
                case '\n': position.y += lineSpacing; position.x = 0; continue;
                }

                // For regular characters, add the advance offset of the glyph
                position.x += m_font->getGlyph(curChar, m_characterSize, isBold).advance + letterSpacing;
                auto local_position = getTransform().transformPoint(position);
                Log(Debug) << " position.x: " << local_position.x << ", character: " << static_cast<char>(m_string[i]);
            }

            // Transform the position to global coordinates
            
        }
        /**
        * Background update.
        */
        void backgroundUpdate(const sf::Vector2f& pos)
        {

        }
        /**
        * Resets the background.
        */
        void backgroundReset()
        {
            m_backgroundVertices.clear();
        }
	private:
        /**
        * Classic override of the SFML draw method from sf::Drawable.
        */
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override 
        {
            if (m_font)
            {
                ensureGeometryUpdate();

                states.transform *= getTransform();
                states.texture = &m_font->getTexture(m_characterSize);

                // Only draw the outline if there is something to draw
                if (m_outlineThickness != 0)
                    target.draw(m_outlineVertices, states);
                if (m_style & Text::Background)
                    target.draw(m_backgroundVertices, states);

                target.draw(m_vertices, states);
            }
		}
        /**
        *	Ovveride of the draw method.
        *	@param[in] window : Classic sf::RenderWindow
        */
        bool draw(sf::RenderWindow& window) override
        {
            window.draw(*this);
            return true;
        }
        /**
        * Updates the transform of an object.
        */
        const sf::Transform& getTransform() const
        {
            // Recompute the combined transform if needed
            if (originStatus() or positionStatus() or scaleStatus())
            {
                Log(Info) << "Updating text transform: " 
                    << std::string(getString()) 
                    << ", parameters changed: originStatus(): " << (originStatus() ? "true": "false")
                    << ", positionStatus(): " << (positionStatus() ? "true" : "false")
                    << ", scaleStatus(): " << (scaleStatus() ? "true" : "false");
                float angle = 0;//-m_rotation * 3.141592654f / 180.f;
                float cosine = static_cast<float>(std::cos(angle));
                float sine = static_cast<float>(std::sin(angle));
                float sxc = getScale().x * cosine;
                float syc = getScale().y * cosine;
                float sxs = getScale().x * sine;
                float sys = getScale().y * sine;
                float tx = -getOrigin().x * sxc - getOrigin().y * sys + getPosition().x;
                float ty = getOrigin().x * sxs - getOrigin().y * syc + getPosition().y;
                m_transform = sf::Transform(sxc, sys, tx,
                    -sxs, syc, ty,
                    0.f, 0.f, 1.f);
                resetPositionStatus();
                resetScaleStatus();
                resetOriginStatus();
            }

            return m_transform;
        }
        /**
        * \brief Modified SFML Text method.
		* 
        * According to SFML 2.5.1:
		* All the attributes related to rendering are cached, such
		* that the geometry is only updated when necessary.
        */
		void ensureGeometryUpdate() const {
            if (!m_font)
                return;

            // Do nothing, if geometry has not changed and the font texture has not changed
            if (!m_geometryNeedUpdate)// && m_font->getTexture(m_characterSize).m_cacheId == m_fontTextureId)
                return;

            // Save the current fonts texture id
            //m_fontTextureId = m_font->getTexture(m_characterSize).m_cacheId;

            // Mark geometry as updated
            m_geometryNeedUpdate = false;

            // Clear the previous geometry
            m_vertices.clear();
            m_outlineVertices.clear();
            m_backgroundVertices.clear();
            m_bounds = sf::FloatRect();

            // No text: nothing to draw
            if (m_string.isEmpty())
                return;

            // Compute values related to the text style
            bool isBold = m_style & Bold;
            bool isUnderlined = m_style & Underlined;
            bool isStrikeThrough = m_style & StrikeThrough;
            bool isBackground = m_style & Background;
            float italicShear = (m_style & Italic) ? 0.209f : 0.f; // 12 degrees in radians
            float underlineOffset = m_font->getUnderlinePosition(m_characterSize);
            float underlineThickness = m_font->getUnderlineThickness(m_characterSize);
            float backgroundThickness = static_cast<float>(m_characterSize) + static_cast<float>(m_characterSize) * (backgroundYBounds / 100.f);
            // Compute the location of the strike through dynamically
            // We use the center point of the lowercase 'x' glyph as the reference
            // We reuse the underline thickness as the thickness of the strike through as well
            sf::FloatRect xBounds = m_font->getGlyph(L'x', m_characterSize, isBold).bounds;
            float strikeThroughOffset = xBounds.top + xBounds.height / 2.f;

            // Precompute the variables needed by the algorithm
            float whitespaceWidth = m_font->getGlyph(L' ', m_characterSize, isBold).advance;
            float letterSpacing = (whitespaceWidth / 3.f) * (m_letterSpacingFactor - 1.f);
            whitespaceWidth += letterSpacing;
            float lineSpacing = m_font->getLineSpacing(m_characterSize) * m_lineSpacingFactor;
            float x = 0.f;
            float y = static_cast<float>(m_characterSize);

            // Create one quad for each character
            float minX = static_cast<float>(m_characterSize);
            float minY = static_cast<float>(m_characterSize);
            float maxX = 0.f;
            float maxY = 0.f;
            MEP::U_int32 prevChar = 0;
            for (std::size_t i = 0; i < m_string.getSize(); ++i)
            {
                MEP::U_int32 curChar = m_string[i];

                // Skip the \r char to avoid weird graphical issues
                if (curChar == '\r')
                    continue;

                // Apply the kerning offset
                x += m_font->getKerning(prevChar, curChar, m_characterSize);

                // If we're using the underlined style and there's a new line, draw a line
                if (isUnderlined && (curChar == L'\n' && prevChar != L'\n'))
                {
                    addLine(m_vertices, x, y, Following::getColor(), underlineOffset, underlineThickness);

                    if (m_outlineThickness != 0)
                        addLine(m_outlineVertices, x, y, m_outlineColor, underlineOffset, underlineThickness, m_outlineThickness);
                }

                // If we're using the strike through style and there's a new line, draw a line across all characters
                if (isStrikeThrough && (curChar == L'\n' && prevChar != L'\n'))
                {
                    addLine(m_vertices, x, y, Following::getColor(), strikeThroughOffset, underlineThickness);

                    if (m_outlineThickness != 0)
                        addLine(m_outlineVertices, x, y, m_outlineColor, strikeThroughOffset, underlineThickness, m_outlineThickness);
                }

                if (isBackground and (curChar == L'\n' && prevChar != L'\n'))
                {
                    Log(Debug) << strikeThroughOffset;
                    addLine(m_backgroundVertices, x, y, getFillColor(), strikeThroughOffset, backgroundThickness);
                }
                prevChar = curChar;

                // Handle special characters
                if ((curChar == L' ') || (curChar == L'\n') || (curChar == L'\t'))
                {
                    // Update the current bounds (min coordinates)
                    minX = std::min(minX, x);
                    minY = std::min(minY, y);

                    switch (curChar)
                    {
                    case L' ':  x += whitespaceWidth;     break;
                    case L'\t': x += whitespaceWidth * 4; break;
                    case L'\n': y += lineSpacing; x = 0;  break;
                    }

                    // Update the current bounds (max coordinates)
                    maxX = std::max(maxX, x);
                    maxY = std::max(maxY, y);

                    // Next glyph, no need to create a quad for whitespace
                    continue;
                }

                // Apply the outline
                if (m_outlineThickness != 0)
                {
                    const sf::Glyph& glyph = m_font->getGlyph(curChar, m_characterSize, isBold, m_outlineThickness);

                    float left = glyph.bounds.left;
                    float top = glyph.bounds.top;
                    float right = glyph.bounds.left + glyph.bounds.width;
                    float bottom = glyph.bounds.top + glyph.bounds.height;

                    // Add the outline glyph to the vertices
                    addGlyphQuad(m_outlineVertices, sf::Vector2f(x, y), m_outlineColor, glyph, italicShear, m_outlineThickness);

                    // Update the current bounds with the outlined glyph bounds
                    minX = std::min(minX, x + left - italicShear * bottom - m_outlineThickness);
                    maxX = std::max(maxX, x + right - italicShear * top - m_outlineThickness);
                    minY = std::min(minY, y + top - m_outlineThickness);
                    maxY = std::max(maxY, y + bottom - m_outlineThickness);
                }

                // Extract the current glyph's description
                const sf::Glyph& glyph = m_font->getGlyph(curChar, m_characterSize, isBold);

                // Add the glyph to the vertices
                addGlyphQuad(m_vertices, sf::Vector2f(x, y), Following::getColor(), glyph, italicShear);

                // Update the current bounds with the non outlined glyph bounds
                if (m_outlineThickness == 0)
                {
                    float left = glyph.bounds.left;
                    float top = glyph.bounds.top;
                    float right = glyph.bounds.left + glyph.bounds.width;
                    float bottom = glyph.bounds.top + glyph.bounds.height;

                    minX = std::min(minX, x + left - italicShear * bottom);
                    maxX = std::max(maxX, x + right - italicShear * top);
                    minY = std::min(minY, y + top);
                    maxY = std::max(maxY, y + bottom);
                }

                // Advance to the next character
                x += glyph.advance + letterSpacing;
            }

            // If we're using the underlined style, add the last line
            if (isUnderlined && (x > 0))
            {
                addLine(m_vertices, x, y, Following::getColor(), underlineOffset, underlineThickness);

                if (m_outlineThickness != 0)
                    addLine(m_outlineVertices, x, y, m_outlineColor, underlineOffset, underlineThickness, m_outlineThickness);
            }

            // If we're using the strike through style, add the last line across all characters
            if (isStrikeThrough && (x > 0))
            {
                addLine(m_vertices, x, y, Following::getColor(), strikeThroughOffset, underlineThickness);

                if (m_outlineThickness != 0)
                    addLine(m_outlineVertices, x, y, m_outlineColor, strikeThroughOffset, underlineThickness, m_outlineThickness);
            }

            if (isBackground && (x > 0))
            {
                addLine(m_backgroundVertices, x, y, getFillColor(), strikeThroughOffset, backgroundThickness);
                //Currently lets ignore the outline thincknes.
            }

            // Update the bounding rectangle
            m_bounds.left = minX;
            m_bounds.top = minY;
            m_bounds.width = maxX - minX;
            m_bounds.height = maxY - minY;
        }
	};
}

#endif