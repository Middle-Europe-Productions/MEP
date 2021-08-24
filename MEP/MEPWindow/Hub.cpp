////////////////////////////////////////////////////////////
//
//	Hub.cpp created with the use of SFML
//	MEP - Middle Europe Productions
//  Work in progress. 
//
//	Licensed under the Apache License, Version 2.0 (the "License");
//	you may not use this file except in compliance with the License.
//	You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
//	Unless required by applicable law or agreed to in writing, software
//	distributed under the License is distributed on an "AS IS" BASIS,
//	WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//	See the License for the specific language governing permissions and
//	limitations under the License.
//
//
//	Created by Piotr Skibiñski
//	Copyright © Middle Europe Productions. All rights reserved.
//
////////////////////////////////////////////////////////////
#include<MEPWindow/Hub.h>

namespace MEP {
	namespace Template {
		Hub::Hub(unsigned int ID, MEP::Template::Application& base, const sf::Color& color) : BaseWindow(ID)
		{
			try {
				//Creating a MEP logo in the left corner of the screen
				sf::Image imLogo;
				imLogo.create(64, 26, imageArray);
				//delete imageArray;
				std::list<sf::Image> list;
				list.push_back(imLogo);
				base.initResources(MEP::Resource(MEP::HUB::MEPLogo, MEP::AssetsGroup::HUB, list, "HUB/mepblack"));
				std::cout << "[MEP_HUB] A new object has been added to the resources. Name: HUB/mepblack" << std::endl;
				textures[0] = new MEP::TextureObject(base.getObject(MEP::HUB::MEPLogo, MEP::AssetsGroup::HUB));
				sf::Uint8 imageArray2[16384];
				for (int i = 0; i < 16384; ++i) {
					imageArray2[i] = (char)0;
				}
				int _break = 64 * 4 * 19;
				for (int i = _break; i < _break + 6656; ++i) {
					imageArray2[i] = imageArray[i - _break];
				}
				base.getRenderWindow().setIcon(64, 64, imageArray2);
			}
			catch (const ResourceException& x) {
				throw WindowException(getID(), x);
			}
			try {
				//Creating a 16 x screen size box at the top.
				sf::Image imTop;
				imTop.create(16, 16, topArray);
				//delete topArray;
				std::list<sf::Image> list;
				list.push_back(imTop);
				base.initResources(MEP::Resource(MEP::HUB::Box, MEP::AssetsGroup::HUB, list, "HUB/top"));
				std::cout << "[MEP_HUB] A new object has been added to the resources. Name: HUB/top" << std::endl;
				textures[1] = new MEP::TextureObject(base.getObject(MEP::HUB::Box, MEP::AssetsGroup::HUB));
			}
			catch (const ResourceException& x) {
				throw WindowException(getID(), x);
			}
			try {
				////////////////////////////////////////////////////////////////////////////////////////////////////
				//Creating exit button
				sf::Image imExit;
				imExit.create(58, 28, exitArray);
				//delete exitArray;
				//Creating background 1
				sf::Image imB1;
				imB1.create(58, 28, iB1);
				//delete iB1;
				//Creating background 2
				sf::Image imB2;
				imB2.create(58, 28, iB2);
				//delete iB2;
				//creating a list
				std::list<sf::Image> list;
				list.push_back(imExit); list.push_back(imB1); list.push_back(imB2);

				base.initResources(MEP::Resource(MEP::HUB::Exit, MEP::AssetsGroup::HUB, list, "HUB/exit"));
				std::cout << "[MEP_HUB] A new object has been added to the resources. Name: HUB/exit" << std::endl;
				textures[2] = new MEP::TextureObject(base.getObject(MEP::HUB::Exit, MEP::AssetsGroup::HUB));
				buttons[0] = new MEP::Button(
					base.getObject(MEP::HUB::Exit, MEP::AssetsGroup::HUB),
					1,
					sf::Vector2f(base.getResolution().x - (float)(base.getObject(MEP::HUB::Exit, MEP::AssetsGroup::HUB).getSize().x), 4.f)
				);
				//We provide the formula to calculate the method's position.
				buttons[0]->addMethodPos([&base]()->sf::Vector2f {
					return sf::Vector2f(base.getResolution().x - (float)(base.getObject(MEP::HUB::Exit, MEP::AssetsGroup::HUB).getSize().x), 4.f);
					});
				//And then we can provide the method for the scale.
				//Example of the scale resize -> \n
				//buttons[0]->addMethodScale([&base]()->sf::Vector2f {
				//	return sf::Vector2f((float)base.getResolution().x/1280, (float)base.getResolution().y / 720); });
				//Finally we change the draw tag to  
				buttons[0]->setDrawTag(DrawTag::Resize_Pos);
				////////////////////////////////////////////////////////////////////////////////////////////////////
				sf::Image imMin;
				imMin.create(58, 28, minArray);
				//delete minArray;
				list.pop_front();
				list.push_front(imMin);

				base.initResources(MEP::Resource(MEP::HUB::Minimize, MEP::AssetsGroup::HUB, list, "HUB/min"));
				std::cout << "[MEP_HUB] A new object has been added to the resources. Name: HUB/min" << std::endl;

				textures[3] = new MEP::TextureObject(base.getObject(MEP::HUB::Minimize, MEP::AssetsGroup::HUB));
				buttons[1] = new MEP::Button(base.getObject(MEP::HUB::Minimize, MEP::AssetsGroup::HUB),
					1,
					sf::Vector2f(base.getResolution().x - (float)(base.getObject(MEP::HUB::Minimize, MEP::AssetsGroup::HUB).getSize().x * 2), 4.f)
				);
				//We provide the formula to calculate the method's position.
				buttons[1]->addMethodPos([&base]()->sf::Vector2f {
					return sf::Vector2f(base.getResolution().x - (float)(base.getObject(MEP::HUB::Minimize, MEP::AssetsGroup::HUB).getSize().x * 2), 4.f); });
				//Finally we change the draw tag to  
				buttons[1]->setDrawTag(DrawTag::Resize_Pos);
			}
			catch (const ResourceException& x) {
				throw WindowException(getID(), x);
			}
			changeColor(color);
			//Setting attributes of the objects
			textures[1]->addMethodRect([&base]()->sf::IntRect {
				return sf::IntRect(0, 0, (int)base.getWindowSize().x + 1, 4); });
			textures[1]->setDrawTag(DrawTag::Resize_Rect);

			textures[0]->setPosition(sf::Vector2f(0, 4));
			//Keep in mind that << operator only copy the MEP::Following attributes.
			*textures[3] << *buttons[1];
			//Draw tag is individual for every object thats why:
			textures[3]->setDrawTag(DrawTag::Resize_Pos);
			//Keep in mind that << operator only copy the MEP::Following attributes.
			*textures[2] << *buttons[0];
			//Draw tag is individual for every object thats why:
			textures[2]->setDrawTag(MEP::DrawTag::Resize_Pos);

			//Adding objects to the list of drawing objects in the window
			newObjects(textures[0], textures[1], buttons[0], textures[2], buttons[1], textures[3]);
		}
		Hub::~Hub() {
			delete buttons[0];
			delete buttons[1];
			delete textures[0];
			delete textures[1];
			delete textures[2];
			delete textures[3];
		}

		void Hub::changeColor(const sf::Color& color) {
			textures[0]->setColor(color);
			textures[1]->setColor(color);
			buttons[0]->setColor(color);
			textures[2]->setColor(color);
			buttons[1]->setColor(color);
			textures[3]->setColor(color);
		}
		void Hub::setFollow(const MEP::AnimationColor& animation, HubElements element, MEP::U_int32 x) {
			if (element & HubElements::MEPLogo) {
				textures[0]->setFollow(animation, x);
			}
			if (element & HubElements::TopLine) {
				textures[1]->setFollow(animation, x);
			}
			if (element & HubElements::ExitButton) {
				textures[2]->setFollow(animation, x);
				buttons[0]->setFollow(animation, x);
			}
			if (element & HubElements::MiniButton) {
				textures[3]->setFollow(animation, x);
				buttons[1]->setFollow(animation, x);
			}
		}

		void Hub::setFollow(const MEP::AnimationPosition& base, const MEP::Following::FollowType type, HubElements element) {
			if (element & HubElements::MEPLogo) {
				textures[0]->setFollow(base, type);
			}
			if (element & HubElements::TopLine) {
				textures[1]->setFollow(base, type);
			}
			if (element & HubElements::ExitButton) {
				textures[2]->setFollow(base, type);
				buttons[0]->setFollow(base, type);
			}
			if (element & HubElements::MiniButton) {
				textures[3]->setFollow(base, type);
				buttons[1]->setFollow(base, type);
			}
		}

		void Hub::handleEvent(sf::RenderWindow& Window, sf::Event& event)
		{
			sf::Vector2i pos = sf::Mouse::getPosition(Window);
			if (event.type == sf::Event::Closed)
				Window.close();
			else if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					if (buttons[0]->mousePress(pos)) {
					}
					else if (buttons[1]->mousePress(pos)) {
					}
					else if (sf::Mouse::getPosition().y - Window.getPosition().y < 35) {
						m_windowPossChange = Window.getPosition() - sf::Mouse::getPosition();
						m_grabbedWindow = true;
					}
				}
			}
			else if (event.type == sf::Event::MouseButtonReleased)
			{
				if (event.mouseButton.button == sf::Mouse::Left) {
					if (buttons[0]->mouseRelease(pos)) {
						Window.close();
					}
					else if (buttons[1]->mouseRelease(pos)) {
						PLATFORM::TOOLS::minimalize(Window.getSystemHandle());
						buttons[1]->forceRelease();
					}
					m_grabbedWindow = false;
				}
			}
			else if (event.type == sf::Event::MouseMoved)
			{
				if (m_grabbedWindow)
					Window.setPosition(sf::Mouse::getPosition() + m_windowPossChange);
				else {
					buttons[0]->mouseActivity(pos);
					buttons[1]->mouseActivity(pos);
				}

			}
			else if (event.type == sf::Event::GainedFocus) {
				PLATFORM::TOOLS::maximalize(Window.getSystemHandle());
			}
			additionalEvents(Window, event);
		}
	}
}