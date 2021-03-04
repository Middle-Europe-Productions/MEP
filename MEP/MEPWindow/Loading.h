
////////////////////////////////////////////////////////////
//
//	Loading.h created with the use of SFML
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
#ifndef MEP_LOADING_H
#define MEP_LEADING_H

#include<thread>
#include <MEPWindow/BaseTemplate.h>
#include <MEPWindow/Application.h>
namespace MEP {
	namespace Template {
		/**
		* Functionalities:
		* The window is capable of execution of given N number of methods on a seperate thread,
		* furthermore, it keeps the track of the exceptions and automatically changes its status to MEP::BaseWindow::Status::Exit
		* when execution of a thread is completed.
		* \brief Template of a custom Middle Europe Productions loading window.
		*/
		class Loading : public BaseTemplate, public BaseWindow {
		private:
			std::exception_ptr exception;
			bool execution;

			std::list<std::function<void()>> m_todo;
			std::thread* m_executionThread;
		private:
			void addMethod() {}
			template<typename Fun>
			void addMethod(Fun fun) {
				m_todo.push_back(fun);
			}
			template<typename First, typename ... Rest>
			void addMethod(First&& first, Rest&& ... rest) {
				addMethod(std::forward<First>(first));
				addMethod(std::forward<Rest>(rest) ...);
			}
			void MainMethod() {
				execution = true;
				for (auto& i : m_todo) {
					try {
						i();
					}
					catch (const MEP::ResourceException& x) {
						exception = std::make_exception_ptr(MEP::WindowException(getID(), x));
					}
					catch (const MEP::WindowException& x) {
						exception = std::make_exception_ptr(x);
					}
				}
				execution = false;
			}
		public:
			/**
			* Constructor of a MEP::Template::Hub
			* @param[in] ID : Window identifier
			* @param[in] base : Reference to a MEP::Template::Application
			* @param[in] todo : Methods that are going to be executed in the background.
			*/
			template<typename ... ToDo>
			Loading(unsigned int ID, MEP::Template::Application& base, ToDo&& ... todo) :
				BaseWindow(ID)
			{
				additionalInit();
				addMethod(std::forward<ToDo>(todo) ...);
				exception = nullptr;
				execution = false;
			}
			virtual void afterUpdate(sf::Time&)
			{
				if (exception != nullptr) {
					this->changeStatus(MEP::BaseWindow::Status::NullAction);
					std::rethrow_exception(exception);
				}
				if (execution == false and
					(getStatus() == MEP::BaseWindow::Status::Main or
						getStatus() == MEP::BaseWindow::Status::InProgress)) {
					if (!m_executionThread) {
						m_executionThread = new std::thread(&Loading::MainMethod, this);
					}
					else {
						this->changeStatus(MEP::BaseWindow::Status::Exit);
					}
				}
			}
			~Loading()
			{
				if (m_executionThread) {
					if (m_executionThread->joinable()) {
						m_executionThread->join();
					}
				}
			}
		};
	}
}

#endif
