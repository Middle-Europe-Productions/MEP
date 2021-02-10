#ifndef MEP_SPRITE_H
#define MEP_SPRITE_H

#include"Following.h"
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
			sf::Vector2f scale = { 1.f, 1.f }) :
		Following(followType, pos, pos, scale, scale)
		{}
		Sprite(sf::Vector2f pos = { 0.f, 0.f },
			sf::Vector2f scale = { 1.f, 1.f }) :
			Following(pos, pos, scale, scale)
		{}
		Sprite& operator<<(const Sprite& x) {
			if (this != &x) {
				(Following&)(*this) << x;
			}
			return *this;
		}
		/**
		* Outputs the sf::Sprite objects in case you want to commit any advanced changes which are not supported by the MEP.
		* @return : sf::Sprite
		*/
		sf::Sprite& getSprite() { return currentSprite; }
		/**
		* Updates the set of sprite variables and it's texture according to the following elements and given texture.
		*/
		void updateSprite(sf::Texture& texture)
		{
			currentSprite.setTexture(texture);
			updateSprite();
		}
		/**
		* Updates the set of sprite variables according to the following elements.
		*/
		virtual void updateSprite()
		{
			for (auto& x : followingList)
				x->updateVariables(*this, currentSprite);
		}
		/**
		* Sets the position
		* @param[in] pos : Position.
		*/
		void setPosition(const sf::Vector2f pos) override { 
			m_pos = pos; 
			m_posFixed = pos; 
			currentSprite.setPosition(m_posFixed);
			updateSprite(); 
		}
		/**
		* Sets the position
		* @param[in] x : MEP::Following object.
		*/
		void setPosition(const Following& x) override { 
			m_pos = x.getOriginPosition(); 
			m_posFixed = x.getPosition(); 
			currentSprite.setPosition(m_posFixed);
			updateSprite(); 
		}
		/**
		* Sets the scale.
		* @param[in] scale : Scale.
		*/
		virtual void setScale(const sf::Vector2f scale) { 
			m_scale = scale; 
			m_scaleFixed = scale; 
			currentSprite.setScale(m_scaleFixed);
			updateSprite(); 
		}
		/**
		* Sets the scale.
		* @param[in] pos : MEP::Following object.
		*/
		virtual void setScale(const Following& x) { 
			m_scale = x.getOriginScale(); 
			m_scaleFixed = x.getScale(); 
			currentSprite.setScale(m_scaleFixed);
			updateSprite(); 
		}
		/**
		* Changes the color of a master sprite.
		* @param[in] color : Color.
		*/
		void setColor(const sf::Color& color) override { 
			currentSprite.setColor(color); 
		}
		/**
		* Sets the main sprite Rect
		*/
		void setRect(const sf::IntRect& rect) {
			currentSprite.setTextureRect(rect);
		}
		/**
		* Adds a method of calculation the scale.
		* @param[in] method : A method of calculating the position.
		*/
		void addMethodRect(std::function<sf::IntRect()> method) {
			calc_rect = method;
		}
		/**
		* Updates the rect of the Sprite
		*/
		void updateRect() {
			currentSprite.setTextureRect(calc_rect());
		}
		/**
		* Outputs the rect.
		*/
		const sf::IntRect& getRect() const {
			return currentSprite.getTextureRect();
		}
		/**
		* Outputs the color of a master sprite.
		* @return : Color.
		*/
		const sf::Color& getColor() const override { 
			return currentSprite.getColor(); 
		}
	};
}

#endif