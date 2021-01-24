#pragma once
#include<MEP.h>
////////////////////////////////////////////////////////
//A simple class showing basic usage of MEP library.
//Each file shows different step of the one independent project. 
//Changes are marked with the number from the folowing table.
//Table of content:
//1. Creates an empty window with a HUB <- curront lesson.
////////////////////////////////////////////////////////
class TreeDrawer : public MEP::Window::Template::Application {
public:
	TreeDrawer();
	~TreeDrawer();
	//This method creates Windows 1.
	void createWindows() override;
};
