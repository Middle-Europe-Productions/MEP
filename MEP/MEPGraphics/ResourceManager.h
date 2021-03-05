
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
#include<MEPGraphics/Font.h>
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
	class Resources: protected MEPtools::GroupManager<MEP::Object>, protected MEPtools::GroupManager<MEP::Font> {
		const std::string m_path;
		bool isInit = false;
		//Method loading individual resource
		void load(const Resource& data);
		void loadResources() { 
			isInit = true; 
		};
		//Forwarding method
		template <typename First, typename ... Rest>
		void loadResources(First&& first, Rest&& ... rest);
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
		bool isLoaded() const { return isInit; }
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
		* Deletes MEP::Object with a given name.
		* @param[in] name : ID of a MEP::Object
		* @param[in] group : Group of a MEP::Object.
		*/
		void deleteObject(const U_int32 ID, const U_int32 group = -1);
		/**
		* Deletes MEP::Object(s) within a given group.
		* @param[in] group : Group of a MEP::Object.
		*/
		void deleteObjectsGroup(const U_int32 group);
		/**
		* Deletes sf::Font with agiven name.
		* @param[in] name : ID of a sf::Font
		* @param[in] group : Group of a sf::Font.
		*/
		void deleteFont(const U_int32 ID, const U_int32 group = -1);
		/**
		* Deletes sf::Font(s) within a given group.
		* @param[in] group : Group of a sf::Font.
		*/
		void deleteFontGroup(const U_int32 group);
		/**
		* Deletes all MEP::Object.
		* @param[in] name : Name of a MEP::Object.
		*/
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

	inline void Resources::load(const MEP::Resource& data)
	{
		if (data.m_type == ResourceType::Multi) {
			try {
				if (!MEPtools::GroupManager<MEP::Object>::insert(data.m_ID,
					data.m_group,
					std::make_unique<MEP::Object>(data.m_ID, m_path, data.m_name, data.m_nofFrames, data.m_transparency))) {
					throw ResourceException(data.m_name, "Resource already exists in that group!", ResourceException::ExceptionType::ResourceAlreadyExists);
				}
			}
			catch (const char* x) {
				throw ResourceException(data.m_name, x, ResourceException::ExceptionType::CouldntLoad);
			}
		}
		else if (data.m_type == ResourceType::Single) {
			try {
				if (!MEPtools::GroupManager<MEP::Object>::insert(data.m_ID,
					data.m_group,
					std::make_unique<MEP::Object>(data.m_ID, m_path, data.m_name, data.m_transparency))) {
					throw ResourceException(data.m_name, "Resource already exists in that group!", ResourceException::ExceptionType::ResourceAlreadyExists);
				}
			}
			catch (const char* x) {
				throw ResourceException(data.m_name, x, ResourceException::ExceptionType::CouldntLoad);
			}
		}
		else if (data.m_type == ResourceType::ImageArray) {
			try {
				if(!MEPtools::GroupManager<MEP::Object>::insert(data.m_ID, 
					data.m_group, 
					std::make_unique<MEP::Object>(data.m_ID, *data.m_array, data.m_name, data.m_transparency))) {
					throw ResourceException(data.m_name, "Resource already exists in that group!", ResourceException::ExceptionType::ResourceAlreadyExists);
				}
			}
			catch (const char* x) {
				throw ResourceException(data.m_name, x, ResourceException::ExceptionType::CouldntLoad);
			}
		}
		else if (data.m_type == ResourceType::Font) {
			if (!MEPtools::GroupManager<MEP::Font>::insert(data.m_ID, 
				data.m_group, 
				std::make_unique<MEP::Font>(data.m_ID, data.m_name, m_path))) {
				throw ResourceException(data.m_name, "Resource already exists in that group!", ResourceException::ExceptionType::ResourceAlreadyExists);
			}
		}
	}

	inline Object& Resources::getObject(const U_int32 ID, const U_int32 group)
	{
		return MEPtools::GroupManager<MEP::Object>::get(ID, group);
	}

	inline sf::Font& Resources::getFont(const U_int32 ID, const U_int32 group)
	{
		return MEPtools::GroupManager<MEP::Font>::get(ID, group).getFont();
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
		MEPtools::GroupManager<MEP::Object>::deleteElement(ID, group);
	}

	inline void Resources::deleteObjectsGroup(const U_int32 group)
	{
		MEPtools::GroupManager<MEP::Object>::deleteGroup(group);
	}

	inline void Resources::deleteFont(const U_int32 ID, const U_int32 group)
	{
		MEPtools::GroupManager<MEP::Font>::deleteElement(ID, group);
	}

	inline void Resources::deleteFontGroup(const U_int32 group)
	{
		MEPtools::GroupManager<MEP::Font>::deleteGroup(group);
	}
}

#endif
