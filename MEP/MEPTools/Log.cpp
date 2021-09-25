////////////////////////////////////////////////////////////
//
//	Log created with the use of SFML
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

#include<MEPTools/Log.h>
#include<iostream>
#include<string>
namespace
{
	VerboseSetup::VerboseSetup(const char* name, unsigned int lvl) : m_name(name), m_lvl(lvl) 
	{
		MEP::Log(Info) << "Verbose log was added, file: " << name << ", level: " << lvl;
	}
	bool VerboseSetup::operator==(const char* name)
	{
		return std::strcmp(m_name, name) == 0;
	}
	bool VerboseSetup::operator==(const VerboseSetup& in)
	{
		return m_name == in.m_name;
	}
	bool VerboseSetup::operator!=(const VerboseSetup& in)
	{
		return !(*this == in);
	}
	bool VerboseSetup::operator<(unsigned int in)
	{
		return m_lvl < in;
	}
	bool VerboseSetup::operator<(const VerboseSetup& in)
	{
		return m_lvl < in.m_lvl;
	}
}
namespace MEP
{
	namespace LOG_SETUP
	{
		std::list<VerboseSetup> Verbose::__setup = std::list<VerboseSetup>();
		void Verbose::add(const char* m_name, unsigned int lvl)
		{
			for (auto& x : __setup)
			{
				if (x == m_name)
				{
					if (x < lvl)
					{
						x.m_lvl = lvl;
						return;
					}
				}
			}
			__setup.push_back({ m_name, lvl });
		}
		int Verbose::contains(const char* m_name)
		{
			for (auto& x : __setup)
			{
				if (x == m_name)
				{
					return x.m_lvl;
				}
			}
			return MAX_VERBOSE_LVL + 1;
		}
	}
	std::string __Log::getName(const char* FILE) const
	{
		std::string x;
		std::size_t it = 0;
		char backslash = '\'';
		for (; FILE[it] != '\0'; it++);
		while (it != 0 and static_cast<int>(FILE[it]) != 92)
		{
			x = FILE[it] + x;
			it--;
		}
		return x;
	}
	__Log::__Log(const char* FILE, unsigned int LINE):
		__Log(FILE, LINE, Info)
	{
	}
#ifdef _DEBUG
	__Log::__Log(const char* FILE, unsigned int LINE, LogLevel __lvl)
	{
		_buffer << "[" << getName(FILE) << ":" << LINE << "][";
		switch (__lvl) {
		case Debug:
			_buffer << "Debug] : ";
			break;
		case Fatal:
			_buffer << "Fatal] : ";
			break;
		case Error:
			_buffer << "Error] : ";
			break;
		case Warning:
			_buffer << "Warning] : ";
			break;
		case Info:
			_buffer << "Info] : ";
			break;
		default:
			break;
		}
	}
	__Log::__Log(const char* FILE, unsigned int LINE, int __lvl)
	{
		if (__lvl > MAX_VERBOSE_LVL)
		{
			Log(Error) << "Invalid verbose lvl. Max level is: " << MAX_VERBOSE_LVL;
			throw "Invalid verbose lvl.";
		}
		std::string name = getName(FILE);
		unsigned int _real_level = LOG_SETUP::Verbose::contains(name.c_str());
		if (_real_level != MAX_VERBOSE_LVL + 1 and _real_level >= __lvl)
		{
			_buffer << "[" << name << ":" << LINE << "][VERBOSE:" << __lvl << "] : ";
		}
		else
		{
			_block = true;
		}
	}
	__Log::~__Log()
	{
		if (!_block)
		{
			_buffer << std::endl;
			std::cout << _buffer.str();
		}
	}
#else
	__Log::__Log(const char* FILE, unsigned int LINE, LogLevel __lvl)
	{}
	__Log::__Log(const char* FILE, unsigned int LINE, int __lvl)
	{}
	__Log::~__Log()
	{}
#endif
}