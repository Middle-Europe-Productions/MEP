
////////////////////////////////////////////////////////////
//
//	Application.h created with the use of SFML
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
#include "BaseManager.h"
namespace MEP {
    namespace Window {
        namespace Template {
            /**
            * MEP::Window::Teample::Application features:
            * Window management.
            * Resource management.
            * Exceptions management.
            * Main loop management.
            * Inheriting this class u are able to generate a fully functional application window.
            * \brief A basic class for the Application.
            */
            class Application : public Resources, public WindowStats, public BaseManager {
            protected:
                /**
                * Main window
                */
                sf::RenderWindow Window;
                /**
                * Master view (can be changed in a MEP::Window::BaseWindow
                */
                sf::View m_view;
                /**
                * Resolution of a window.
                */
                sf::Vector2u m_resolution;
                /**
                * Setting of a context. Antialiasing etc.
                */
                sf::ContextSettings m_settings;
                /**
                * Status of an initialization.
                */
                bool isInit = false;
                /**
                * Main initialization method. 
                */
                void init(const char* title,
                    const sf::Vector2u& mainResolution = { 1280, 720 })
                {
                    m_settings.antialiasingLevel = 16;
                    Window.create(sf::VideoMode(mainResolution.x, mainResolution.y), title, sf::Style::None, m_settings);
                    Window.setFramerateLimit(120);
                    setResolution(mainResolution);
                    m_view = Window.getView();
                };
                /**
                * Main update method, all of the program logic is executed here.
                * The update method in executed only for MEP::Window::BaseWindow with a status != BaseWindow::Status::NullAction
                */
                virtual void update() {
                    for (auto& x : m_windows) {
                        if (x->getStatus() != BaseWindow::Status::NullAction) {
                            x->update(getGlobalTime());
                        }

                    }
                }
                /**
                * Main update events method, all of the imputs to the program are analyzed here.
                * The update method in executed only for MEP::Window::BaseWindow with a status == BaseWindow::Status::Main
                * furthermore, the individual imput will be handled separately for all of the BaseWindow::Status::Main windows.
                */
                virtual void handleEvents() {
                    sf::Event event;
                    while (Window.pollEvent(event))
                    {
                        for (auto& x : m_windows) {
                            if (x->getStatus() == BaseWindow::Status::Main)
                                x->handleEvent(Window, event);
                        }
                    }
                }
                /**
                * Main render method, all of the drawing are done here.
                * Method is supporting custom views from the MEP::Window::BaseWindow and it renders all of the  MEP::Window::BaseWindow with a status == BaseWindow::Status::Main
                */
                virtual void render() {
                    Window.clear(sf::Color::Transparent);
                    bool ready = true;
                    for (auto& x : m_windows) {
                        if (x->getStatus() != BaseWindow::Status::NullAction) {
                            if (x->customView()) {
                                if (!x->render(Window))
                                    ready = false;
                            }
                            else {
                                if (!x->render(Window))
                                    ready = false;
                            }
                           
                        }
                            
                    }
                    if(ready)
                        Window.display();
                }
                /**
                * Changes the resolution of a window.
                * @param[in] newRes : sf::Vector2u
                */
                void changeResolution(const sf::Vector2u& newRes) {
                    Window.setSize(newRes);
                }
            public:
                /**
                * Returns a reference to the sf::RenderWindow
                */
                sf::RenderWindow& getWindow() { return Window; }
                /**
                * Returns a reference to the sf::ContextSettings
                */
                sf::ContextSettings& getContext() { return m_settings; }
                /**
                * Returns a reference to the master sf::View
                */
                sf::View& getView() { return m_view; }
                /**
                * Base constructor for the Application.
                * @param[in] title : Title of the window.
                * @param[in] resPath : Path to the resorces.
                * @param[in] mainResolution : Resolution of the window.
                */
                Application(const char* title,
                    const char* resPath,
                    const sf::Vector2u& mainResolution = { 1280, 720 })
                    : MEP::Resources(resPath),
                    BaseManager()
                {
                    init(title, mainResolution);
                }
                virtual ~Application() {}
                /**
                * Method sets the sf::Color::Transparent to a real transparent color.
                * It is a PLATFORM dependent method.
                */
                void setWindowTransparent() {
                    PLATFORM::transparent(Window.getSystemHandle());
                }
                /**
                * Method changes the transparency level up to 255 of a window.
                * It is a PLATFORM dependent method.
                */
                void setWindowTransparency(unsigned char alpha) {
                    PLATFORM::transparency(Window.getSystemHandle(), alpha);
                }
                /**
                * Returns the actual size of a window if you are using MEP::Template::Hub size == resolution.
                */
                const sf::Vector2u getWindowSize() const { return Window.getSize(); }
                /**
                * Sets the resolution of a window.
                * *Warning* setResolution does not update the resolution use updateResolution() if you want to commit changes.
                */
                void setResolution(const sf::Vector2u& res) {
                    m_resolution = res;
                }
                /**
                * Output the current resolution of a window.
                * @return : sf::Vector2u.
                */
                sf::Vector2u getResolution() const {
                    return m_resolution;
                }
                /**
                * Updates the resolution and the master view.
                */
                void updateResolution() {
                    Window.setSize(m_resolution);
                    m_view.setCenter({ (float)m_resolution.x / 2, (float)m_resolution.y / 2 });
                    m_view.setSize({ (float)m_resolution.x, (float)m_resolution.y });
                    Window.setView(m_view);
                }
                /**
                * Initialization of an Application
                * Two methods are executed:
                * createResources()
                * createWindows()
                * (in the following order)
                * The method can throw a MEP::Window::WindowException exception if something is not right inside of the aforementioned methods.
                */
                void initApp() {
                    try {
                        createResorces();
                    }
                    catch (const MEP::ResourceException& x) {
                        throw MEP::Window::WindowException(-1, x);
                    }
                    try {
                        createWindows();
                    }
                    catch (const MEP::Window::WindowException& x) {
                        throw x;
                    }
                    isLoaded = true;
                    isInit = true;
                }
                /**
                * Simply closes the window.
                */
                void close() {
                    Window.close();
                }
                /**
                * Main loop. Just use it to run an application.
                * The method can throw a MEP::Window::WindowException.
                */
                virtual bool run() {
                    if (isInit == false) {
                        throw MEP::Window::WindowException("Appliaction is not initialized!");
                    }
                    sf::Clock clock;
                    sf::Time timeSinceLastUpdate = sf::Time::Zero;

                    while (Window.isOpen())
                    {
                        sf::Time dt = clock.restart();
                        getGlobalTime() += dt;
                        handleEvents();
                        try {
                            update();
                        }
                        catch (const MEP::Window::WindowException& x) {
                            throw x;
                        }
                        render();
                        updateStatistics(dt);
                    }
                    return false;
                }
                /**
                * Creates the game resources. Method needs to be overwritten
                */
                virtual void createResorces() {};
                /**
                * Creates the game resources. Method needs to be overwritten
                */
                virtual void createWindows() {};
            };
        }
    }
}
