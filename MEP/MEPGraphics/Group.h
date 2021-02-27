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
#include"ResourceException.h"
#include"Config.h"
namespace MEP {
	/**
* Object group manager.
* \brief Simple group manager.
*/
	template<typename X>
	class Group {
	public:
		//Id of the group.
		const MEP::U_int32 group_ID;

		//Container of the objects.
		std::list<std::unique_ptr<X>> objects;
	public:
		//Constructor.
		Group(const MEP::U_int32& ID) : group_ID(ID) {}

		//finds an element with a given method
		template<typename Method>
		X* find(Method method) const {
			for (auto& x : objects) {
				if (method(x)) {
					return x.get();
				}
			}
			return nullptr;
		}

		template<typename Method>
		bool remove(Method method) {
			for (auto ele = objects.begin(); ele != objects.end(); ++ele)
				if (method(ele)) {
					objects.remove(*ele);
					return true;
				}

			return false;
		}

		std::list<std::unique_ptr<X>>& get() {
			return objects;
		}

		//outputs the ID of a group
		MEP::U_int32 getID() const {
			return group_ID;
		}
	};

	template<typename X>
	class GroupManager {
		std::map<MEP::U_int32, Group<X>> m_objects;
	public:
		GroupManager() = default;

		//add 
		void add(MEP::U_int32 ID) {
			if (auto& x = m_objects.find(ID)) {
				x.get();
			}
		}
	};
}

#endif