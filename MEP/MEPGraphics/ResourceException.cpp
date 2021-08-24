////////////////////////////////////////////////////////////
//
//	ResourceException.cpp created with the use of SFML
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
#include<MEPGraphics/ResourceException.h>
namespace MEP
{
	ResourceException::ResourceException(const std::string& name, const std::string& msg, const ExceptionType& type) :
		exceptionType(type),
		ResourceName(name),
		Message(msg)
	{}

	ResourceException::ResourceException(const char* name, const char* msg, const ExceptionType& type) :
		exceptionType(type),
		ResourceName(name),
		Message(msg)
	{}

	std::ostream& operator<<(std::ostream& out, const ResourceException& x) {
		out << "ResourceException ResourceName: " << x.ResourceName << ", Message: " << x.Message << std::endl;
		return out;
	}
}