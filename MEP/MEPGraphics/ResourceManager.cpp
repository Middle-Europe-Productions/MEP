#include<MEPGraphics/ResourceManager.h>

namespace MEP
{
	Resource::Resource(const ResourceType type, const U_int32 ID, const std::string& name, unsigned int nofFrames, bool transparency) :
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
	/**
	* Resource contructor. It is capable of creating Single and Multi resource.
	* @param[in] ID : An ID of a resource.
	* @param[in] name : Name of a resource.
	* @param[in] nofFrames : Number of textures. 1 by default.
	* @param[in] transparency : True if we want an object to generate alpha channel table. False by default.
	*/
	Resource::Resource(const U_int32 ID, const std::string& name, unsigned int nofFrames, bool transparency) :
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
	/**
	* Resource contructor. It is capable of creating ImageArray resource.
	* @param[in] ID : An ID of a resource.
	* @param[in] name : Name of a resource.
	* @param[in] nofFrames : Number of textures. 1 by default.
	* @param[in] transparency : True if we want an object to generate alpha channel table. False by default.
	*/
	Resource::Resource(const U_int32 ID, std::list<sf::Image>& images, const std::string& name, bool transparency) :
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