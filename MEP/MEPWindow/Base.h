
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
#include"..\MEPGraphics\MEPGraphics.h"
namespace MEP {
	namespace Window {
		struct WindowException {
			const unsigned int WindowID;
			std::string Message;
			explicit WindowException(const unsigned int ID, const std::string& msg) : WindowID(ID), Message(msg) 
			{}
			explicit WindowException(const unsigned int ID, const char* msg) : WindowID(ID), Message(msg) 
			{}
			explicit WindowException(const unsigned int ID, const MEP::ResourceException& x) : WindowID(ID) 
			{
				Message = "caused by ResourceException ResourceName: " + x.ResourceName + ", Message: " + x.Message;
			}
			friend std::ostream& operator<<(std::ostream& out, const WindowException& x) {
				out << "WindowException, ID:" << x.WindowID << ", Message:" << x.Message << std::endl;
				return out;
			}
		};

		class BaseWindow {
		public:
			//Various statuses of a window
			enum class Status {
				Entrance = -1,
				Exit = -2,
				InProgress = -3,
				Main = -4,
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
			std::list<std::unique_ptr<MEP::Drawable>> m_objects;
			//Connections to different windows around the scope
			std::list<BaseWindow*> m_connections;
			BaseWindow* GetWindow(unsigned int ID);
		public:
			BaseWindow(const unsigned int ID) : m_ID(ID) {}
			virtual void render(sf::RenderWindow& Window);
			//all update functions
			virtual void update(sf::Time& currentTime);
			virtual void updateRunning(sf::Time& currentTime);
			virtual void updateEntrance(sf::Time& currentTime);
			virtual void updateExit(sf::Time& currentTime);
			//handling events function
			virtual void handleEvent(sf::RenderWindow& Window, sf::Event& event);
			const Status& GetStatus() { return m_status; }
			void ChangeStatus(const Status status) { m_status = status; }
			//setting new connected menu
			void SetConnection(BaseWindow* window) { m_connections.push_back(window); }
			//checking if the connection is extablished
			bool IsConnected(unsigned int ID) const;
			//adds a new object to the scope
			void newObject(MEP::Drawable* object) { m_objects.push_back(std::unique_ptr<MEP::Drawable>(object)); };
			void newObject(MEP::Drawable& object) { m_objects.push_back(std::unique_ptr<MEP::Drawable>(&object)); }
			template<typename ... Values>
			void newObjects(Values&& ... values);
			//Returns window ID
			unsigned int GetID() const { return m_ID; }
			//operators
			bool operator==(const unsigned int ID) const { return m_ID == ID; }
			bool operator==(const BaseWindow& x) const { return GetID() == x.GetID(); }
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
			if (m_status == Status::InProgress or m_status == Status::Main) {
				updateRunning(currentTime);
			}
			else if (m_status == Status::Entrance) {
				updateEntrance(currentTime);
			}
			else if (m_status == Status::Exit) {
				updateExit(currentTime);
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

		inline BaseWindow* BaseWindow::GetWindow(unsigned int ID)
		{
			for (auto& x : m_connections)
				if (*x == ID)
					return x;
			return nullptr;
		}

		inline void BaseWindow::render(sf::RenderWindow& Window)
		{
			for (auto& x : m_objects)
				x->draw(Window);
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

		inline bool BaseWindow::IsConnected(unsigned int ID) const
		{
			for (auto& x : m_connections)
				if (*x == ID)
					return true;
			return false;
		}
	}
}
