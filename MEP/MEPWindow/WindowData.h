////////////////////////////////////////////////////////////
//
//	WindowData.h created with the use of SFML
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
#ifndef MEP_WINDOW_DATA_H
#define MEP_WINDOW_DATA_H

#include<SFML/Graphics.hpp>
namespace MEP {
    /**
        * Holds information about window.
        * Avalible operations: \n
        * Window - main window. \n
        * m_view - main view port. \n
        * m_resolution - master resolution \n
        * m_settings - main context of a window. \n
        * \brief Core information related to the SFML Window functionalities. As well as context settings.
        */
    class WindowData : public sf::RenderWindow {
    protected:
        /**
        * Master view (can be changed in a MEP::Window::BaseWindow
        */
        sf::View m_view;
        /**
        * Resolution of a window.
        */
        sf::Vector2u m_resolution;
        /**
        * Lunching resloution of the code.
        */
        const sf::Vector2u m_launchResolution;
        /**
        * Setting of a context. Antialiasing etc.
        */
        sf::ContextSettings m_settings;
        /**
        * Color of a background of the window.
        */
        sf::Color m_backgroundColor = sf::Color::Black;
        /**
        * Title of the window.
        */
        std::string m_title;
        /**
        * Style of the window.
        */
        U_int32 m_style;
    public:
        WindowData(const char* title, const
            sf::Vector2u& mainResolution = { 1280, 720 },
            U_int32 style = sf::Style::Default,
            sf::ContextSettings settings = sf::ContextSettings()) :
            m_resolution(mainResolution),
            m_launchResolution(mainResolution),
            m_settings(settings),
            m_title(title),
            m_style(style)
        {
        }
        /**
        * Creates the window.
        */
        void initWindow() {
            create(sf::VideoMode(m_resolution.x, m_resolution.y), m_title, m_style, m_settings);
            m_view = getView();
        }
        /**
        * Returns a reference to the sf::RenderWindow
        */
        sf::RenderWindow& getWindow() { return *this; }
        /**
        * Returns a reference to the sf::ContextSettings
        */
        sf::ContextSettings& getContext() { return m_settings; }
        /**
        * Returns a reference to the master sf::View
        */
        sf::View& getMepView() { return m_view; }
        /**
        * Changes the resolution of a window.
        * @param[in] newRes : sf::Vector2u
        */
        void changeResolution(const sf::Vector2u& newRes) {
            setSize(newRes);
        }
        /**
        * Outputs the lunch re
        */
        const sf::Vector2u& getLaunchResolution() const {
            return m_launchResolution;
        }
        /**
            * Returns the actual size of a window if you are using MEP::Template::Hub size == resolution.
            */
        const sf::Vector2u getWindowSize() const { return getSize(); }
        /**
        * Sets the resolution of a window.
        * *Warning* setResolution does not update the resolution use updateResolution() if you want to commit changes.
        */
        void setResolution(const sf::Vector2u& res) {
            m_resolution = res;
            setSize(m_resolution);
            m_view.setCenter({ (float)m_resolution.x / 2, (float)m_resolution.y / 2 });
            m_view.setSize({ (float)m_resolution.x, (float)m_resolution.y });
            setView(m_view);
        }
        /**
        * Output the current resolution of a window.
        * @return : sf::Vector2u.
        */
        sf::Vector2u getResolution() const {
            return m_resolution;
        }
        /**
        * A method from sf::Window.
        */
        virtual void onResize() {
            m_resolution = getSize();
            m_view.setCenter({ (float)m_resolution.x / 2, (float)m_resolution.y / 2 });
            m_view.setSize({ (float)m_resolution.x, (float)m_resolution.y });
            setView(m_view);
        }
    };
}

#endif
