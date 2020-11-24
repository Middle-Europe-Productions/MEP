
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
#include"NonCopyable.h"
namespace MEP {
	/**
	* \brief Resource exception structure.
	*/
	struct ResourceException {
		/**
		* @enum MEP::ExceptionType
		* Provides quick definition of an exceptions.
		*/
		enum class ExceptionType {
			WrongResourceConstructor,
			ObjectNotFound,
			CouldntLoad
		};
		const ExceptionType exceptionType;
		const std::string ResourceName;
		const std::string Message;
		/**
		* explicit contructor
		* @param[in] name : Name of the MEP::Object.
		* @param[in] msg : Description of an error.
		* @param[in] type : MEP::ResourceException::ExceptionType
		*/
		explicit ResourceException(const std::string& name, const std::string& msg, const ExceptionType& type) :
			ResourceName(name),
			Message(msg),
			exceptionType(type)
		{}
		/**
		* explicit contructor
		* @param[in] name : Name of the MEP::Object.
		* @param[in] msg : Description of an error.
		* @param[in] type : MEP::ResourceException::ExceptionType
		*/
		explicit ResourceException(const char* name, const char* msg, const ExceptionType& type) :
			ResourceName(name),
			Message(msg),
			exceptionType(type)
		{}
		/**
		* Overloading the << operator.
		*/
		friend std::ostream& operator<<(std::ostream& out, const ResourceException& x) {
			out << "ResourceException ResourceName: " << x.ResourceName << ", Message: " << x.Message << std::endl;
			return out;
		}
	};
	/**
	* Resources class is a utility which is meant to be working with all of the MEP::Drawable objects.
	* \brief A main MEP::Drawable cointainer.
	*/
	class Resources {
	public:
		/**
		* @enum MEP::ExceptionType
		* Provides a types of a Resource.
		*/
		enum class ResourceType {
			/** When image of arrays is provided to constuct a MEP::Object*/
			ImageArray = 2,
			/** When there is only a single texture to create a MEP::Object*/
			Single = 1,
			/** When there is a set of texture on an input to create a MEP::Object*/
			Multi = 0
		};
		/**
		* \brief A deffinitio of a individual resource.
		*/
		struct Resource: public NonCopyable {
			const std::string m_name;
			Resources::ResourceType m_type;
			unsigned int m_nofFrames = 0;
			bool m_transparency = false;
			std::list<sf::Image>* m_array = nullptr;
			/**
			* Resource contructor. It is capable of creating Single and Multi resource.
			* @param[in] name : Name of a resource.
			* @param[in] nofFrames : Number of textures. 1 by default.
			* @param[in] transparency : True if we want an object to generate alpha channel table. False by default.
			*/
			explicit Resource(const std::string& name, unsigned int nofFrames = 1, bool transparency = false) :
				m_name(name), 
				m_transparency(transparency), 
				m_type(Resources::ResourceType::Single){
				if (nofFrames == 0)
					throw ResourceException(name, "Number of frames!", ResourceException::ExceptionType::WrongResourceConstructor);
				if (nofFrames > 1)
					m_type = Resources::ResourceType::Multi;
				m_nofFrames = nofFrames;
			}
			/**
			* Resource contructor. It is capable of creating ImageArray resource.
			* @param[in] name : Name of a resource.
			* @param[in] nofFrames : Number of textures. 1 by default.
			* @param[in] transparency : True if we want an object to generate alpha channel table. False by default.
			*/
			explicit Resource(std::list<sf::Image>& images, const std::string& name, bool transparency = false) :
				m_name(name),
				m_transparency(transparency),
				m_array(&images) 
			{
				m_type = Resources::ResourceType::ImageArray;
			}
		};
	private:
		const std::string m_path;
		bool isInit = false;
		//List of the objects
		std::list<std::unique_ptr<Object>> objects;
		//Method loading individual resource
		void load(const Resource& data);
		void loadResources() { 
			isInit = true; 
		};
		//Forwarding method
		template <typename First, typename ... Rest>
		void loadResources(First&& first, Rest&& ... rest);
	protected:
		bool isLoaded = false;
	public:
		/**
		* Constructor of the resources.
		* @param[in] path : Path of the resource folder.
		*/
		Resources(const std::string& path) : m_path(path) {};
		/**
		* Initialization of the resources.
		* @param[in] values : Inputs ... number of MEP::Resources::Resource. 
		*/
		template<typename ... Values>
		void initResources(Values&& ... values);
		/**
		* Outputs the status of the resources.
		*/
		bool IsLoaded() const { return isLoaded; }
		/**
		* Outputs created MEP::Object
		* @param[in] name : Name of a MEP::Object.
		* @return Reference to MEP::Object.
		*/
		Object& getObject(const std::string& name);
		/**
		* Deletes MEP::Object with agiven name.
		* @param[in] name : Name of a MEP::Object.
		*/
		void deleteObject(const std::string& name);
		/**
		* Deletes all MEP::Object.
		* @param[in] name : Name of a MEP::Object.
		*/
		void deleteObjects() {
			objects.clear();
		}
		virtual ~Resources() {
			objects.clear();
		};
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

	inline void Resources::load(const MEP::Resources::Resource& data)
	{
		std::cout << data.m_name << " " << data.m_nofFrames << " " << (int)data.m_type << std::endl;
		if (data.m_type == ResourceType::Multi) {
			try {
				objects.push_back(std::make_unique<MEP::Object>(m_path, data.m_name, data.m_nofFrames, data.m_transparency));
			}
			catch (const char* x) {
				throw ResourceException(data.m_name, x, ResourceException::ExceptionType::CouldntLoad);
			}
		}
		else if (data.m_type == ResourceType::Single) {
			try {
				objects.push_back(std::make_unique<MEP::Object>( m_path, data.m_name, data.m_transparency ));
			}
			catch (const char* x) {
				throw ResourceException(data.m_name, x, ResourceException::ExceptionType::CouldntLoad);
			}
		}
		else if (data.m_type == ResourceType::ImageArray) {
			try {
				objects.push_back(std::make_unique<MEP::Object>(*data.m_array, data.m_name, data.m_transparency ));
			}
			catch (const char* x) {
				throw ResourceException(data.m_name, x, ResourceException::ExceptionType::CouldntLoad);
			}
		}
	}

	inline Object& Resources::getObject(const std::string& name)
	{
		for (auto& x : objects) {
			if (x->getName() == name) {
				return x->getObjectRef();
			}
		}
		throw ResourceException(name, "Could not find the object!", ResourceException::ExceptionType::ObjectNotFound);
	}

	inline void Resources::deleteObject(const std::string& name)
	{
		std::list<std::unique_ptr<Object>>::iterator it = objects.begin();
		while (it != objects.end()) {
			if (it->get()->getName() == name)
				break;
			it++;
		}
		if (it != objects.end()) {
			objects.remove(*it);
		}
		else {
			throw ResourceException(name, "Could not find the object!", ResourceException::ExceptionType::ObjectNotFound);
		}
	}
}