
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

#pragma once
#include "..\MEPGraphics\MEPGraphics.h"

namespace MEP {
	namespace Window {
		/**
		* \brief MEP::Window::BaseWindow exceptions handler. 
		*/
		struct WindowException {
			const unsigned int WindowID;
			std::string Message;
			/**
			* Constructor of a BaseWindow
			* @param[in] ID : Identification of a w MEP::Window::BaseWindow
			* @param[in] msg : Message
			*/
			explicit WindowException(const unsigned int ID, const std::string& msg) : WindowID(ID), Message(msg)
			{}
			/**
			* Constructor of a BaseWindow
			* @param[in] ID : Identification of a w MEP::Window::BaseWindow
			* @param[in] msg : Message
			*/
			explicit WindowException(const unsigned int ID, const char* msg) : WindowID(ID), Message(msg)
			{}
			/**
			* Constructor of a BaseWindow
			* @param[in] ID : Identification of a w MEP::Window::BaseWindow
			* @param[in] x : A MEP::ResourceException that caused the MEP::Window::WindowException
			*/
			explicit WindowException(const unsigned int ID, const MEP::ResourceException& x) : WindowID(ID)
			{
				Message = "caused by ResourceException ResourceName: " + x.ResourceName + ", Message: " + x.Message;
			}
			/**
			* Overloading the << operator.
			*/
			friend std::ostream& operator<<(std::ostream& out, const WindowException& x) {
				out << "WindowException, ID:" << x.WindowID << ", Message:" << x.Message << std::endl;
				return out;
			}
		};
		/**
		* All of the Windows added to the MEP::Template::Application are expected to be a MEP::Window::BaseWindow objects.
		* \brief A basic class for the BaseWindow
		*/
		class BaseWindow {
		public:
			/**
			* @enum MEP::Windwo::BaseWindow::Status
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
		protected:
			//window movement
			sf::Vector2i m_windowPossChange;
			bool m_grabbedWindow = false;
			//List of all drawable objects
			std::list<MEP::Drawable*> m_objects;
			//Connections to different windows around the scope
			std::list<std::weak_ptr<BaseWindow>> m_connections;
			std::shared_ptr<BaseWindow>& getWindow(unsigned int ID);
			//custom view
			sf::View m_view;
			bool isCustomViewEnabled = false;
		public:
			/**
			* Constructor of a BaseWindow
			* @param[in] id : Window identifier
			*/
			BaseWindow(const unsigned int ID) : m_ID(ID) {}
			/**
			* Constructor of a BaseWindow
			* @param[in] id : Window identifier
			*/
			BaseWindow(const unsigned int ID, const sf::View& view) : m_ID(ID), m_view(view), isCustomViewEnabled(true) {}
			/**
			* Base render method.
			* @param[in] Window : RenderWindow object.
			* @return True if non of the window elements need a rebuild, false when atleast one element could not be rendered. 
			*/
			virtual bool render(sf::RenderWindow& Window) {
				bool stop = true;
				for (auto& x : m_objects) {
					if (!x->draw(Window)) {
						stop = false;
					}
				}
				return stop;
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
			virtual void beforeUpdate(sf::Time& currentTime) {}
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
			virtual void afterUpdate(sf::Time& currentTime) {}
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
			* Sets a new connection with a window.
			* @param[in] window : MEP::BaseWindow
			*/
			void setConnection(std::shared_ptr<BaseWindow>& window) {
				m_connections.push_back(window); 
			}
			/**
			* Sets a new connection with a window.
			* @return : true if a custom view is enabled for the window, false otherwise.
			*/
			bool customView() const { 
				return isCustomViewEnabled; 
			}
			/**
			* Outputs the view parameter.
			* @param[in] : const sf::View&
			*/
			const sf::View& getView() const { 
				return m_view; 
			}
			/**
			* Checks if the connection is established.
			* @return : true it is, false otherwise
			*/
			bool isConnected(unsigned int ID) const;
			/**
			* Adds a new MEP::Drawable to the main scope.
			* @param[in] : MEP::Drawable*
			*/
			void newObject(MEP::Drawable* object) { 
				m_objects.push_back(object); 
			};
			/**
			* Adds a new MEP::Drawable to the main scope.
			* @param[in] : MEP::Drawable&
			*/
			void newObject(MEP::Drawable& object) { 
				m_objects.push_back(&object);
			}
			/**
			* Deletes all MEP::Drawable in the MEP::Window::BaseWindow
			*/
			void deleteObjects() {
				while (!m_objects.empty()) {
					delete m_objects.front();
					m_objects.pop_front();
				}
			}
			/**
			* Deletes all MEP::Objects in the MEP::Window::BaseWindow
			*/
			template<typename ... Values>
			void newObjects(Values&& ... values);
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
			virtual ~BaseWindow() { 
				deleteObjects();
			};
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
			catch (const MEP::Window::WindowException& x) {
				throw x;
			}
			catch (const MEP::ResourceException& x) {
				throw x;
			}
		}

		inline void BaseWindow::updateRunning(sf::Time& currentTime)
		{
			for (auto& x : m_objects)
				x->update(currentTime);
		}

		inline void BaseWindow::updateEntrance(sf::Time& currentTime)
		{
			for (auto& x : m_objects)
				x->entryUpdate(currentTime);
			m_status = Status::Main;
		}

		inline void BaseWindow::updateExit(sf::Time& currentTime)
		{
			bool isActive = false;
			for (auto& x : m_objects) {
				x->exitUpdate(currentTime);
			}
			for (auto& x : m_objects) {
				if (x->IsActive())
					isActive = true;
			}
			if (!isActive) {
				m_status = Status::NullAction;
			}
		}

		inline std::shared_ptr<BaseWindow>& BaseWindow::getWindow(unsigned int ID)
		{
			for (auto& x : m_connections)
				if (auto obj = x.lock()) {
					if (obj.get()->getID() == ID) {
						return obj;
					}
				}
			throw MEP::Window::WindowException(getID(), "Window not found!");
		}

		inline void BaseWindow::handleEvent(sf::RenderWindow& Window, sf::Event& event)
		{
			if (event.type == sf::Event::Closed)
				Window.close();
			else if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					m_windowPossChange = Window.getPosition() - sf::Mouse::getPosition();
					m_grabbedWindow = true;
				}
			}
			else if (event.type == sf::Event::MouseButtonReleased)
			{
				if (event.mouseButton.button == sf::Mouse::Left)
					m_grabbedWindow = false;
			}
			else if (event.type == sf::Event::MouseMoved)
			{
				if (m_grabbedWindow)
					Window.setPosition(sf::Mouse::getPosition() + m_windowPossChange);
			}
		}

		inline bool BaseWindow::isConnected(unsigned int ID) const
		{
			for (auto& x : m_connections)
				if (auto obj = x.lock()) {
					if (obj.get()->getID() == ID) {
						return true;
					}
				}
			return false;
		}
	}
}
