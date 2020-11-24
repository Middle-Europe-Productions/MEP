# Patch notes

### 28.10.2020
## MEP Lib version alpha 1.0
	-Initial implementation.

### 12.11.2020
## MEP Lib version alpha 1.1:
	-Added documentation. \n
	-Added memory management. \n
	-Added view functionality for the BaseWindow. \n
	-Reorganized templates.

### 24.11.2020
## MEP Lib version alpha 1.2:
	-Improved methods naming. \n
	-Added MEP::Sprite type. Provides access to the sf::Sprite as well as MEP::Animation functionalities. \n
	-Implementation of a MEP::TextObject with the full support of the MEP lib elements. \n
	-Implementation of a MEP::AnimationColor it works with the use of MEP::Following. Generally it is another type of a FollowType. Enjoy :) \n
	-DrawTag has been added to the MEP::Drawable object. Currently only ViewLock is avalible. If window is using custom view an object with the tag will be rendered using master app view. \n
	-Added << operator for all MEP::Sprite(MEP::TextureObject, MEP::Button, MEP::AnimationObject) and MEP::Text. The operator copies position, scale and color (Following attributes) to a left object. \n
	-When ID of a MEP::Window::WindowException is not specified exception will ba a master exception.
	-better naming & getLastAccess(); in base manager.