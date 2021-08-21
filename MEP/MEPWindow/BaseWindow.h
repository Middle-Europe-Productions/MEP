
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
		ToRender(MEP::Drawable* ele);
		ToRender(MEP::Drawable& ele);
		/**
		* Outputs the element.
		*/
		MEP::Drawable* get() const;
		/**
		* Outputs the activity of an object.
		* False - object destructor was called. True - objects exists.
		*/
		bool isActive() const;
		/**
		* << operator.
		*/
		friend std::ostream& operator<<(std::ostream& out, const ToRender& x);
	};
}
namespace MEP {
	struct DataPackage {
		MEP::Drawable* _obj;
		MEP::U_int32 _group;
		DataPackage(MEP::Drawable* obj, MEP::U_int32 group = 4294967295);
		DataPackage(MEP::Drawable& obj, MEP::U_int32 group = 4294967295);
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
		explicit WindowException(const unsigned int ID, const std::string& msg);
		/**
		* Constructor of a WindowException
		* @param[in] ID : Identification of a w MEP::BaseWindow
		* @param[in] msg : Message
		*/
		explicit WindowException(const unsigned int ID, const char* msg);
		/**
		* Constructor of a WindowException
		* @param[in] ID : Identification of a w MEP::BaseWindow
		* @param[in] x : A MEP::ResourceException that caused the MEP::WindowException
		*/
		explicit WindowException(const unsigned int ID, const MEP::ResourceException& x);
		/**
		* Constructor of a WindowException
		* @param[in] ID : Identification of a w MEP::BaseWindow
		* @param[in] msg : Message
		*/
		explicit WindowException(const std::string& msg);
		/**
		* Constructor of a WindowException
		* @param[in] msg : Message
		*/
		explicit WindowException(const char* msg);
		/**
		* Constructor of a WindowException
		* @param[in] x : A MEP::ResourceException that caused the MEP::WindowException
		*/
		explicit WindowException(const MEP::ResourceException& x);
		/**
		* Overloading the << operator.
		*/
		friend std::ostream& operator<<(std::ostream& out, const WindowException& x);
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
			/** In this state all of the MEP::Animation with RunAtLowEntry or RunAtLowEntryAndEnd are activated. Then window enters InProgress state.*/
			LowEntrance = 0,
			/** In this state all of the MEP::Animation with RunAtEntry or RunAtEntryAndEnd are activated. Then window enters Main state.*/
			Entrance = -1,
			/** In this state all of the MEP::Objects with RunAtEnd or RunAtEntryAndEnd are activated and Window wait for them to finish. */
			Exit = -2,
			/** In this state all of the MEP::Animation with RunAtLowEntry or RunAtLowEntryAndEnd are activated and Window wait for them to finish. */
			LowExit = -3,
			/** In this state window is being rendered.*/
			InProgress = -4,
			/** In this state window is being rendered and events from it are handled.*/
			Main = -5,
			/** In this state window is not doing anything.*/
			NullAction = -6
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
		BaseWindow(const unsigned int ID);
		/**
		* Constructor of a BaseWindow
		* @param[in] id : Window identifier
		* @patam[in] view : Input view of the window.
		* @patam[in] master : Main window view.
		*/
		BaseWindow(const unsigned int ID, const sf::View& view, const sf::View& master);
		/**
		* Base render method.
		* @param[in] Window : RenderWindow object.
		* @return True if non of the window elements need a rebuild, false when atleast one element could not be rendered.
		*/
		virtual bool render(sf::RenderWindow& Window);
		/**
		* Updates the position when window is resized.
		*/
		void onResize(const sf::Vector2u& new_res);
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
		const Status& getStatus();
		/**
		* Changes the status of a window.
		* @param[in] status : MEP::Status
		*/
		void changeStatus(const Status status);
		/**
		* Adds a new MEP::Drawable to the main scope.
		* @param[in] : MEP::Drawable*
		*/
		void newObject(DataPackage object);
		/**
		* Adds a new MEP::Drawable to the main scope.
		* @param[in] : MEP::Drawable*
		*/
		void newObject(MEP::Drawable* object);
		/**
		* Adds a new MEP::Drawable to the main scope.
		* @param[in] : MEP::Drawable&
		*/
		void newObject(MEP::Drawable& object);
		/**
		* Deletes all MEP::Objects in the MEP::Window::BaseWindow
		*/
		template<typename ... Values>
		void newObjects(Values&& ... values);
		/**
		* Debug output method. 
		*/
		void debugOutput(std::ostream& out);
		/**
		* Outputs an ID of a MEP::Window::BaseWindow
		* @return : ID
		*/
		unsigned int getID() const;
		bool operator==(const unsigned int ID) const;
		bool operator==(const BaseWindow& x) const;
		virtual ~BaseWindow();
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

}

#endif
