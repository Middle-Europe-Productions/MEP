#pragma once
#include<MEP.h>

//2----
#include"TreeRenderer.h"
//-----

////////////////////////////////////////////////////////
//A simple class showing basic usage of MEP library.
//Each file shows different step of the one independent project. 
//Changes are marked with the number from the folowing table.
//Table of content:
//1. Creates an empty window with a HUB
//2. Loading the resources into memory
//3. Handling the events and simple animations <- current lesson.
////////////////////////////////////////////////////////
class TreeDrawer : public MEP::Window::Template::Application {
public:
	TreeDrawer();
	~TreeDrawer();
	//This method creates Windows 1.
	void createWindows() override;
	//This method initialize the resources. 2.
	void createResources() override;
};
