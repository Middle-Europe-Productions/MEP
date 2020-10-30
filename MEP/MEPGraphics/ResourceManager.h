
////////////////////////////////////////////////////////////
//
//	ResourceManager.h created with the use of SFML
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
#include<list>
#include<string>
#include<thread>
#include"AnimationObject.h"
#include"TextureObject.h"
namespace MEP {
	//Structor of an exceptions
	struct ResourceException {
		enum class ExceptionType {
			WrongResourceConstructor,
			ObjectNotFound,
			CouldntLoad
		};
		const ExceptionType exceptionType;
		const std::string ResourceName;
		const std::string Message;

		explicit ResourceException(const std::string& name, const std::string& msg, const ExceptionType& type) :
			ResourceName(name),
			Message(msg),
			exceptionType(type)
		{}
		explicit ResourceException(const char* name, const char* msg, const ExceptionType& type) :
			ResourceName(name),
			Message(msg),
			exceptionType(type)
		{}
		friend std::ostream& operator<<(std::ostream& out, const ResourceException& x) {
			out << "ResourceException ResourceName: " << x.ResourceName << ", Message: " << x.Message << std::endl;
			return out;
		}
	};
	//Main resources cointainer.
	class Resources {
	public:
		//type of the resource
		enum class ResourceType {
			ImageArray = 2,
			Single = 1,
			Multi = 0
		};
		//resource 
		struct Resource {
			const std::string m_name;
			Resources::ResourceType m_type;
			int m_nofFrames = 0;
			bool m_transparency = false;
			std::list<sf::Image>* m_array = nullptr;
			explicit Resource(const std::string& name, Resources::ResourceType type, bool transparency = false, unsigned int nofFrames = 1) :
				m_name(name), 
				m_type(type), 
				m_transparency(transparency) {
				if (m_type == Resources::ResourceType::Multi)
					m_nofFrames = nofFrames;
				if(type == Resources::ResourceType::ImageArray)
					throw ResourceException(name, "Wrong type of a resource!", ResourceException::ExceptionType::WrongResourceConstructor);
			}
			explicit Resource(std::list<sf::Image>& images, const std::string& name, Resources::ResourceType type, bool transparency = false, unsigned int nofFrames = 1) :
				m_name(name), 
				m_type(type), 
				m_transparency(transparency),
				m_array(&images) {
				if (m_type == Resources::ResourceType::Multi) {
					m_nofFrames = nofFrames;
				}
				if (nofFrames != images.size())
					throw ResourceException(name, "Number of images doesnt match the number of frames!", ResourceException::ExceptionType::WrongResourceConstructor);
				if (type != Resources::ResourceType::ImageArray)
					throw ResourceException(name, "Wrong type of a resource!", ResourceException::ExceptionType::WrongResourceConstructor);
			}
		};
	private:
		const std::string m_path;
		bool isInit = false;
		//List of the objects
		std::list<std::unique_ptr<Object>> objects;
		//Method loading individual resource
		void load(const Resource& data);
		void loadResources() { isInit = true; };
		//Forwarding method
		template <typename First, typename ... Rest>
		void loadResources(First&& first, Rest&& ... rest);
	protected:
		bool isLoaded = false;
	public:
		//Constructor with a resources path.
		Resources(const std::string& path) : m_path(path) {};
		//Method initializeing resources
		template<typename ... Values>
		void initResources(Values&& ... values);
		//Checks the status of the resources. 
		//Status parameter can be accessed from the inherited class. 
		bool IsLoaded() const { return isLoaded; }
		//Returns the reference to the object according to its name
		Object& getObject(const std::string name);
		virtual ~Resources() {};
	};

	template<typename First, typename ...Rest>
	inline void Resources::loadResources(First&& first, Rest&& ...rest)
	{
		load(std::forward<First>(first));
		loadResources(std::forward<Rest>(rest) ...);
	}

	template<typename ... Values>
	inline void Resources::initResources(Values&& ...values)
	{
		loadResources(std::forward<Values>(values) ...);
	}

	inline void Resources::load(const Resource& data)
	{
		std::cout << data.m_name << " " << data.m_nofFrames << " " << std::endl;
		if (data.m_type == ResourceType::Multi) {
			try {
				objects.push_back(std::make_unique<Object>(m_path, data.m_name, data.m_nofFrames, data.m_transparency));
			}
			catch (const char* x) {
				throw ResourceException(data.m_name, x, ResourceException::ExceptionType::CouldntLoad);
			}
		}
		else if (data.m_type == ResourceType::Single) {
			try {
				objects.push_back(std::make_unique<Object>(m_path, data.m_name, data.m_transparency));
			}
			catch (const char* x) {
				throw ResourceException(data.m_name, x, ResourceException::ExceptionType::CouldntLoad);
			}
		}
		else if (data.m_type == ResourceType::ImageArray) {
			try {
				objects.push_back(std::make_unique<Object>(*data.m_array, data.m_name, data.m_nofFrames, data.m_transparency));
			}
			catch (const char* x) {
				throw ResourceException(data.m_name, x, ResourceException::ExceptionType::CouldntLoad);
			}
		}
	}

	inline Object& Resources::getObject(const std::string name)
	{
		for (auto& x : objects) {
			if ((*x).GetName() == name) {
				return (*x).GetObjectRef();
			}
		}
		throw ResourceException(name, "Could not find the object!", ResourceException::ExceptionType::ObjectNotFound);
	}
}