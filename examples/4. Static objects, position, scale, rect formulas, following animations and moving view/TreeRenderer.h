#ifndef TREE_RENDERER_H
#define TREE_REDNERER_H
#include <MEP.h>
////////////////////////////////////////////////////////
//A simple class showing basic usage of MEP library.
//2. Creates a simple custom window & display simple object. 
//Keep in mind that we do need to init our resource.
//It is done in the main class.
////////////////////////////////////////////////////////
class TreeRenderer : public MEP::Window::BaseWindow {
	//Objects in genereal does not have default constructor.
	//It means that this type of statements needs to be specified in the class constructor.
	MEP::TextureObject object;
	//To avoid that u can use pointers.
	MEP::Text* text;
	//3---
	//Animation of the position
	MEP::AnimationPosition* animation;
	//Animation of the color.
	MEP::AnimationColor* color_animation;
	//----
	//4---
	//Let's create the second circle to demonstrate the idea of static object.
	//A static objects will stick to the given position no matter how the view acts.
	//Keep in mind that it does not mean that it is going to change the position while windows is resized.
	MEP::TextureObject *static_object;
	//Firstly, we need to create a way of moving the view.
	//The most commont approche is grabbing the view with the left click.
	//Third circle will follow the first one with some delay.
	//We do need two things
	MEP::AnimationPosition* second_animation;
	MEP::TextureObject* follow_object;
	//----
public:
	//Reference to the base app is needed because we want to gen access to the resources and view.
	TreeRenderer(MEP::Window::Template::Application& base);
	~TreeRenderer();
	//3. To handle the events you do need to override the following method.
	//Window will handle the events of the window if the state == BaseWindow::Status::Main
	void handleEvent(sf::RenderWindow& Window, sf::Event& event) override;
};

#endif