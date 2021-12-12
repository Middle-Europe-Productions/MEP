
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
//	Created by Piotr Skibi�ski
//	Copyright � Middle Europe Productions. All rights reserved.
//
////////////////////////////////////////////////////////////
#ifndef MEP_TIMER_H
#define MEP_TIMER_H
#if defined(MEP_ALLOW_TIMER)
#include<MEPTools/TimerContainer.h>
#include<chrono>
#include<string>
#define __NAME_FINAL(name, id) name##id
#define __NAME_DEC(name, id) __NAME_FINAL(name, id)
#define TIMER(method) __TIMER(__NAME_DEC(timer, __LINE__), method)
#define __TIMER(name, method) MEP::__Timer name(method, __LINE__, __FILE__, __FUNCTION__); 
#define GENERATE MEP::__TimerContainer::generate();
#define RESET MEP::__TimerContainer::reset();

namespace MEP
{
	class __Timer
	{
		const char* __FILE;
		const char* __NAME;
		const char* __FUNCTION;
		unsigned int __LINE;
		std::chrono::time_point<std::chrono::high_resolution_clock> __START;
	public:
		explicit __Timer(const char* NAME, unsigned int LINE, const char* FILE, const char* FUNCTION) :
			__FILE(FILE),
			__NAME(NAME),
			__FUNCTION(FUNCTION),
			__LINE(LINE)
		{
			__START = std::chrono::high_resolution_clock::now();
		}
		void stop()
		{
			auto __STOP = std::chrono::high_resolution_clock::now();
			auto start = std::chrono::time_point_cast<std::chrono::microseconds>(__START).time_since_epoch().count();
			auto stop = std::chrono::time_point_cast<std::chrono::microseconds>(__STOP).time_since_epoch().count();
			auto duration = stop - start;
#if defined(MEP_ALLOW_LIVE_VIEW)
			MEP::__TimerContainer::add(DataTask(DataTask::Type::Add, __NAME, __FILE, __LINE, static_cast<double>(duration) * 0.001));
#else
			Log(Info) << "Name:" <<__NAME << ", Time:"<< static_cast<double>(duration) * 0.001 <<"ms, Function:" << __FUNCTION << ", File:" << __FILE;
#endif
		}
		~__Timer()
		{
			stop();
		}
	};
}
#else
#define TIMER() ;
#define TIMER(method) ;
#define GENERATE ;
#define RESET ;
#endif

#endif