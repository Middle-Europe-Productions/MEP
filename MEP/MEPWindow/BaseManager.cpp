////////////////////////////////////////////////////////////
//
//	BaseManger.cpp created with the use of SFML
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
#include<MEPWindow/BaseManager.h>

namespace MEP
{
    BaseWindow& BaseManager::getWindow(MEP::U_int32 ID, MEP::U_int32 group) {
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

    std::map<MEP::U_int32, std::shared_ptr<BaseWindow>>& BaseManager::getWindowGroup(MEP::U_int32 group) {
        try {
            return _getGroup(group);
        }
        catch (const MEP::ResourceException& x) {
            if (x.exceptionType == MEP::ResourceException::ExceptionType::GroupNotFound)
                throw MEP::WindowException("Window group not found!");
            else
                throw MEP::WindowException("Window not found!");
        }
    }

    void BaseManager::deleteWindow(MEP::U_int32 ID, MEP::U_int32 group)
    {
        _deleteElement(ID, group);
        mostRecentAccess = nullptr;
    }

    void BaseManager::deleteWindowGroup(MEP::U_int32 group)
    {
        _deleteGroup(group);
        mostRecentAccess = nullptr;
    }

    void BaseManager::addWindow(BaseWindow* window, MEP::U_int32 group) {
        mostRecentAccess = window;
        mostRecentGroup = group;
        _insert(window->getID(), group, std::move(std::shared_ptr<BaseWindow>{window}));
    }

    BaseWindow& BaseManager::latestWindow() {
        if (mostRecentAccess)
            return *mostRecentAccess;
        throw MEP::WindowException("Most recent access deleted the window/most recent window does not exist!");
    }
}