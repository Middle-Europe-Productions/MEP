////////////////////////////////////////////////////////////
//
//	WindowData.cpp created with the use of SFML
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
//	Created by Piotr Skibi�ski
//	Copyright � Middle Europe Productions. All rights reserved.
//
////////////////////////////////////////////////////////////
#include<MEPWindow/WindowData.h>

namespace MEP
{
    WindowData::WindowData(const char* title, const
        sf::Vector2u& mainResolution,
        U_int32 style,
        sf::ContextSettings settings) :
        m_resolution(mainResolution),
        m_launchResolution(mainResolution),
        m_settings(settings),
        m_title(title),
        m_style(style)
    {
    }

    void WindowData::initWindow() 
    {
        create(sf::VideoMode(m_resolution.x, m_resolution.y), m_title, m_style, m_settings);
        m_view = getView();
    }

    sf::RenderWindow& WindowData::getRenderWindow()
    { 
        return *this; 
    }

    sf::ContextSettings& WindowData::getContext() 
    { 
        return m_settings;
    }

    sf::View& WindowData::getMepView()
    { 
        return m_view; 
    }

    void WindowData::changeResolution(const sf::Vector2u& newRes) 
    {
        setSize(newRes);
    }

    const sf::Vector2u& WindowData::getLaunchResolution() const 
    {
        return m_launchResolution;
    }

    const sf::Vector2u WindowData::getWindowSize() const 
    { 
        return getSize(); 
    }

    void WindowData::setResolution(const sf::Vector2u& res) {
        m_resolution = res;
        setSize(m_resolution);
        m_view.setCenter({ (float)m_resolution.x / 2, (float)m_resolution.y / 2 });
        m_view.setSize({ (float)m_resolution.x, (float)m_resolution.y });
        setView(m_view);
    }

    sf::Vector2u WindowData::getResolution() const {
        return m_resolution;
    }

    void WindowData::onResize() {
        m_resolution = getSize();
        m_view.setCenter({ (float)m_resolution.x / 2, (float)m_resolution.y / 2 });
        m_view.setSize({ (float)m_resolution.x, (float)m_resolution.y });
        setView(m_view);
    }
}