
////////////////////////////////////////////////////////////
//
//	Base.h created with the use of SFML
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
#ifndef MEP_BASE_WINDOW_H
#define MEP_BASE_WINDOW_H

#include<MEPWindow/WindowView.h>
namespace MEPtools {
	class ToRender {
		std::shared_ptr<bool> link;
		MEP::Drawable* element;
	public:	
		ToRender(MEP::Drawable* ele) {
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
		ToRender(MEP::Drawable& ele): ToRender(&ele) {}
		/**
		* Outputs the element.
		*/
		MEP::Drawable* get() const {
			return element;
		}
		/**
		* Outputs the activity of an object.
		* False - object destructor was called. True - objects exists.
		*/
		bool isActive() const {
			if (!link)
				return false;
			return *link;
		}
		friend std::ostream& operator<<(std::ostream& out, const ToRender& x) {
			if (x.isActive()) {
				out <<"|-"<< *x.get();
			}
			else {
				out << "|-Unactive";
			}
			return out;
		}
	};
}
namespace MEP {
	struct DataPackage {
		MEP::Drawable* _obj;
		MEP::U_int32 _group;
		DataPackage(MEP::Drawable* obj, MEP::U_int32 group = 4294967295) : _obj(obj), _group(group) {}
		DataPackage(MEP::Drawable& obj, MEP::U_int32 group = 4294967295) : _obj(&obj), _group(group) {}
	};
	/**
		* \brief MEP::BaseWindow exceptions handler.
		*/
	struct WindowException {
		bool master = false;
		const unsigned int WindowID = 0;
		std::string Message;
		/**
		* Constructor of a WindowException
		* @param[in] ID : Identification of a w MEP::BaseWindow
		* @param[in] msg : Message
		*/
		explicit WindowException(const unsigned int ID, const std::string& msg) : WindowID(ID), Message(msg)
		{}
		/**
		* Constructor of a WindowException
		* @param[in] ID : Identification of a w MEP::BaseWindow
		* @param[in] msg : Message
		*/
		explicit WindowException(const unsigned int ID, const char* msg) : WindowID(ID), Message(msg)
		{}
		/**
		* Constructor of a WindowException
		* @param[in] ID : Identification of a w MEP::BaseWindow
		* @param[in] x : A MEP::ResourceException that caused the MEP::WindowException
		*/
		explicit WindowException(const unsigned int ID, const MEP::ResourceException& x) : WindowID(ID)
		{
			Message = "caused by ResourceException ResourceName: " + x.ResourceName + ", Message: " + x.Message;
		}
		/**
		* Constructor of a WindowException
		* @param[in] ID : Identification of a w MEP::BaseWindow
		* @param[in] msg : Message
		*/
		explicit WindowException(const std::string& msg) : master(true), Message(msg)
		{}
		/**
		* Constructor of a WindowException
		* @param[in] msg : Message
		*/
		explicit WindowException(const char* msg) : master(true), Message(msg)
		{}
		/**
		* Constructor of a WindowException
		* @param[in] x : A MEP::ResourceException that caused the MEP::WindowException
		*/
		explicit WindowException(const MEP::ResourceException& x) : master(true)
		{
			Message = "caused by ResourceException ResourceName: " + x.ResourceName + ", Message: " + x.Message;
		}
		/**
		* Overloading the << operator.
		*/
		friend std::ostream& operator<<(std::ostream& out, const WindowException& x) {
			if (x.master)
				out << "WindowException, ID: MASTER, Message:" << x.Message << std::endl;
			else
				out << "WindowException, ID:" << x.WindowID << ", Message:" << x.Message << std::endl;
			return out;
		}
	};
	/**
	* All of the Windows added to the MEP::Template::Application are expected to be a MEP::BaseWindow objects.
	* \brief A basic class for the BaseWindow
	*/
	class BaseWindow: public MEPtools::GroupManager<MEPtools::ToRender, MEPtools::ToRender, std::list<MEPtools::ToRender>>, public WindowView {
	public:
		/**
		* @enum MEP::BaseWindow::Status
		* Definition of a status of the window.
		*/
		enum class Status {
			/** In this state all of the MEP::Animation with RunAtEntry or RunAtEntryAndEnd are activated.*/
			Entrance = -1,
			/** In this state all of the MEP::Objects with RunAtEnd or RunAtEntryAndEnd are activated and Window wait for them to finish. */
			Exit = -2,
			/** In this state window is being rendered.*/
			InProgress = -3,
			/** In this state window is being rendered and events from it are handled.*/
			Main = -4,
			/** In this state window is not doing anything.*/
			NullAction = -5
		};
	private:
		Status m_status = Status::NullAction;
		void newObj() {};
		template <typename First, typename ... Rest>
		void newObj(First&& first, Rest&& ... rest);
		//window unique ID
		unsigned int m_ID;
	public:
		/**
		* Constructor of a BaseWindow
		* @param[in] id : Window identifier
		*/
		BaseWindow(const unsigned int ID) :
			m_ID(ID)
		{}
		/**
		* Constructor of a BaseWindow
		* @param[in] id : Window identifier
		* @patam[in] view : Input view of the window.
		* @patam[in] master : Main window view.
		*/
		BaseWindow(const unsigned int ID, const sf::View& view, const sf::View& master) :
			WindowView(view, master),
			m_ID(ID)
		{}
		/**
		* Base render method.
		* @param[in] Window : RenderWindow object.
		* @return True if non of the window elements need a rebuild, false when atleast one element could not be rendered.
		*/
		virtual bool render(sf::RenderWindow& Window) {
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
		/**
		* Updates the position when window is resized.
		*/
		void onResize(const sf::Vector2u& new_res) {
			if (isCustomViewEnabled) {
				m_view.setSize({ (float)new_res.x, (float)new_res.y });
			}
			_execute([](auto& x) {
				if (x.isActive())
					x.get()->onResize();
				});
		}
		/**
		* Base update method.
		* @param[in] currontTime : Current global time.
		*/
		virtual void update(sf::Time& currentTime);
		/**
		* If you dont want to ovveride update just use this function. To update things before update call.
		* @param[in] currontTime : Current global time.
		*/
		virtual void beforeUpdate(sf::Time&) {}
		/**
		* This is a classic update it executes if window has Main or InProgress tag.
		* @param[in] currontTime : Current global time.
		*/
		virtual void updateRunning(sf::Time& currentTime);
		/**
		* This is a classic update it executes if window has Entrance tag.
		* @param[in] currontTime : Current global time.
		*/
		virtual void updateEntrance(sf::Time& currentTime);
		/**
		* This is a classic update it executes if window has Exit tag.
		* @param[in] currontTime : Current global time.
		*/
		virtual void updateExit(sf::Time& currentTime);
		/**
		* If you dont want to ovveride update just use this function. To update things after update call.
		* @param[in] currontTime : Current global time.
		*/
		virtual void afterUpdate(sf::Time&) {}
		/**
		* Base handle events method.
		* @param[in] Window : sf::RenderWindow.
		* @param[in] event : sf::Event
		*/
		virtual void handleEvent(sf::RenderWindow& Window, sf::Event& event);
		/**
		* Outputs the status of a window.
		* @return MEP::Status
		*/
		const Status& getStatus() {
			return m_status;
		}
		/**
		* Changes the status of a window.
		* @param[in] status : MEP::Status
		*/
		void changeStatus(const Status status) {
			m_status = status;
		}
		/**
		* Adds a new MEP::Drawable to the main scope.
		* @param[in] : MEP::Drawable*
		*/
		void newObject(DataPackage object) {
			_insert(0, object._group, object._obj);
		};
		/**
		* Adds a new MEP::Drawable to the main scope.
		* @param[in] : MEP::Drawable*
		*/
		void newObject(MEP::Drawable* object) {
			_insert(0, 4294967295, object);
		};
		/**
		* Adds a new MEP::Drawable to the main scope.
		* @param[in] : MEP::Drawable&
		*/
		void newObject(MEP::Drawable& object) {
			_insert(0, 4294967295, object);
		}
		/**
		* Deletes all MEP::Objects in the MEP::Window::BaseWindow
		*/
		template<typename ... Values>
		void newObjects(Values&& ... values);
		void debugOutput(std::ostream& out) {
			std::cout << "|-Display-Queue-------------------------------------------"<< std::endl;
			std::cout << "MEP::debugOutput() Window ID :" << getID() << std::endl;
			MEPtools::GroupManager<MEPtools::ToRender, MEPtools::ToRender, std::list<MEPtools::ToRender>>::_debugOutput(out, "", "\n");
			std::cout << "|---------------------------------------------------------" << std::endl;
		}
		/**
		* Outputs an ID of a MEP::Window::BaseWindow
		* @return : ID
		*/
		unsigned int getID() const {
			return m_ID;
		}
		bool operator==(const unsigned int ID) const {
			return m_ID == ID;
		}
		bool operator==(const BaseWindow& x) const {
			return getID() == x.getID();
		}
		virtual ~BaseWindow() {};
	};

	template<typename First, typename ...Rest>
	inline void BaseWindow::newObj(First&& first, Rest&& ...rest)
	{
		newObject(std::forward<First>(first));
		newObj(std::forward<Rest>(rest) ...);
	}

	template<typename ...Values>
	inline void BaseWindow::newObjects(Values&& ...values)
	{
		newObj(std::forward<Values>(values) ...);
	}

	inline void BaseWindow::update(sf::Time& currentTime)
	{
		try {
			beforeUpdate(currentTime);
			if (m_status == Status::InProgress or m_status == Status::Main) {
				updateRunning(currentTime);
			}
			else if (m_status == Status::Entrance) {
				updateEntrance(currentTime);
			}
			else if (m_status == Status::Exit) {
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

	inline void BaseWindow::updateRunning(sf::Time& currentTime)
	{
		_execute([&currentTime](auto& x) {
			if (x.isActive())
				x.get()->update(currentTime);
			});
	}

	inline void BaseWindow::updateEntrance(sf::Time& currentTime)
	{
		_execute([&currentTime](auto& x) {
			if(x.isActive())
				x.get()->entryUpdate(currentTime);
			});
		m_status = Status::Main;
	}

	inline void BaseWindow::updateExit(sf::Time& currentTime)
	{
		bool isActive = false;
		_execute([&currentTime, &isActive](auto& x) {
			if (x.isActive()) {
				x.get()->exitUpdate(currentTime);
				if (x.get()->isActive())
					isActive = true;
			}
			});
		if (!isActive) {
			m_status = Status::NullAction;
		}
	}

	inline void BaseWindow::handleEvent(sf::RenderWindow& Window, sf::Event& event)
	{
		if (event.type == sf::Event::Closed)
			Window.close();
	}
}

#endif
