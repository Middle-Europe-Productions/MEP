#include<MEPGraphics/Sprite.h>

namespace MEP 
{
	Sprite::Sprite(const FollowType& followType,
		sf::Vector2f pos,
		sf::Vector2f scale) :
		Following(followType, pos, pos, scale, scale)
	{}

	Sprite::Sprite(sf::Vector2f pos,
		sf::Vector2f scale) :
		Following(pos, pos, scale, scale)
	{}

	Sprite& Sprite::operator<<(const Sprite& x) {
		if (this != &x) {
			(Following&)(*this) << x;
		}
		return *this;
	}

	sf::Sprite& Sprite::getSprite() 
	{ 
		return currentSprite; 
	}

	void Sprite::updateSprite(sf::Texture& texture)
	{
		currentSprite.setTexture(texture);
		updateSprite();
	}

	void Sprite::updateSprite()
	{
		followingListv2._execute([&](auto& x) {
			x.get()->updateVariables(*this, currentSprite);
			});
	}

	void Sprite::setPosition(const sf::Vector2f pos) {
		m_pos = pos;
		m_posFixed = pos;
		currentSprite.setPosition(m_posFixed);
		updateSprite();
	}

	void Sprite::setPosition(const Following& x) {
		m_pos = x.getOriginPosition();
		m_posFixed = x.getPosition();
		currentSprite.setPosition(m_posFixed);
		updateSprite();
	}

	void Sprite::setScale(const sf::Vector2f scale) {
		m_scale = scale;
		m_scaleFixed = scale;
		currentSprite.setScale(m_scaleFixed);
		updateSprite();
	}

	void Sprite::setScale(const Following& x) {
		m_scale = x.getOriginScale();
		m_scaleFixed = x.getScale();
		currentSprite.setScale(m_scaleFixed);
		updateSprite();
	}

	void Sprite::setColor(const sf::Color& color) {
		currentSprite.setColor(color);
	}

	void Sprite::setRect(const sf::IntRect& rect) {
		currentSprite.setTextureRect(rect);
	}

	void Sprite::addMethodRect(std::function<sf::IntRect()> method) {
		calc_rect = method;
	}

	void Sprite::updateRect() {
		currentSprite.setTextureRect(calc_rect());
	}

	const sf::IntRect& Sprite::getRect() const {
		return currentSprite.getTextureRect();
	}

	const sf::Color& Sprite::getColor() const {
		return currentSprite.getColor();
	}
}