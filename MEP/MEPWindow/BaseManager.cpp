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