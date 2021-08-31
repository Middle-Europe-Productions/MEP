
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
#ifndef MEP_LOG_H
#define MEP_LOG_H
#include <iostream>
#include <sstream>
enum LogLevel
{
	/** When execution of the code will be terminated. */
	Fatal = 0,
	/** When there is an error but code can still be executed. */
	Error = 1,
	/** When there is a warning. */
	Warning = 2,
	/** Information log outside the constructor and destructor of na object. */
	Info = 3,
	/** Information log inside of the constructor. */
	CInfo = 4,
	/** Information log inside of the destructor. */
	DInfo = 5
};

namespace MEP
{
	/**
	* \brief Simple build in logging class.
	*/
	class Log
	{
		std::ostringstream _buffer;
	public:
		/**
		* @param[in] __lvl : Info level of the log.
		* @param[in] className : Name of the class from which the log occured.
		*/
		Log(LogLevel __lvl = Info, const char* className = "");
		/**
		* Overload of the << operator.
		*/
		template<typename T>		
		Log& operator<<(T const& out);
		/**
		* The line ends with destruction.
		*/
		~Log();
	};

	template<typename T>
	Log& Log::operator<<(T const& out)
	{
		_buffer << out;
		return *this;
	}
}
#endif