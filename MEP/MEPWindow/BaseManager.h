
////////////////////////////////////////////////////////////
//
//	BaseManager.h created with the use of SFML
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

#pragma once
#include <list>
#include "WindowCrossPlatform.h"
#include "WindowsStat.h"
#include "Base.h"
namespace MEP {
    namespace Window {
        class BaseManager : public Resources, public WindowStats {
        protected:
            std::list<BaseWindow*> m_windows;
            BaseWindow* GetWindow(unsigned int ID) {
                for (auto& x : m_windows)
                    if (*x == ID)
                        return x;
                return nullptr;
            }
            //Outputs the window at the front
            BaseWindow* WindowFront() {
                return m_windows.front();
            }
            //Outputs the window at the back
            BaseWindow* WindowBack() {
                return m_windows.back();
            }
            //Adds a new window to back of the windows list.
            void AddWindowBack(BaseWindow* window) {
                m_windows.push_back(window);
            }
            //Adds a new window to front of the windows list.
            void AddWindowFront(BaseWindow* window) {
                m_windows.push_front(window);
            }
            sf::RenderWindow Window;
            sf::View m_view;
            sf::Vector2u m_resolution;
            sf::ContextSettings m_settings;
            //initialization of a window
            void init(const char* title, 
                const sf::Vector2u& Resolution = { 1280, 720 },
                const sf::Vector2u& mainResolution = { 1280, 720 }) 
            {
                Window.create(sf::VideoMode(Resolution.x, Resolution.y), title, sf::Style::None, m_settings);
                Window.setFramerateLimit(120); 
                SetResolution(mainResolution);
            };
            //////////////////////////////////////////////////////////
            //Updates a main loop of a code.
            virtual void update() {
                for (auto& x : m_windows) {
                    if (x->GetStatus() != BaseWindow::Status::NullAction) {
                        try {
                            x->update(GetGlobalTime());
                        }
                        catch (const WindowException& x) {
                            std::cout << x;
                        }
                    }

                }
            }
            //Handles events inside of a events.
            virtual void handleEvents() {
                sf::Event event;
                while (Window.pollEvent(event))
                {
                    for (auto& x : m_windows) {
                        if (x->GetStatus() == BaseWindow::Status::Main)
                            x->handleEvent(Window, event);
                    }
                }
            }
            //Renders the window.
            virtual void render() {
                Window.clear(sf::Color::Transparent);
                for (auto& x : m_windows) {
                    if (x->GetStatus() != BaseWindow::Status::NullAction)
                        x->render(Window);
                }
                Window.display();
            }
            //Changes the resolution of a window
            void ChangeResolution(const sf::Vector2u& newRes) {
                Window.setSize(newRes);
            }
        public:
            BaseManager(const char* title, 
                const char* resPath, 
                const sf::Vector2u& Resolution = {1280, 720}, 
                const sf::Vector2u& mainResolution = {1280, 720})
                : MEP::Resources(resPath) 
            {
                init(title, Resolution, mainResolution);
            }
            //function sets the transparency mode of a sf::Color::Transparent
            void setWindowTransparent() {
                PLATFORM::transparent(Window.getSystemHandle());
            }
            //function changes the alpha channel of a window
            void setWindowTransparency(unsigned char alpha) {
                PLATFORM::transparency(Window.getSystemHandle(), alpha);
            }
            //Returns size of a window
            const sf::Vector2u GetWindowSize() const { return Window.getSize(); }
            //Returns sf::RenderWindow of an object
            sf::RenderWindow& GetWindow() { return Window;}
            sf::ContextSettings& GetContext() { return m_settings; }
            //Changes the target resolution of a window
            void SetResolution(const sf::Vector2u& res) {
                m_resolution = res;
            }
            //Updates the resolution of an object as well as a camera view
            void UpdateResolution() {
                Window.setSize(m_resolution);
                m_view.setCenter({ (float)m_resolution.x / 2, (float)m_resolution.y / 2 });
                m_view.setSize({ (float)m_resolution.x, (float)m_resolution.y });
                Window.setView(m_view);
            }
            //Resturns current resolution of an object
            sf::Vector2u GetResolution() const { 
                return m_resolution; 
            }
            //Initialization of the textures and windows
            void init() {
                try {
                    loadResorces();
                }
                catch (const MEP::ResourceException& x) {
                    throw MEP::Window::WindowException(-1, x);
                }
                try{
                    createWindows();
                }
                catch (const MEP::Window::WindowException& x) {
                    throw x;
                }
                isLoaded = true;
            }
            //Method closing the main window.
            void close() {
                Window.close();
            }
            //Main program loop
            virtual bool Run() {
                sf::Clock clock;
                sf::Time timeSinceLastUpdate = sf::Time::Zero;

                while (Window.isOpen())
                {
                    sf::Time dt = clock.restart();
                    GetGlobalTime() += dt;
                    handleEvents();
                    update();
                    render();
                    updateStatistics(dt);
                }
                return false;
            }
            //////////////////////////////////////////////////////////
            //Virtual Method
            //function creating windows with a BaseWindow base
            virtual void createWindows() {};
            //Virtual Method
            //function creating windows after loading with a BaseWindow base window has been lunched 
            virtual void runtimeCreateWindows() {};
            //Virtual Method
            //function loading resources
            virtual void loadResorces() {  };
            //Virtual Method
            //function loading resources while loading window is active
            virtual void runtimeloadResources() {};
        };
    }
}
