
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
#ifndef MEP_APPLICATION_H
#define MEP_APPLICATION_H

#include <MEPWindow/WindowCrossPlatform.h>
#include <MEPWindow/WindowStat.h>
#include <MEPWindow/BaseManager.h>
#include <MEPWindow/WindowData.h>

namespace MEP {
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
            class Application : public WindowData, public Resources, public WindowStats, public BaseManager {
            protected:
                /**
                * Status of an initialization.
                */
                bool isInit = false;
                /**
                * Main update method, all of the program logic is executed here.
                * The update method in executed only for MEP::Window::BaseWindow with a status != BaseWindow::Status::NullAction
                */
                virtual void update();
                /**
                * Main update events method, all of the imputs to the program are analyzed here.
                * The update method in executed only for MEP::Window::BaseWindow with a status == BaseWindow::Status::Main
                * furthermore, the individual imput will be handled separately for all of the BaseWindow::Status::Main windows.
                */
                virtual void handleEvents();
                /**
                * Main render method, all of the drawing are done here.
                * Method is supporting custom views from the MEP::Window::BaseWindow and it renders all of the  MEP::Window::BaseWindow with a status == BaseWindow::Status::Main
                */
                virtual void render();
                /**
                * Overrides the on resize method.
                * A little hint is that SFML only executes this method when actual size of the window was changed so
                * you dont need to check that.
                */
                virtual void onResize();
            public:
                /**
                * Base constructor for the Application.
                * @param[in] title : Title of the window.
                * @param[in] resPath : Path to the resorces.
                * @param[in] mainResolution : Resolution of the window.
                * @param[in] style : Style of a window. Use sf::Style here.
                * @param[in] settings : Have a look on sf::ContextSettings for the information.
                */
                Application(const char* title,
                    const char* resPath,
                    const sf::Vector2u& mainResolution = { 1280, 720 },
                    U_int32 style = sf::Style::Default,
                    sf::ContextSettings settings = sf::ContextSettings());
                /**
                * Method sets the sf::Color::Transparent to a real transparent color.
                * It is a PLATFORM dependent method.
                */
                void setWindowTransparent();
                /**
                * Method changes the transparency level up to 255 of a window.
                * It is a PLATFORM dependent method.
                */
                void setWindowTransparency(unsigned char alpha);
                /**
                * Initialization of an Application
                * Two methods are executed:
                * createResources()
                * createWindows()
                * (in the following order)
                * The method can throw a MEP::Window::WindowException exception if something is not right inside of the aforementioned methods.
                */
                void initApp();
                /**
                * Main loop. Just use it to run an application.
                * The method can throw a MEP::Window::WindowException.
                */
                virtual bool run();
                /**
                * Creates the game resources. Method needs to be overwritten
                */
                virtual void createResources() = 0;
                /**
                * Creates the game resources. Method needs to be overwritten
                */
                virtual void createWindows() = 0;
                /**
                * Destructor.
                */
                virtual ~Application();
            };
        }
}

#endif
