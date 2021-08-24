////////////////////////////////////////////////////////////
//
//	BaseWindow.cpp created with the use of SFML
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
#include<MEPWindow/BaseWindow.h>

namespace MEPtools 
{
	ToRender::ToRender(MEP::Drawable* ele) {
		if (ele->_isLinked()) {
			link = ele->_linkAddr();
			*link = true;
		}
		else {
			link = std::make_shared<bool>(false);
			if (ele) {
				*link = true;
				ele->_link(link);
			}
		}
		element = ele;
	}

	ToRender::ToRender(MEP::Drawable& ele) : ToRender(&ele) 
	{}

	MEP::Drawable* ToRender::get() const {
		return element;
	}

	bool ToRender::isActive() const {
		if (!link)
			return false;
		return *link;
	}

	std::ostream& operator<<(std::ostream& out, const ToRender& x) {
		if (x.isActive()) {
			out << "|-" << *x.get();
		}
		else {
			out << "|-Unactive";
		}
		return out;
	}
}
namespace MEP
{
	//DataPackage <------------------
	DataPackage::DataPackage(MEP::Drawable* obj, MEP::U_int32 group) : _obj(obj), _group(group) {}
	DataPackage::DataPackage(MEP::Drawable& obj, MEP::U_int32 group) : _obj(&obj), _group(group) {}

	//WindowExcpetion <--------------
	WindowException::WindowException(const unsigned int ID, const std::string& msg) : WindowID(ID), Message(msg)
	{}

	WindowException::WindowException(const unsigned int ID, const char* msg) : WindowID(ID), Message(msg)
	{}

	WindowException::WindowException(const unsigned int ID, const MEP::ResourceException& x) : WindowID(ID)
	{
		Message = "caused by ResourceException ResourceName: " + x.ResourceName + ", Message: " + x.Message;
	}

	WindowException::WindowException(const std::string& msg) : master(true), Message(msg)
	{}

	WindowException::WindowException(const char* msg) : master(true), Message(msg)
	{}

	WindowException::WindowException(const MEP::ResourceException& x) : master(true)
	{
		Message = "caused by ResourceException ResourceName: " + x.ResourceName + ", Message: " + x.Message;
	}

	std::ostream& operator<<(std::ostream& out, const WindowException& x) {
		if (x.master)
			out << "WindowException, ID: MASTER, Message:" << x.Message << std::endl;
		else
			out << "WindowException, ID:" << x.WindowID << ", Message:" << x.Message << std::endl;
		return out;
	}
	//BaseWindow <--------------
	BaseWindow::BaseWindow(const unsigned int ID) :
		m_ID(ID)
	{}

	BaseWindow::BaseWindow(const unsigned int ID, const sf::View& view, const sf::View& master) :
		WindowView(view, master),
		m_ID(ID)
	{}

	bool BaseWindow::render(sf::RenderWindow& Window) {
		bool stop = true;
		if (customView())
			Window.setView(getView());
		_execute([&Window, this, &stop](auto& x) {
			if (x.isActive()) {
				if (x.get()->getDrawTag() & MEP::DrawTag::ViewLock and customView()) {
					Window.setView(getMasterView());
					if (!x.get()->draw(Window)) {
						stop = false;
					}
					Window.setView(getView());;
				}
				else if (!(x.get()->getDrawTag() & MEP::DrawTag::Unactive)) {
					if (!x.get()->draw(Window)) {
						stop = false;
					}
				}
			}
			});
		if (customView())
			Window.setView(getMasterView());
		return stop;
	}

	void BaseWindow::onResize(const sf::Vector2u& new_res) {
		if (isCustomViewEnabled) {
			m_view.setSize({ (float)new_res.x, (float)new_res.y });
		}
		_execute([](auto& x) {
			if (x.isActive())
				x.get()->onResize();
			});
	}

	const BaseWindow::Status& BaseWindow::getStatus() {
		return m_status;
	}

	void BaseWindow::changeStatus(const Status status) {
		m_status = status;
	}

	void BaseWindow::newObject(DataPackage object) {
		_insert(0, object._group, object._obj);
	};

	void BaseWindow::newObject(MEP::Drawable* object) {
		_insert(0, 4294967295, object);
	};

	void BaseWindow::newObject(MEP::Drawable& object) {
		_insert(0, 4294967295, object);
	}
	void BaseWindow::debugOutput(std::ostream& out) {
		std::cout << "|-Display-Queue-------------------------------------------" << std::endl;
		std::cout << "MEP::debugOutput() Window ID :" << getID() << std::endl;
		MEPtools::GroupManager<MEPtools::ToRender, MEPtools::ToRender, std::list<MEPtools::ToRender>>::_debugOutput(out, "", "\n");
		std::cout << "|---------------------------------------------------------" << std::endl;
	}

	void BaseWindow::update(sf::Time& currentTime)
	{
		try {
			beforeUpdate(currentTime);
			if (m_status == Status::InProgress or m_status == Status::Main) {
				updateRunning(currentTime);
			}
			else if (m_status == Status::Entrance or m_status == Status::LowEntrance) {
				updateEntrance(currentTime);
			}
			else if (m_status == Status::Exit or m_status == Status::LowExit) {
				updateExit(currentTime);
			}
			afterUpdate(currentTime);
		}
		catch (const MEP::WindowException& x) {
			throw x;
		}
		catch (const MEP::ResourceException& x) {
			throw x;
		}
	}

	void BaseWindow::updateRunning(sf::Time& currentTime)
	{
		_execute([&currentTime](auto& x) {
			if (x.isActive())
				x.get()->update(currentTime);
			});
	}

	void BaseWindow::updateEntrance(sf::Time& currentTime)
	{
		if (m_status == Status::Entrance) {
			_execute([&currentTime](auto& x) {
				if (x.isActive())
					x.get()->entryUpdate(currentTime);
				});
			m_status = Status::Main;
		}
		else {
			_execute([&currentTime](auto& x) {
				if (x.isActive())
					x.get()->entryUpdate(currentTime, true);
				});
			m_status = Status::InProgress;
		}
	}

	void BaseWindow::updateExit(sf::Time& currentTime)
	{
		bool isActive = false;
		if (m_status == Status::Exit) {
			_execute([&currentTime, &isActive](auto& x) {
				if (x.isActive()) {
					x.get()->exitUpdate(currentTime);
					if (x.get()->isActive())
						isActive = true;
				}
				});
		}
		else {
			_execute([&currentTime, &isActive](auto& x) {
				if (x.isActive()) {
					x.get()->exitUpdate(currentTime, true);
					if (x.get()->isActive())
						isActive = true;
				}
				});
		}
		if (!isActive) {
			m_status = Status::NullAction;
		}
	}

	void BaseWindow::handleEvent(sf::RenderWindow& Window, sf::Event& event)
	{
		if (event.type == sf::Event::Closed)
			Window.close();
	}

	unsigned int BaseWindow::getID() const {
		return m_ID;
	}

	bool BaseWindow::operator==(const unsigned int ID) const {
		return m_ID == ID;
	}

	bool BaseWindow::operator==(const BaseWindow& x) const {
		return getID() == x.getID();
	}

	BaseWindow::~BaseWindow() 
	{};
}