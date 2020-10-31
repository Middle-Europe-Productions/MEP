
////////////////////////////////////////////////////////////
//
//	BaseLoading.h created with the use of SFML
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
#include<thread>
#include "BaseTemplate.h"
#include "BaseManager.h"
namespace MEP {
	namespace Window {
		namespace Template {
			class BaseLoading: public BaseTemplate, public BaseWindow {
			private:
				inline static std::exception_ptr exception;

				std::list<std::function<void()>> m_todo;
				std::thread* m_executionThread;
				inline static bool execution;
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
							exception = std::make_exception_ptr(MEP::Window::WindowException(GetID(), x));
						}
						catch (const MEP::Window::WindowException& x) {
							exception = std::make_exception_ptr(x);
						}
					}	
					execution = false;
				}
			public:
				template<typename ... ToDo>
				BaseLoading(unsigned int ID, MEP::Window::BaseManager& base, ToDo&& ... todo) :
					BaseWindow(ID)
				{
					addMethod(std::forward<ToDo>(todo) ...);
					exception = nullptr;
					execution = false;
				}
				virtual void afterUpdate(sf::Time& currentTime)
				{
					if (exception != nullptr) {
						this->ChangeStatus(MEP::Window::BaseWindow::Status::NullAction);
						std::rethrow_exception(exception);
					}
					if (execution == false and GetStatus() == MEP::Window::BaseWindow::Status::Main) {
						if (!m_executionThread) {
							m_executionThread = new std::thread(&BaseLoading::MainMethod, this);
						}
						else {
							this->ChangeStatus(MEP::Window::BaseWindow::Status::Exit);
						}
					}	
				}
				~BaseLoading() 
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
}