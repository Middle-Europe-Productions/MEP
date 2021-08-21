////////////////////////////////////////////////////////////
//
//	Group.h created with the use of SFML
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
#ifndef MEP_GROUP_H
#define MEP_GROUP_H
#include<MEPGraphics/ResourceException.h>
#include<MEPGraphics/Config.h>
#include<map>

namespace MEPtools {
	/**
	* A library memory management system is built around this container.
	*/
	template<typename X, typename PtrType = std::unique_ptr<X>, typename SecondStructure = std::map<MEP::U_int32, PtrType>>
	class GroupManager {
		/**
		* Master container.
		*/
		std::map<MEP::U_int32, SecondStructure> m_objects;
		/**
		* Size
		*/
		unsigned int size = 0;
		/**
		* Map insert.
		*/
		bool insert(MEP::U_int32 ID, PtrType& value, std::map<MEP::U_int32, PtrType>& input);
		/**
		* List insert
		*/
		bool insert(MEP::U_int32 ID, PtrType& value, std::list<PtrType>& input);
	public:
		GroupManager() = default;
		/**
		* Insert the element at a given spot.
		* When SecondStructure is a std::set or std::map executes in O(logn + m) else  
		* When SecondStructure is a std::list executes in O(m)
		* Where n is a numer of elements in m-th group, and m is a number of groups.
		*/
		bool _insert(MEP::U_int32 ID, MEP::U_int32 group, PtrType value);
		/**
		* Outputs the element.
		*/
		X& _get(MEP::U_int32 ID, MEP::U_int32 group) const;
		/**
		* Outputs the group of elements.
		*/
		SecondStructure& _getGroup(MEP::U_int32 group);
		/**
		* Deletes the group of objects.
		* @return: True - group deleted. False - group not found.
		*/
		bool _deleteGroup(MEP::U_int32 group);
		/**
		* Deletes the object.
		* @return: True - object deleted. False - object not found.
		*/
		bool _deleteElement(MEP::U_int32 ID, MEP::U_int32 group);
		/**
		* Executes method a for all of the elements.
		*/
		template<typename Method>
		void _execute(Method method);
		/**
		* Execute method for a group of objects.
		*/
		template<typename Method>
		bool _execute(Method method, MEP::U_int32 group);
		/**
		* Executes constant method a for all of the elements.
		*/
		template<typename Method>
		void _execute(Method method) const;
		/**
		* Execute  constant method for a group of objects.
		*/
		template<typename Method>
		bool _execute(Method method, MEP::U_int32 group) const;
		/**
		* Diagnostic tool.
		*/
		void _debugOutput(std::ostream& out, const char* before = "", const char* after = "") const;
		/**
		* Diagnostic tool.
		*/
		template<typename Out>
		void _debugOutput(std::ostream& out, Out method) const;
		/**
		* Number of objects.
		*/
		unsigned int _size() const;
		/**
		* Is constainer empty.
		*/
		bool _empty() const;
		/**
		* Clears the map.
		*/
		void _clear();
	};

	template<typename X, typename PtrType, typename SecondStructure>
	bool GroupManager<X, PtrType, SecondStructure>::insert(MEP::U_int32 ID, PtrType& value, std::map<MEP::U_int32, PtrType>& input) {
		++size;
		return input.insert({ ID, std::move(value) }).second;
	}

	template<typename X, typename PtrType, typename SecondStructure>
	bool GroupManager<X, PtrType, SecondStructure>::insert(MEP::U_int32 ID, PtrType& value, std::list<PtrType>& input) {
		input.push_back(std::move(value));
		++size;
		return true;
	}
	template<typename X, typename PtrType, typename SecondStructure>
	bool GroupManager<X, PtrType, SecondStructure>::_insert(MEP::U_int32 ID, MEP::U_int32 group, PtrType value) {
		auto [iterator, status] = m_objects.insert({ group, SecondStructure() });
		return insert(ID, value, iterator->second);
	}

	template<typename X, typename PtrType, typename SecondStructure>
	X& GroupManager<X, PtrType, SecondStructure>::_get(MEP::U_int32 ID, MEP::U_int32 group) const {
		auto iterator = m_objects.find(group);
		if (iterator != m_objects.end()) {
			auto second_insert = iterator->second.find(ID);
			if (second_insert == iterator->second.end()) {
				throw MEP::ResourceException(std::to_string(group), "Could not find a resource!", MEP::ResourceException::ExceptionType::ObjectNotFound);
			}
			return *second_insert->second;
		}
		else {
			throw MEP::ResourceException(std::to_string(group), "Could not find a group!", MEP::ResourceException::ExceptionType::GroupNotFound);
		}
	}

	template<typename X, typename PtrType, typename SecondStructure>
	SecondStructure& GroupManager<X, PtrType, SecondStructure>::_getGroup(MEP::U_int32 group) {
		auto iterator = m_objects.find(group);
		if (iterator != m_objects.end()) {
			return iterator->second;
		}
		else {
			throw MEP::ResourceException(std::to_string(group), "Could not find a group!", MEP::ResourceException::ExceptionType::GroupNotFound);
		}
	}

	template<typename X, typename PtrType, typename SecondStructure>
	bool GroupManager<X, PtrType, SecondStructure>::_deleteGroup(MEP::U_int32 group) {
		auto iterator = m_objects.find(group);
		if (iterator != m_objects.end()) {
			size -= m_objects.size();
			m_objects.erase(iterator);
			return true;
		}
		return false;
	}

	template<typename X, typename PtrType, typename SecondStructure>
	bool GroupManager<X, PtrType, SecondStructure>::_deleteElement(MEP::U_int32 ID, MEP::U_int32 group) {
		auto iterator = m_objects.find(group);
		if (iterator != m_objects.end()) {
			auto second_iter = iterator->second.find(ID);
			if (second_iter == iterator->second.end()) {
				return false;
			}
			else {
				--size;
				iterator->second.erase(second_iter);
				return true;
			}
		}
		return false;
	}

	template<typename X, typename PtrType, typename SecondStructure>
	template<typename Method>
	void GroupManager<X, PtrType, SecondStructure>::_execute(Method method) {
		for (auto& x : m_objects) {
			for (auto& it : x.second) {
				method(it);
			}
		}
	}

	template<typename X, typename PtrType, typename SecondStructure>
	template<typename Method>
	bool GroupManager<X, PtrType, SecondStructure>::_execute(Method method, MEP::U_int32 group) {
		auto iterator = m_objects.find(group);
		if (iterator != m_objects.end()) {
			for (auto& x : iterator->second)
				method(x);
			return true;
		}
		return false;
	}

	template<typename X, typename PtrType, typename SecondStructure>
	template<typename Method>
	void GroupManager<X, PtrType, SecondStructure>::_execute(Method method) const {
		for (auto& x : m_objects) {
			for (auto& it : x.second) {
				method(it);
			}
		}
	}

	template<typename X, typename PtrType, typename SecondStructure>
	template<typename Method>
	bool GroupManager<X, PtrType, SecondStructure>::_execute(Method method, MEP::U_int32 group) const {
		auto iterator = m_objects.find(group);
		if (iterator != m_objects.end()) {
			for (auto& x : iterator->second)
				method(x);
			return true;
		}
		return false;
	}

	template<typename X, typename PtrType, typename SecondStructure>
	void GroupManager<X, PtrType, SecondStructure>::_debugOutput(std::ostream& out, const char* before, const char* after) const {
		for (auto& x : m_objects) {
			out << "Group: " << x.first << std::endl;
			for (auto& it : x.second) {
				out << before << it << after << std::endl;
			}
		}
	}

	template<typename X, typename PtrType, typename SecondStructure>
	template<typename Out>
	void GroupManager<X, PtrType, SecondStructure>::_debugOutput(std::ostream& out, Out method) const {
		for (auto& x : m_objects) {
			out << "Group: " << x.first << std::endl;
			for (auto& it : x.second) {
				method(it, out);
			}
		}
	}
	template<typename X, typename PtrType, typename SecondStructure>
	unsigned int GroupManager<X, PtrType, SecondStructure>::_size() const {
		return size;
	}

	template<typename X, typename PtrType, typename SecondStructure>
	bool GroupManager<X, PtrType, SecondStructure>::_empty() const {
		return _size() == 0;
	}

	template<typename X, typename PtrType, typename SecondStructure>
	void GroupManager<X, PtrType, SecondStructure>::_clear() {
		size = 0;
		m_objects.clear();
	}
}

#endif