
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
#ifndef MEP_RESOURCE_H
#define MEP_RESOURCE_H

#include<list>
#include<thread>
#include<MEPGraphics/AnimationObject.h>
#include<MEPGraphics/TextureObject.h>
#include<MEPGraphics/NonCopyable.h>
#include<MEPGraphics/FontManager.h>
#include<MEPGraphics/Assets.h>
namespace MEP {
	/**
		* @enum MEP::ExceptionType
		* Provides a types of a Resource.
		*/
	enum class ResourceType {
		/** A simple case to handle the fonts.*/
		Font = 3,
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
	struct Resource : public NonCopyable {
		const U_int32 m_ID;
		const U_int32 m_group;
		const std::string m_name;
		ResourceType m_type;
		unsigned int m_nofFrames = 0;
		bool m_transparency = false;
		std::list<sf::Image>* m_array = nullptr;
		/**
		* Resource contructor. It creates the font.
		* @param[in] ID : An ID of a resource.
		* @param[in] name : Name of a resource.
		* @param[in] nofFrames : Number of textures. 1 by default.
		* @param[in] transparency : True if we want an object to generate alpha channel table. False by default.
		*/
		Resource(const ResourceType type, const U_int32 ID, const std::string& name, unsigned int nofFrames = 1, bool transparency = false) :
			Resource(type, ID, AssetsGroup::UserAssets, name, nofFrames, transparency)
		{
		}
		/**
		* Resource contructor. It creates the font.
		* @param[in] ID : An ID of a resource.
		* @param[in] name : Name of a resource.
		* @param[in] nofFrames : Number of textures. 1 by default.
		* @param[in] transparency : True if we want an object to generate alpha channel table. False by default.
		*/
		Resource(const ResourceType type, const U_int32 ID, const U_int32 group, const std::string& name, unsigned int nofFrames = 1, bool transparency = false) :
			m_ID(ID),
			m_group(group),
			m_name(name),
			m_type(type),
			m_transparency(transparency)
		{
			if (nofFrames == 0)
				throw ResourceException(name, "Number of frames!", ResourceException::ExceptionType::WrongResourceConstructor);
			m_nofFrames = nofFrames;
		}
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
			m_type(ResourceType::Single),
			m_transparency(transparency)
		{
			if (nofFrames == 0)
				throw ResourceException(name, "Number of frames!", ResourceException::ExceptionType::WrongResourceConstructor);
			if (nofFrames > 1)
				m_type = ResourceType::Multi;
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
			m_type = ResourceType::ImageArray;
		}
	};
	/**
	* Resources class is a utility which is meant to be working with all of the MEP::Drawable objects.
	* \brief A main MEP::Drawable cointainer.
	*/
	class Resources: public FontManager {
		const std::string m_path;
		bool isInit = false;
		//List of the objects
		std::list<Group<Object>> objects;
		//Method loading individual resource
		void load(const Resource& data);
		void loadResources() { 
			isInit = true; 
		};
		//Forwarding method
		template <typename First, typename ... Rest>
		void loadResources(First&& first, Rest&& ... rest);

		//finds or of creates a new group
		template<typename Type, typename ListContent>
		std::list<std::unique_ptr<Type>>& findOrAdd(const U_int32& group, std::list<ListContent>& container);

		//adds an object to a group
		template<typename Type>
		void check(std::list<std::unique_ptr<Type>>& x, const U_int32& ID);

		//finds an element
		template<typename Out, typename ListContent, typename Type>
		Out* find(const U_int32& group, Type method, const std::list<ListContent>& container);
		
		//removes an element
		template<typename Out, typename ListContent, typename Type>
		void remove(const U_int32& group, Type method, std::list<ListContent>& container);
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
		* Outputs the font.
		* @param[in] ID : ID of a MEP::Object.
		* @param[in] group : Group of a MEP::Object.
		*/
		sf::Font& getFont(const U_int32 ID, const U_int32 group = -1);
		/**
		* Outputs the Type.
		* if MEP::Objects outputs object.
		* if sf::Font outputs font.
		* @param[in] ID : ID of a MEP::Object.
		* @param[in] group : Group of a MEP::Object.
		*/
		template <typename T>
		T& get(const U_int32 ID, const U_int32 group = -1);
		/**
		* Deletes MEP::Object with agiven name.
		* @param[in] name : ID of a MEP::Object
		* @param[in] group : Group of a MEP::Object.
		*/
		void deleteObject(const U_int32 ID, const U_int32 group = -1);
		/**
		* Deletes sf::Font with agiven name.
		* @param[in] name : ID of a MEP::Object
		* @param[in] group : Group of a MEP::Object.
		*/
		void deleteFont(const U_int32 ID, const U_int32 group = -1);
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

	template<typename Type, typename ListContent>
	inline std::list<std::unique_ptr<Type>>& Resources::findOrAdd(const U_int32& group, std::list<ListContent>& container)
	{
		for (auto& x : container)
			if (x.group_ID == group)
				return x.objects;
		container.push_back(Group<Type>(group));
		return container.back().objects;
	}

	template<typename Type>
	inline void Resources::check(std::list<std::unique_ptr<Type>>& x, const U_int32& ID)
	{
		for (auto& it : x)
			if (it.get()->getID() == ID)
				throw ResourceException(it.get()->getName(), "Resource already exists in that group!", ResourceException::ExceptionType::ResourceAlreadyExists);
	}

	template<typename Out, typename ListContent, typename Type>
	inline Out* Resources::find(const U_int32& group, Type method, const std::list<ListContent>& container)
	{
		for (auto& it : container) {
			if (it.getID() == group) {
				if (Out* x = it.find(method))
					return x;
				throw ResourceException(std::to_string(group), "Could not find a resource!", ResourceException::ExceptionType::ObjectNotFound);
			}
		}
		throw ResourceException(std::to_string(group), "Could not find a group!", ResourceException::ExceptionType::GroupNotFound);
	}

	template<typename Out, typename ListContent, typename Type>
	inline void Resources::remove(const U_int32& group, Type method, std::list<ListContent>& container)
	{
		for (auto& it : container) {
			if (it.getID() == group) {
				if (it.remove(method)) {
					return;
				}
				else {
					throw ResourceException(std::to_string(group), "Could not find a resource!", ResourceException::ExceptionType::ObjectNotFound);
				}
			}
		}
		throw ResourceException(std::to_string(group), "Could not find a group!", ResourceException::ExceptionType::GroupNotFound);
	}

	template<typename ... Values>
	inline void Resources::initResources(Values&& ...values)
	{
		loadResources(std::forward<Values>(values) ...);
	}

	inline void Resources::load(const MEP::Resource& data)
	{
		if (data.m_type == ResourceType::Multi) {
			try {
				//finds the target group
				std::list<std::unique_ptr<Object>>& x = findOrAdd<MEP::Object, Group<MEP::Object>>(data.m_group, objects);
				//check is the resource already exists in a group
				check<Object>(x, data.m_ID);
				x.push_back(std::make_unique<MEP::Object>(data.m_ID, m_path, data.m_name, data.m_nofFrames, data.m_transparency));
			}
			catch (const char* x) {
				throw ResourceException(data.m_name, x, ResourceException::ExceptionType::CouldntLoad);
			}
		}
		else if (data.m_type == ResourceType::Single) {
			try {
				//finds the target group
				std::list<std::unique_ptr<Object>>& x = findOrAdd<MEP::Object, Group<MEP::Object>>(data.m_group, objects);
				//check is the resource already exists in a group
				check<Object>(x, data.m_ID);
				x.push_back(std::make_unique<MEP::Object>(data.m_ID, m_path, data.m_name, data.m_transparency ));
			}
			catch (const char* x) {
				throw ResourceException(data.m_name, x, ResourceException::ExceptionType::CouldntLoad);
			}
		}
		else if (data.m_type == ResourceType::ImageArray) {
			try {
				//finds the target group
				std::list<std::unique_ptr<Object>>& x = findOrAdd<MEP::Object, Group<MEP::Object>>(data.m_group, objects);
				//check is the resource already exists in a group
				check<Object>(x, data.m_ID);
				x.push_back(std::make_unique<MEP::Object>(data.m_ID, *data.m_array, data.m_name, data.m_transparency ));
			}
			catch (const char* x) {
				throw ResourceException(data.m_name, x, ResourceException::ExceptionType::CouldntLoad);
			}
		}
		else if (data.m_type == ResourceType::Font) {
			//finds the target group
			std::list<std::unique_ptr<Font>>& x = findOrAdd<Font, Group<Font>>(data.m_group, fonts);
			//check is the resource already exists in a group
			check<Font>(x, data.m_ID);
			//initialize and add the newly created object.
			x.push_back(std::make_unique<Font>(data.m_ID, data.m_name, m_path));
		}
	}

	inline Object& Resources::getObject(const std::string& name, const U_int32 group)
	{
		std::cout << "ID:" << name << ", gourp: " << group << std::endl;
		return find<MEP::Object>(group, [name](auto& element) -> bool
			{
				return element->getName() == name;
			}, 
			objects)->getObjectRef();
	}

	inline void Resources::deleteObject(const std::string& name, const U_int32 group)
	{
		remove<Object, Group<Object>>(group, [name](std::list<std::unique_ptr<Object>>::iterator& element) -> bool
			{
				return element->get()->getName() == name;
			}, objects);
	}

	inline Object& Resources::getObject(const U_int32 ID, const U_int32 group)
	{
		return find<MEP::Object, Group<MEP::Object>>(group, [ID](auto& element) -> bool
			{
				return element->getID() == ID;
			},
			objects)->getObjectRef();
	}

	inline sf::Font& Resources::getFont(const U_int32 ID, const U_int32 group)
	{
		return find<Font, Group<Font>>(group, [ID](auto& element)->bool
			{
				return element->getID() == ID;
			},
			fonts)->getFont();
	}

	template <typename T>
	inline T& Resources::get(const U_int32 ID, const U_int32 group) {
		if (std::is_same<T, MEP::Object>()) {
			return (T&)getObject(ID, group);
		}
		else if (std::is_same<T, sf::Font>()) {
			return (T&)getFont(ID, group);
		} else
			throw ResourceException("ID: " + std::to_string(ID), "Incorrect type!", ResourceException::ExceptionType::IncorrectType);
	}
	inline void Resources::deleteObject(const U_int32 ID, const U_int32 group)
	{
		remove<Object, Group<Object>>(group, [ID](std::list<std::unique_ptr<Object>>::iterator& element) -> bool
			{
				return element->get()->getID() == ID;
			}, objects);
	}
	inline void Resources::deleteFont(const U_int32 ID, const U_int32 group)
	{
		remove<Font, Group<Font>>(group, [ID](auto& element)->bool
			{
				return element->get()->getID() == ID;
			},
			fonts);
	}
}

#endif
