
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

#include <MEPWindow/BaseWindow.h>

namespace MEP {
    /**
    * It manages all of the MEP::Window added to the MEP::Teamplate::Application
    * \brief A MEP::Window manager. With a build in memory management.
    */
    class BaseManager: private MEPtools::GroupManager<BaseWindow, std::shared_ptr<BaseWindow>> {
        BaseWindow* mostRecentAccess = nullptr;
        MEP::U_int32 mostRecentGroup;
    public:
        BaseManager() = default;
        /**
        * Outputs a reference to a MEP::Window with a given ID number.
        * When you do not access the same window in a row O(logn + logm) n - number of groups, m - number of elements in group.
        * Otherwise O(1)
        * @param[in] window : unsigned int ID
        */
        BaseWindow& getWindow(MEP::U_int32 ID, MEP::U_int32 group = -1) {
            try {
                if (mostRecentAccess and mostRecentAccess->getID() == ID and mostRecentGroup == group) {
                    return *mostRecentAccess;
                }
                else {
                    mostRecentAccess = &_get(ID, group);
                    mostRecentGroup = group;
                }
                return *mostRecentAccess;
            }
            catch (const MEP::ResourceException& x) {
                if (x.exceptionType == MEP::ResourceException::ExceptionType::GroupNotFound)
                    throw MEP::WindowException("Window group not found!");
                else
                    throw MEP::WindowException("Window not found!");
            }
        }
        /**
        * Deletes the window with a given id.
        * @param[in] window : unsigned int ID
        */
        void deleteWindow(MEP::U_int32 ID, MEP::U_int32 group = -1)
        {
            _deleteElement(ID, group);
            mostRecentAccess = nullptr;
        }
        /**
        * Deletes a group of windows.
        * @param[in] window : unsigned int ID
        */
        void deleteWindowGroup(MEP::U_int32 group = -1)
        {
            _deleteGroup(group);
            mostRecentAccess = nullptr;
        }
        /**
        * Adds a new window to back of the m_windows render list. \n
        * Window is being renderd only if its Type != NullAction. \n
        * MEP::BaseWindow added with this command has lower priority. \n
        * It is added at the end of the list.
        * @param[in] window : MEP::BaseWindow
        */
        void addWindow(BaseWindow* window, MEP::U_int32 group = -1) {
            mostRecentAccess = window;
            mostRecentGroup = group;
            _insert(window->getID(), group, std::move(std::shared_ptr<BaseWindow>{window}));
        }

        BaseWindow& latestWindow() {
            if (mostRecentAccess)
                return *mostRecentAccess;
            throw MEP::WindowException("Most recent access deleted the window/most recent window does not exist!");
        }
        template<typename Method>
        void execute(Method method) {
            MEPtools::GroupManager<BaseWindow, std::shared_ptr<BaseWindow>>::_execute(method);
        }
        template<typename Method>
        void execute(Method method, MEP::U_int32 group) {
            MEPtools::GroupManager<BaseWindow, std::shared_ptr<BaseWindow>>::_execute(method, group);
        }
    };

}

#endif
