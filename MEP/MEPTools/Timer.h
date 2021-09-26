
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
#ifndef MEP_TIMER_H
#define MEP_TIMER_H
#ifndef ENABLE_TIMER
#include<chrono>

#define TIMER() MEP::__Timer timer__LINE__("", __LINE__, __FILE__);
#define TIMER(method) MEP::__Timer timer__LINE__(method, __LINE__, __FILE__);

namespace MEP
{
	class __Timer
	{
		const std::string& __FILE;
		const std::string& __NAME;
		unsigned int __LINE;
	public:
		explicit __Timer(const std::string& NAME, unsigned int LINE, const std::string& FILE) :
			__FILE(FILE),
			__NAME(NAME),
			__LINE(LINE)
		{

		}
		void stop()
		{

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
#endif

#endif