# Patch notes

### 28.10.2020
## MEP Lib version alpha 1.0
	-Initial implementation.

### 12.11.2020
## MEP Lib version alpha 1.1:
	-Added documentation. \n
	-Added memory management. \n
	-Added view functionality for the BaseWindow. \n
	-Reorganized templates.

### 24.11.2020
## MEP Lib version alpha 1.2:
	-Improved methods naming. \n
	-Added MEP::Sprite type. Provides access to the sf::Sprite as well as MEP::Animation functionalities. \n
	-Implementation of a MEP::TextObject with the full support of the MEP lib elements. \n
	-Implementation of a MEP::AnimationColor it works with the use of MEP::Following. Generally it is another type of a FollowType. Enjoy :) \n
	-DrawTag has been added to the MEP::Drawable object. Currently only ViewLock is avalible. If window is using custom view an object with the tag will be rendered using master app view. \n
	-Added << operator for all MEP::Sprite(MEP::TextureObject, MEP::Button, MEP::AnimationObject) and MEP::Text. The operator copies position, scale and color (Following attributes) to a left object. \n
	-When ID of a MEP::Window::WindowException is not specified exception will ba a master exception.
	-better naming & getLastAccess(); in base manager.
### 1.01.2021
## MEP lib version alpha 1.3
	-Added OSSetUp.h which specifies the operating systems. Currently only MEP_WINDOWS is avalible. \n
	-Added WindowData.h responsible for window and view management. \n
	-Changed naming WindowsStat.h -> WindowStat.h \n
	-Reorganized resource management: \n
		*Now there is a Assets.h which defines some basic assets. \n
		*Now resource have its own unique U_int32(MEPGraphics/Config.h) ID. \n
		*The ID needs to be specified on the input. \n
		*The ID needs to be unique in every group. \n
		*Group is defined by the user. Currently there are 2 "hard coded" groups. \n
		1.UserAssets - a default assets direction. If you do not specify the group your resource goes here. \n
		2.HUB - all of the HUB assets. \n
		*To access the resource u do need to use one of the methods: \n
		getObject(const U_int32 ID, const U_int32 group = -1) \n
		getObject(const std::string& name, const U_int32 group = -1) \n
		*To access the build in assets/your simply: \n
		getObject(MEP::HUB::Box, MEP::AssetsGroup::HUB) \n
		*Hint: To enhance your work create enums same as in the Assets.h\n
		Do not use AssetsGroup (-1, -2) there are reserved for the engine. \n
	-The 1.3 version comes with the modified version of SFML 2.5.1 \n
		*In order to achive full mep experience u will need to download SFML 2.5.1 and replace the files. \n
		*All of the files are in the SFML_2.5.1_Changes folder. \n 
		*Please keep in mind that I do not own any rights the the files. \n
		*All of the changes are marked in the following way: \n
		/// <MEP Modification> \n
		Implementation \n
		/// </MEP Modification> \n
		*Those are the changes related to sf::Style::None not really looking the best. \n
		*A new *Windows exclusive* styles are avalible. sf::Style::Modern and sf::Style::Modern_Resize == sf::Style::Modern | sf::Style::Resize. \n
		*If you do not edit the SFML sf::Style::None is the equivalent of sf::Style::Modern. \n
		*Unfortuantely, resizing the sf::Style::None is not avalible in the SFML. \n
		*What is the difference between None and Modern? \n
		*Modern style has the WS_POPUP tag (borderless window) but with the addition of windows animations and drop shadow. \n
		*Furthermore it is possible to resize it thanks to the sf::Style::Modern_Resize. \n
	-A new Drawable tag & more.
		*It is possible to mix the drawable tags (they are bitwise now). \n
		*A new tag Resize_Pos was added. \n
		*When set it is going to be used when the window is resized. \n
		*It executes the calculation method to recalculate the position of an objects. \n
		*You do need to provide the method with the use of: addMethodPos(...) \n
### 13.01.2021
## MEP lib version alpha 1.3.1
	-Better memory management. \n
	-General code improvements. \n
	-Added Font resource type. \n
	-A new methods were added to ResourceManager. get<Type>(ID, group) enables you to quick access fonts & objects. \n
	-Better constructors. \n
	-Examples were added. \n
### 20.02.2021
## MEP lib version alpha 1.3.2
	-Now u can reset the animation position/color. \n
	-Fixed memory leaks. \n
	-Better Button functionallities (force actions forcePress() forcePressed(), forceRelease(), forceReleased and block button activity block()) \n
	-Now there is a possibility of setting the any sort of an animation for the objects of the HUB thanks to the setFollow() method. \n
	-MEP::TextObject now can output sf::Text object thanks to getText method. The getText method(which outputs the content of the string) is now getString() \n
	-AnimationColor R channel locked at 10 bugfix. \n
	-Fixed groups in get method from resource exception. \n
	-Now there is a method to setDirection of an animation. \n
	-Fixed a bug which blocked interaction with the button with following list active. \n
	-Now while connecting the MEP::ColorAnimation to the objects you can limit it to the RGBA channel \n
	-Now u can use up to 4 MEP::ColorAnimation in one objects (for each individual channel) \n
	-Now there is a possibility to add lower importance objects. In the future there are going to be layers. (newObject(object, true(lower importance))\n
	-If you move the texture using movePosition() method it will be applyed on addMethodPos() \n
### 16.03.2021
## MEP lib version alpha 1.3.3
	-Improved MEP::Loading class. \n	
	-Deleted Window namespace. \n
	-Recreated the Resource class. Now individual members are using GroupManager which is a map<map>. In other wards groups, manager and subgroup manager is a balancing tree. Which provides better access time O(logn + logm) instead of O(n + m). Where n is the number of groups and m is the number of elements in the n-th group. \n
	-Library share the same aforementioned container. \n
	-Diagnostic tool for the BaseWindow class is now available. debugOutput(std::osteam& out) will output information regarding the order of displaying the object of the screen every object currently available in the render queue. If the message Unavailable was displayed the object was deleted. If the message Base Class was displayed object does not have an override of the << operator. \n
	-Deleted setting window connection in BaseWindow. \n
	-Redesign of application window container. \n
	-Better view manager. \n
	-Namming: Base.h -> BaseWindow.h \n
	-Now you can apply unlimited nummber of animations on the Object. \n
	-New setDelay(const sf::Time&, bool = false) method. Now does not activate the animation and inputs two arguments delay(time, bool = false) where boolean one set to true the delay is activated every time we use run(). If an animation has a tag RunAtEnd or RunAtEntry there is also a possibility of delaying the Entrance and Exit thanks to the setEntryDelay() and setExitDelay() in the case of RunAtLowEnd or RunAtLowEntry you will have to use setLowEntryDelay() and setLowExitDelay() in order to delay Low Entrance and Low Exit. \n
	-Objects and Animations are now Delete safe. If you delete any of the MEP::Drawable, Window and Following lists will ignore it instead of throwing an error. \n
	-You can now divide animations following into groups. \n
	-You can mute follow of the group of animations. \n
	-New animation manager was added. Thanks to that container you can divide animations into groups and execute commands directly on them. Managers run on the shared container. \n
	-Two new window states are added. LowEntry and LowExit. LowEntry menu activates every animation with the RunAtLowEntry tag and then enters the *InProgress state*!. LowExit executes every animation with RunAtLowExit tag and then enters null. \n
	-MEP::Animation::AdditionalTag -> MEP::AdditionalTag & AdditionalTag is now Bitwise \n
## MEP lib version alpha 1.3.4
	-Due to increased compilie times library is exiting header only environment. Now in order to use it you will need to compile it on your own or use one of the presets.
	-MEP::Image library, currently support version of the sf::Image library. It will be capable of generating images.
	-MEP::NonCreatable when inherite it wont be posible to instanceiete a class.
	-ResourceManager now inputs MEP::Objects
	-Simple logging class was added MEP::Log.
	-Logging Object class.