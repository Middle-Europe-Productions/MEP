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
	//3----
	//In general AnimationPosition and AnimationColor work in the same way.
	//Firstly, you do need to provide start and end value (in case of AnimationColor u pick the sf::Color).
	//Keep in mind that this is not an actual position but it is a change of the position.
	//0 at start == object stays in place chosen in the constructor.
	//Third variable is a lenght of the animation.
	//Here is an example:
	animation = new MEP::AnimationPosition(0, 100, sf::milliseconds(1000));
	//Secondly, here is an example of full functionallities of the aninations.
	//Fourth variable is a frame rate of an animation.
	//Finally, 5th, 6th and 7th are connected with eachother.
	//5th and 6th variable is a range of a function given in 7th variable (f(x) = x by default).
	//The minimal value of a function is our starting position and the max value of a funciton is a end position. (keep in mind that not always min == begin and max == end) 
	//You can use whatever function you would like std::sin(...), std::cos(...), polynomials will work just fine.
	color_animation = new MEP::AnimationColor(sf::Color::Green, sf::Color::Blue, sf::milliseconds(1000), 120, 0, 100, [](double in) { return std::pow(in, 3); });
	//Every animation can be use multiple times on multiple objects. 
	//The only limitation is that u can have only one animation for the FollowType of an object.
	object.setFollow(*animation, MEP::Following::FollowType::X_Pos);
	object.setFollow(*animation, MEP::Following::FollowType::Y_Pos);
	//Color animation is applied in the same way.
	object.setFollow(*color_animation);
	//Every type of an activity needs to be registered.
	newObjects(animation, color_animation);
	//-----
}

void TreeRenderer::handleEvent(sf::RenderWindow& Window, sf::Event& event)
{
	//3---
	//The events are 100% SFML events so visit SFML wiki for more information.
	//I do not handle the sf::Event::Closed because HUB does that.
	if (event.type == sf::Event::KeyPressed) {
		if (event.key.code == sf::Keyboard::A) {
			//Let us test the object visibility functionallity
			//All of the objects have a DrawTag which defines the key visibility feature.
			//Let A be a 'switch' between visibility of a newly created object.
			if (object.getDrawTag() & MEP::DrawTag::Unactive) {
				object.removeDrawTag(MEP::DrawTag::Unactive);
			}
			else {
				object.setDrawTag(MEP::DrawTag::Unactive);
			}
		}
		//B will activate the animation.
		else if (event.key.code == sf::Keyboard::B) {
			animation->run(MEP::Direction::Forward);
		}
		//C will activate the color animation
		else if (event.key.code == sf::Keyboard::C) {
			color_animation->run(MEP::Direction::Forward);
		}
	}
	//-----
}

TreeRenderer::~TreeRenderer()
{
	//Remember to free the memory.
	delete text;
	delete animation;
	delete color_animation;
}
