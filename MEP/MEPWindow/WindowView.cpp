////////////////////////////////////////////////////////////
//
//	WindowView.cpp created with the use of SFML
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
#include<MEPWindow/WindowView.h>

namespace MEP
{
	WindowView::WindowView(const sf::View& view, const sf::View& master) :
		m_view(view),
		m_appView(&master),
		isCustomViewEnabled(true) 
	{}

	void WindowView::grabWindow() 
	{
		m_grabbedWindow = true;
	}

	void WindowView::releaseWindow() 
	{
		m_grabbedWindow = false;
	}

	void WindowView::moveViewChange(const sf::Vector2i& change) 
	{
		m_windowPossChange = change;
	}

	bool WindowView::isGrabbed() const 
	{
		return m_grabbedWindow;
	}

	bool WindowView::customView() const 
	{
		return isCustomViewEnabled and m_appView;
	}

	const sf::View& WindowView::getView() const 
	{
		return m_view;
	}

	void WindowView::setView(const sf::View& view) 
	{
		m_view = view;
	}

	void WindowView::moveView(sf::RenderWindow& Window) 
	{
		m_view.move(-(sf::Mouse::getPosition(Window).x - m_windowPossChange.x),
			-(sf::Mouse::getPosition(Window).y - m_windowPossChange.y));
		m_windowPossChange = sf::Mouse::getPosition(Window);
	}

	const sf::View& WindowView::getMasterView() const 
	{
		return *m_appView;
	}
}