#include "TreeRenderer.h"

TreeRenderer::TreeRenderer(MEP::Window::Template::Application& base) :
	//2----
	//All of the windows have unique ID. U need to specify it.
	MEP::Window::BaseWindow(10),
	//TextureObject fo need to gain access to MEP::Object.
	//We initialize it is the initResources() method.
	//As you can see in get method we did not specify the group.
	//This is because by default all resources are in UserAssets(<unsigned int>-1) group.
	object(MEP::TextureObject(base.get<MEP::Object>(1), {200, 200}))
	//-----
{
	//2----
	//Text can be constructed is a following way.
	//I wont dive into all of the constructors if you want to know more have a look on documentation.
	text = new MEP::Text("It is simple :)", base.get<sf::Font>(1), 40, {100, 100});
	//Let us use one of the additional features and change the default black color to blue.
	text->setColor(sf::Color::Blue);
	//If we do want our object to be visible on the screen it needs to be added to local objects list.
	//newObjects and newObject method does that.
	newObjects(object, text);
	//-----
}

TreeRenderer::~TreeRenderer()
{
	//Remember to free the memory.
	delete text;
}
