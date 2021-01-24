#include "MainApp.h"
TreeDrawer::TreeDrawer() :
	//1.
	//Input arguments represent as follows:
	//[1]Application name.
	//[2]Resources path.
	//[3]Resolution.
	//[4]SFML window style.
	MEP::Window::Template::Application("Tree Drawer", "resources/", { 500, 500 }, sf::Style::Modern_Resize)
{
}

TreeDrawer::~TreeDrawer()
{
}

void TreeDrawer::createWindows()
{
	//1-----
	//To create a HUB ill use a build in template.
	addWindow(new MEP::Window::Template::Hub(1, *this, sf::Color::Blue));
	//It is important to change the status of a HUB.
	latestWindow().changeStatus(MEP::Window::BaseWindow::Status::Main);
	//------

	//2-----
	addWindow(new TreeRenderer(*this));
	latestWindow().changeStatus(MEP::Window::BaseWindow::Status::Main);
	//------
}

void TreeDrawer::createResources()
{
	//2-----
	//To load the resorces you need to type in initResources() command.
	//The method expect you to provide a number of MEP::Resource.
	//If you do not want to type MEP::Resource all the time you can simply.
	//typedef MEP::Resource 'Your name'; at the top.
	//All of the Resource constructors are avalible in the documentation.
	//Resource work in the following way:
	//EACH resource type (in version 1.3.1 MEP::Object & sf::Font) have it's individual group.
	//EACH group have a list of unique ID's objects.
	//EACH group and ID is a type of unsigned int == U_int32.
	//In version 1.3.1 groups -1 and -2 are occupied by the library.
	//It is recommended to use enum's.
	//In the constructor we specify the directory of the resources.
	//Of cource you can create subfolders as long as you specify that in the resource 'name'.
	//Here is an example of loading simple PNG and the font.
	initResources(MEP::Resource(1, "kw"), MEP::Resource(MEP::ResourceType::Font, 1, "Arialn.ttf"));
	//------
}

