
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
#include"Base.h"

namespace MEP {
    namespace Window {
        /**
        * It manages all of the MEP::Window added to the MEP::Teamplate::Application
        * \brief A MEP::Window manager. With a build in memory management.
        */
        class BaseManager {
            protected:
                std::list<std::shared_ptr<BaseWindow>> m_windows;
            public:
                BaseManager() = default;
                /**
                * Outputs a window std::shared_ptr to a MEP::Window::BaseWindow
                * *Warning* The connection feature inside of a MEP::Window::BaseWindow is in fact a std::weak_ptr
                * to properly add a window into a scope of another MEP::Window::BaseWindow u do need to use this method.
                * @param[in] window : unsigned int ID
                * @return shared_ptr to a window.
                */
                std::shared_ptr<BaseWindow>& GetWindowSharedPtr(unsigned int ID) {
                    for (auto& x : m_windows)
                        if (x.get()->getID() == ID)
                            return x;
                    throw MEP::Window::WindowException(-1, "Window not found!");
                }
                /**
                * Outputs a reference to a MEP::Window
                * @param[in] window : unsigned int ID
                */
                BaseWindow& GetBaseWindow(unsigned int ID) {
                    for (auto& x : m_windows)
                        if (x.get()->getID() == ID)
                            return *x;
                    throw MEP::Window::WindowException(-1, "Window not found!");
                }
                /**
                * Deletes the window with a given id.
                * @param[in] window : unsigned int ID
                */
                void DeleteWindow(unsigned int ID)
                {
                    std::list<std::shared_ptr<BaseWindow>>::iterator it = m_windows.begin();
                    while (it != m_windows.end()) {
                        if ((*it).get()->getID() == ID)
                            break;
                        it++;
                    }
                    if (it != m_windows.end()) {
                        m_windows.remove(*it);
                    }
                    else {
                        throw MEP::Window::WindowException(-1, "Could not find a window inside of a DeteleWindow method!");
                    }
                }
                /**
                * Outputs the first element of m_windows list.
                * @return Front MEP::Window::BaseWindow
                */
                BaseWindow& WindowFront() {
                    return *m_windows.front();
                }
                /**
                * Outputs the last element of m_windows list.
                * @return Back MEP::Window::BaseWindow
                */
                BaseWindow& WindowBack() {
                    return *m_windows.back();
                }
                /**
                * Adds a new window to back of the m_windows render list.
                * Window is being renderd only if its Type != NullAction.
                * Object added with this command has lower priority. It is added at the end of the list.
                * @param[in] window : MEP::Window::BaseWindow
                */
                void AddWindowBack(BaseWindow* window) {
                    m_windows.push_back(std::move(std::shared_ptr<BaseWindow>{window}));
                }
                /**
                * Adds a new window to back of the m_windows render list.
                * Window is being renderd only if its Type != NullAction.
                * Object added with this command has higher priority. It is added at the front of the list.
                * @param[in] window : MEP::Window::BaseWindow
                */
                void AddWindowFront(BaseWindow* window) {
                    m_windows.push_front(std::move(std::shared_ptr<BaseWindow>{window}));
                }
        };
    }
}