////////////////////////////////////////////////////////////
//
//	AnimationBase created with the use of SFML
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
#ifndef MEP_GROUP_SET
#define MEP_GROUP_SET
#include<MEPGraphics/Group.h>
/**
* Manages a set of group elements.
*/
namespace MEPtools {
	/**
	* Represents a set of groups.
	* Used in classes handling varius resource in a slightly better way.
	*/
	template <typename ...Tree>
	class GroupSet : protected Tree...{
	public:
		template<typename X>
		X& get(MEP::U_int32 ID, MEP::U_int32 group) const {
			return GroupManager<X>::_get(ID, group);
		}
		template<typename X>
		bool insert(MEP::U_int32 ID, MEP::U_int32 group, std::unique_ptr<X> value) {
			return GroupManager<X>::_insert(ID, group, value);
		}
		template<typename X>
		std::map<MEP::U_int32, std::unique_ptr<X>>& getGroup(MEP::U_int32 group) {
			return GroupManager<X>::_getGroup(group);
		}
		template<typename X>
		bool deleteGroup(MEP::U_int32 group) {
			return GroupManager<X>::_deleteGroup(group);
		}
		template<typename X>
		bool deleteElement(MEP::U_int32 ID, MEP::U_int32 group) {
			return GroupManager<X>::_deleteElement(ID, group);
		}
		template<typename X, typename Method>
		void execute(Method method) {
			GroupManager<X>::_execute(method);
		}
		template<typename X, typename Method>
		void execute(Method method, MEP::U_int32 group) {
			GroupManager<X>::_execute(method, group);
		}
		template<typename X>
		void debugOutput(std::ostream& out, const char* before = "", const char* after = "") {
			GroupManager<X>::_debugOutput(out, before, after);
		}
	};
}

#endif