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
	latestWindowMaster().changeStatus(MEP::Window::BaseWindow::Status::Main);
	//------
}

void TreeDrawer::createResources()
{
}
