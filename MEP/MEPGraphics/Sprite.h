#ifndef MEP_SPRITE_H
#define MEP_SPRITE_H

#include<MEPGraphics/Following.h>
namespace MEP {
	/**
	* \brief Basically the SFML sprite with the support for the MEP functionalities.
	*/
	class Sprite: public Following {
		//[optional] formula for calculation of the rect of the 
		std::function<sf::IntRect()> calc_rect = [this]()->sf::IntRect { return currentSprite.getTextureRect(); };
	protected:
		/**
		* Current sprite ready to bo rendered;
		*/
		sf::Sprite currentSprite;
	public:
		Sprite(const FollowType& followType,
			sf::Vector2f pos = { 0.f, 0.f },
			sf::Vector2f scale = { 1.f, 1.f });

		Sprite(sf::Vector2f pos = { 0.f, 0.f },
			sf::Vector2f scale = { 1.f, 1.f });
		Sprite& operator<<(const Sprite& x);
		/**
		* Outputs the sf::Sprite objects in case you want to commit any advanced changes which are not supported by the MEP.
		* @return : sf::Sprite
		*/
		sf::Sprite& getSprite();
		/**
		* Updates the set of sprite variables and it's texture according to the following elements and given texture.
		*/
		void updateSprite(sf::Texture& texture);
		/**
		* Updates the set of sprite variables according to the following elements.
		*/
		virtual void updateSprite();
		/**
		* Sets the position
		* @param[in] pos : Position.
		*/
		void setPosition(const sf::Vector2f pos) override;
		/**
		* Sets the position
		* @param[in] x : MEP::Following object.
		*/
		void setPosition(const Following& x) override;
		/**
		* Sets the scale.
		* @param[in] scale : Scale.
		*/
		virtual void setScale(const sf::Vector2f scale);
		/**
		* Sets the scale.
		* @param[in] pos : MEP::Following object.
		*/
		virtual void setScale(const Following& x);
		/**
		* Changes the color of a master sprite.
		* @param[in] color : Color.
		*/
		void setColor(const sf::Color& color) override;
		/**
		* Sets the main sprite Rect
		*/
		void setRect(const sf::IntRect& rect);
		/**
		* Adds a method of calculation the scale.
		* @param[in] method : A method of calculating the position.
		*/
		void addMethodRect(std::function<sf::IntRect()> method);
		/**
		* Updates the rect of the Sprite
		*/
		void updateRect();
		/**
		* Outputs the rect.
		*/
		const sf::IntRect& getRect() const;
		/**
		* Outputs the color of a master sprite.
		* @return : Color.
		*/
		const sf::Color& getColor() const override;
	};
}

#endif