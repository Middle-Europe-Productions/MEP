////////////////////////////////////////////////////////////
//
//	ResourceManger.cpp created with the use of SFML
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
#include<MEPGraphics/ResourceManager.h>

namespace MEP
{
	Resource::Resource(const U_int32 group, Object&& object):
		m_ID(object.getID()),
		m_group(group),
		local(&object)
	{
		m_type = ResourceType::Move;
	}
	Resource::Resource(const ResourceType type, const U_int32 ID, const std::string& name, unsigned int nofFrames, bool transparency) :
		Resource(type, ID, AssetsGroup::UserAssets, name, nofFrames, transparency)
	{
	}

	Resource::Resource(const ResourceType type, const U_int32 ID, const U_int32 group, const std::string& name, unsigned int nofFrames, bool transparency) :
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

	Resource::Resource(const U_int32 ID, const std::string& name, unsigned int nofFrames, bool transparency) :
		//by default we are assigning it to the MEP::UserAssets (-1)
		Resource(ID, -1, name, nofFrames, transparency)
	{}

	Resource::Resource(const U_int32 ID, const U_int32 group, const std::string& name, unsigned int nofFrames, bool transparency) :
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

	Resource::Resource(const U_int32 ID, std::list<sf::Image>& images, const std::string& name, bool transparency) :
		//by default we are assigning it to the MEP::UserAssets (-1)
		Resource(ID, -1, images, name, transparency)
	{
	}

	Resource::Resource(const U_int32 ID, const U_int32 group, std::list<sf::Image>& images, const std::string& name, bool transparency) :
		m_ID(ID),
		m_group(group),
		m_name(name),
		m_transparency(transparency),
		m_array(&images)
	{
		m_type = ResourceType::ImageArray;
	}

	void Resources::loadResources() {
		isInit = true;
	};

	Resources::Resources(const std::string& path) :
		m_path(path) 
	{};

	bool Resources::isLoaded() const 
	{ 
		return isInit; 
	}

	Object& Resources::getObject(const U_int32 ID, const U_int32 group)
	{
		return MEPtools::GroupManager<MEP::Object>::_get(ID, group);
	}

	sf::Font& Resources::getFont(const U_int32 ID, const U_int32 group)
	{
		return MEPtools::GroupManager<MEP::Font>::_get(ID, group).getFont();
	}

	void Resources::deleteObject(const U_int32 ID, const U_int32 group)
	{
		MEPtools::GroupManager<MEP::Object>::_deleteElement(ID, group);
	}

	void Resources::deleteObjectsGroup(const U_int32 group)
	{
		MEPtools::GroupManager<MEP::Object>::_deleteGroup(group);
	}

	void Resources::deleteFont(const U_int32 ID, const U_int32 group)
	{
		MEPtools::GroupManager<MEP::Font>::_deleteElement(ID, group);
	}

	void Resources::deleteFontGroup(const U_int32 group)
	{
		MEPtools::GroupManager<MEP::Font>::_deleteGroup(group);
	}

	Resources::~Resources() 
	{}
}