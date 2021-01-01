
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
			ResourceAlreadyExists,
			WrongResourceConstructor,
			ObjectNotFound,
			GroupNotFound,
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
		* \brief A deffinition of an individual resource.
		*/
		struct Resource: public NonCopyable {
			const U_int32 m_ID;
			const U_int32 m_group;
			const std::string m_name;
			Resources::ResourceType m_type;
			unsigned int m_nofFrames = 0;
			bool m_transparency = false;
			std::list<sf::Image>* m_array = nullptr;
			/**
			* Resource contructor. It is capable of creating Single and Multi resource.
			* @param[in] ID : An ID of a resource.
			* @param[in] name : Name of a resource.
			* @param[in] nofFrames : Number of textures. 1 by default.
			* @param[in] transparency : True if we want an object to generate alpha channel table. False by default.
			*/
			Resource(const U_int32 ID, const std::string& name, unsigned int nofFrames = 1, bool transparency = false) :
				//by default we are assigning it to the MEP::UserAssets (-1)
				Resource(ID, -1, name, nofFrames, transparency)
			{}
			/**
			* Resource contructor. It is capable of creating Single and Multi resource.
			* @param[in] ID : An ID of a resource.
			* @param[in] group : A group of a resource.
			* @param[in] name : Name of a resource.
			* @param[in] nofFrames : Number of textures. 1 by default.
			* @param[in] transparency : True if we want an object to generate alpha channel table. False by default.
			*/
			Resource(const U_int32 ID, const U_int32 group, const std::string& name, unsigned int nofFrames = 1, bool transparency = false) :
				m_ID(ID),
				m_group(group),
				m_name(name), 
				m_transparency(transparency), 
				m_type(Resources::ResourceType::Single)
			{
				if (nofFrames == 0)
					throw ResourceException(name, "Number of frames!", ResourceException::ExceptionType::WrongResourceConstructor);
				if (nofFrames > 1)
					m_type = Resources::ResourceType::Multi;
				m_nofFrames = nofFrames;
			}
			/**
			* Resource contructor. It is capable of creating ImageArray resource.
			* @param[in] ID : An ID of a resource.
			* @param[in] name : Name of a resource.
			* @param[in] nofFrames : Number of textures. 1 by default.
			* @param[in] transparency : True if we want an object to generate alpha channel table. False by default.
			*/
			Resource(const U_int32 ID, std::list<sf::Image>& images, const std::string& name, bool transparency = false) :
				//by default we are assigning it to the MEP::UserAssets (-1)
				Resource(ID, -1, images, name, transparency)
			{
			}
			/**
			* Resource contructor. It is capable of creating ImageArray resource.
			* @param[in] ID : An ID of a resource.
			* @param[in] group : A group of a resource.
			* @param[in] name : Name of a resource.
			* @param[in] nofFrames : Number of textures. 1 by default.
			* @param[in] transparency : True if we want an object to generate alpha channel table. False by default.
			*/
			Resource(const U_int32 ID, const U_int32 group, std::list<sf::Image>& images, const std::string& name, bool transparency = false) :
				m_ID(ID),
				m_group(group),
				m_name(name),
				m_transparency(transparency),
				m_array(&images) 
			{
				m_type = Resources::ResourceType::ImageArray;
			}
		};
	private:
		struct Group {
			const U_int32 group_ID;
			std::list<std::unique_ptr<Object>> objects;
			Group(const U_int32& ID) : group_ID(ID) {}
		};
	private:
		const std::string m_path;
		bool isInit = false;
		//List of the objects
		std::list<Group> objects;
		//Method loading individual resource
		void load(const Resource& data);
		void loadResources() { 
			isInit = true; 
		};
		//Forwarding method
		template <typename First, typename ... Rest>
		void loadResources(First&& first, Rest&& ... rest);
		//finds or of creates a new group
		std::list<std::unique_ptr<Object>>& findOrAdd(const U_int32& group) {
			for (auto& x : objects)
				if (x.group_ID == group)
					return x.objects;
			objects.push_back(Group(group));
			return objects.back().objects;
		}
		//adds an object to a group
		void check(std::list<std::unique_ptr<Object>>& x, const U_int32& ID) {
			for(auto& it: x)
				if(it.get()->getID() == ID)
					throw ResourceException(it.get()->getName(), "Resource already exists in that group!", ResourceException::ExceptionType::ResourceAlreadyExists);
		}
		//find or throws an exception
		template<typename Type>
		Object& find(const U_int32& group, Type method)
		{
			for (auto it = objects.begin(); it != objects.end(); ++it) {
				if (it->group_ID == group) {
					for (auto ele = it->objects.begin(); ele != it->objects.end(); ++ele)
						if (method(ele))
							return ele->get()->getObjectRef();
					throw ResourceException("unknown", "Could not find a resource!", ResourceException::ExceptionType::ObjectNotFound);
				}				
			}
			throw ResourceException("unknown", "Could not find a group!", ResourceException::ExceptionType::GroupNotFound);
		}
		//find or throws an exception
		template<typename Type>
		void remove(const U_int32& group, Type method)
		{
			for (auto it = objects.begin(); it != objects.end(); ++it) {
				if (it->group_ID == group) {
					for (auto ele = it->objects.begin(); ele != it->objects.end(); ++ele)
						if (method(ele))
							it->objects.remove(*ele);
				}
				else
					throw ResourceException("unknown", "Could not find a resource!", ResourceException::ExceptionType::ObjectNotFound);
			}
			throw ResourceException("unknown", "Could not find a group!", ResourceException::ExceptionType::GroupNotFound);
		}
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
		* @param[in] group : Group of a MEP::Object.
		* @return Reference to MEP::Object.
		*/
		Object& getObject(const std::string& name, const U_int32 group = -1);
		/**
		* Deletes MEP::Object with agiven name.
		* @param[in] name : Name of a MEP::Object.
		* @param[in] group : Group of a MEP::Object.
		*/
		void deleteObject(const std::string& name, const U_int32 group = -1);
		/**
		* Outputs created MEP::Object
		* @param[in] ID : ID of a MEP::Object.
		* @param[in] group : Group of a MEP::Object.
		* @return Reference to MEP::Object.
		*/
		Object& getObject(const U_int32 ID, const U_int32 group = -1);
		/**
		* Deletes MEP::Object with agiven name.
		* @param[in] name : ID of a MEP::Object
		* @param[in] group : Group of a MEP::Object.
		*/
		void deleteObject(const U_int32 ID, const U_int32 group = -1);
		/**
		* Deletes all MEP::Object.
		* @param[in] name : Name of a MEP::Object.
		*/
		void deleteObjects() {
			objects.clear();
		}
		virtual ~Resources() {
			deleteObjects();
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
		//finds the target group
		std::list<std::unique_ptr<Object>>& x = findOrAdd(data.m_group);
		//check is the resource already exists in a group
		check(x, data.m_ID);
		if (data.m_type == ResourceType::Multi) {
			try {
				x.push_back(std::make_unique<MEP::Object>(data.m_ID, m_path, data.m_name, data.m_nofFrames, data.m_transparency));
			}
			catch (const char* x) {
				throw ResourceException(data.m_name, x, ResourceException::ExceptionType::CouldntLoad);
			}
		}
		else if (data.m_type == ResourceType::Single) {
			try {
				x.push_back(std::make_unique<MEP::Object>(data.m_ID, m_path, data.m_name, data.m_transparency ));
			}
			catch (const char* x) {
				throw ResourceException(data.m_name, x, ResourceException::ExceptionType::CouldntLoad);
			}
		}
		else if (data.m_type == ResourceType::ImageArray) {
			try {
				x.push_back(std::make_unique<MEP::Object>(data.m_ID, *data.m_array, data.m_name, data.m_transparency ));
			}
			catch (const char* x) {
				throw ResourceException(data.m_name, x, ResourceException::ExceptionType::CouldntLoad);
			}
		}
	}

	inline Object& Resources::getObject(const std::string& name, const U_int32 group)
	{
		std::cout << "ID:" << name << ", gourp: " << group << std::endl;
		return find(group, [name](auto& element) -> bool
			{
				return element->get()->getName() == name;
			});
	}

	inline void Resources::deleteObject(const std::string& name, const U_int32 group)
	{
		remove(group, [name](std::list<std::unique_ptr<Object>>::iterator& element) -> bool
			{
				return element->get()->getName() == name;
			});
	}

	inline Object& Resources::getObject(const U_int32 ID, const U_int32 group)
	{
		return find(group, [ID](auto& element) -> bool
			{
				return element->get()->getID() == ID;
			});
	}

	inline void Resources::deleteObject(const U_int32 ID, const U_int32 group)
	{
		remove(group, [ID](std::list<std::unique_ptr<Object>>::iterator& element) -> bool
			{
				return element->get()->getID() == ID;
			});
	}
}