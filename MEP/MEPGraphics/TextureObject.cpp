#include<MEPGraphics/TextureObject.h>

namespace MEP
{
	void TextureObject::updateSprite() {
		if (followingListv2._size() != 0)
			followingListv2._execute([&](auto& x) {
			x.get()->updateVariables(*this, currentSprite);
				});
		currentSprite.setPosition(m_posFixed);
		currentSprite.setScale(m_scaleFixed);
	}
	void TextureObject::init() {
		currentSprite.setTexture(*texture->front());
		currentSprite.setPosition(m_posFixed);
		currentSprite.setScale(m_scaleFixed);
		isInit = true;
	}
	TextureObject::TextureObject(const Object& x,
		sf::Vector2f pos,
		sf::Vector2f scale) :
		Object(x),
		Sprite(pos, scale)
	{
		init();
	};

	void TextureObject::onResize() {
		if (getDrawTag() & DrawTag::Resize_Scale)
			updateScale();
		if (getDrawTag() & DrawTag::Resize_Pos)
			updatePosition();
		if (getDrawTag() & DrawTag::Resize_Rect)
			updateRect();
	}

	bool TextureObject::draw(sf::RenderWindow& window) {
		if (isInit) {
			window.draw(currentSprite);
		}
		return true;
	}

	void TextureObject::update(sf::Time&) {
		updateSprite();
	}

	void TextureObject::setColor(const sf::Color& color) {
		currentSprite.setColor(color);
	}

	void TextureObject::setRotation(const float angle) {
		currentSprite.setRotation(angle);
	}

	const sf::Color& TextureObject::getColor() const {
		return currentSprite.getColor();
	}

	bool TextureObject::isActive() const {
		return isFollowerActive();
	}

	void TextureObject::debugOutput(std::ostream& out) const {
		out << "MEP::TextureObject, Following:" << std::endl;
		followingDebug(out, "  ");
		out << "   \\MEP::Object, ID: " << getID() << ", name : " << getName() << std::endl;
		out << "     \\";
		drawTagDebug(out);
	}

	std::ostream& operator<<(std::ostream& out, const TextureObject& x) {
		x.debugOutput(out);
		return out;
	}
}