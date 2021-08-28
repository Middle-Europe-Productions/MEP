#include <MEPGraphics/Image.h>
#include<iostream>
sf::Image MEP::Image::createBox(sf::Vector2u size, sf::Color color)
{
	sf::Image image;
	image.create(size.x, size.y, color);
	return image;
}