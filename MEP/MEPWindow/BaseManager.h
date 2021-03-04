
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
#ifndef MEP_BASE_MANAGER_H
#define MEP_BASE_MANAGER_H

#include <MEPWindow/Base.h>

namespace MEP {
    /**
    * It manages all of the MEP::Window added to the MEP::Teamplate::Application
    * \brief A MEP::Window manager. With a build in memory management.
    */
    class BaseManager {
            protected:
                std::list<std::shared_ptr<BaseWindow>> m_windows;
                std::shared_ptr<BaseWindow> mostRecentAccess;
            public:
                BaseManager() = default;
                /**
                * Outputs a window std::shared_ptr to a MEP::Window::BaseWindow
                * *Warning* The connection feature inside of a MEP::Window::BaseWindow is in fact a std::weak_ptr
                * to properly add a window into a scope of another MEP::Window::BaseWindow u do need to use this method.
                * @param[in] window : unsigned int ID
                * @return shared_ptr to a window.
                */
                std::shared_ptr<BaseWindow>& getWindowSharedPtr(unsigned int ID) {
                    for (auto& x : m_windows)
                        if (x.get()->getID() == ID) {
                            mostRecentAccess = x;
                            return x;
                        }
                    throw MEP::WindowException("Window not found!");
                }
                /**
                * Ouputs last accessed window.
                * @return : shared_ptr to window.
                */
                BaseWindow& getLastAccess() {
                    if (mostRecentAccess.get() == nullptr) {
                        throw MEP::WindowException("You did not access any base window yet!");
                    }
                    return *mostRecentAccess.get();
                }
                /**
                * Outputs a reference to a MEP::Window with a given ID number.
                * @param[in] window : unsigned int ID
                */
                BaseWindow& getBaseWindow(unsigned int ID) {
                    for (auto& x : m_windows)
                        if (x.get()->getID() == ID)
                            if (x.get()->getID() == ID) {
                                mostRecentAccess = x;
                                return *x;
                            }
                    throw MEP::WindowException("Window not found!");
                }
                /**
                * Deletes the window with a given id.
                * @param[in] window : unsigned int ID
                */
                void deleteWindow(unsigned int ID)
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
                        throw MEP::WindowException("Could not find a window inside of a DeteleWindow method!");
                    }
                }
                /**
                * Outputs the first element of m_windows list.
                * @return Front MEP::BaseWindow
                */
                BaseWindow& latestWindow() {
                    mostRecentAccess = m_windows.front();
                    return *m_windows.front();
                }
                /**
                * Outputs the last element of m_windows list.
                * @return Back MEP::BaseWindow
                */
                BaseWindow& latestWindowMaster() {
                    mostRecentAccess = m_windows.back();
                    return *m_windows.back();
                }
                /**
                * Adds a new window to back of the m_windows render list. \n
                * Window is being renderd only if its Type != NullAction. \n
                * MEP::BaseWindow added with this command has lower priority. \n
                * It is added at the end of the list.
                * @param[in] window : MEP::BaseWindow
                */
                void addWindow(BaseWindow* window) {
                    m_windows.push_front(std::move(std::shared_ptr<BaseWindow>{window}));
                }
                /**
                * Adds a new window to back of the m_windows render list.
                * Window is being renderd only if its Type != NullAction.
                * Object added with this command has higher priority. It is added at the front of the list.
                * @param[in] window : MEP::BaseWindow
                */
                void addWindowMaster(BaseWindow* window) {
                    m_windows.push_back(std::move(std::shared_ptr<BaseWindow>{window}));
                }
        };

}

#endif
