### 1. Simple Window
In order to create a simple window will need to create a new class and inherit MEP::Template::Application. 
``` cpp
class TreeDrawer : public MEP::Template::Application {
     ...
}
```
Secondly, you will need to properly create constructor. MEP::Template::Application takes up to five arguments.
First is a title of the window (const char *), second resolution of the window (sf::Vector2u), third style of the window (U_int32), fourth setting (sf::ContextSettings). At this point I would like to higlight some things. As yo can see all of those method are stricly realted to the SFML library. That is bacause MEP is using it to display the output. In the folowing example I am using one of the futures (sf::Style::Modern_Resize) that is not available in the SFML. In order to get this working you will need to build SFML on your own using cmake with [this](https://github.com/Middle-Europe-Productions/MEP/tree/master/SFML_2.5.1_Changes) files replaced.
``` cpp
TreeDrawer::TreeDrawer() :
	MEP::Template::Application("Tree Drawer", "resources/", { 500, 500 }, sf::Style::Modern_Resize)
{}
```
Thirdly, you will need to override two of the MEP::Application methods.
```cpp
void createWindows() override;
void createResources() override;
```
```createWindows()``` is used to create windows the content of this method should look in the following way:
``` cpp
void TreeDrawer::createWindows()
{
    addWindow(new MEP::Template::Hub(1, *this, sf::Color::Blue));
    latestWindow().changeStatus(MEP::BaseWindow::Status::Main);
}
```
In the aforementioned example I am using addWindow() method which is designed to load the MEP::BaseWindow into the application memory. In the basic example we will use one of the other build in Templates a Hub. Hub class adds an interactive bar which is capable of repositioning, closing and minimizing the window. Second method latestWindow() outputs the latest added window. Third method changeStatus() changes the status of the window. In the library we have seven states of the window:
 - ```MEP::BaseWindow::Status::Entrance``` - enables all of the animations with the RunAtEntry tag and then switches the state to Main.
- ```MEP::BaseWindow::Status::LowEntrance``` - enables all of the animations with the RunAtLowEntry tag and then switches the state to InProgress.
- ```MEP::BaseWindow::Status::Exit``` - enables all of the animations with the RunAtEnd and RunAtEntryAndEnd tag waits for them to finish the execution and then changes the tag to NullAction
- ```MEP::BaseWindow::Status::LowExit``` - enables all of the animations with the RunAtLowEnd tag waits for them to finish the execution and then changes the tag to NullAction
- ```MEP::BaseWindow::Status::Main``` - window with this tag is visible and all of the evenets are precessed.
- ```MEP::BaseWindow::Status::InProgress``` - window with this tag is visible but events are not processed.
- ```MEP::BaseWindow::Status::NullAction``` - window with the tag is not visible.

While developing your first app it is crucial to follow the following window operation diagram:
    *`Status::Entrance` -> `Status::Main` -> `Status::Exit`* 
    or 
    *`Status::LowEntrance` -> `Status::InProgress` -> `Status::LowExit`*
Thanks to that approach you will be able to easily animate your window without worrying about activating the animation. MEP Library will do that for you!

```createResources()``` is used load resources into the memory. Resources are loaded thanks to the initResources(...) method.
``` cpp
void TreeDrawer::createResources()
{
    initResources(MEP::Resource(1, "kw"), MEP::Resource(MEP::ResourceType::Font, 1, "Arialn.ttf"));
}
```
initResources() method accepts MEP::Recource() and this is a point where you will need to remember some rules in order to use resource management efficiently and effectively. Those are the constructors of the MEP::Resoure
```cpp
1. Resource(const ResourceType type, const U_int32 ID, const std::string& name, unsigned int nofFrames = 1, bool transparency = false) :
2. Resource(const ResourceType type, const U_int32 ID, const U_int32 group, const std::string& name, unsigned int nofFrames = 1, bool transparency = false) :
3. Resource(const U_int32 ID, const std::string& name, unsigned int nofFrames = 1, bool transparency = false) :
4. Resource(const U_int32 ID, const U_int32 group, const std::string& name, unsigned int nofFrames = 1, bool transparency = false) :
5. Resource(const U_int32 ID, std::list<sf::Image>& images, const std::string& name, bool transparency = false) :
6. Resource(const U_int32 ID, const U_int32 group, std::list<sf::Image>& images, const std::string& name, bool transparency = false) :
```	
Let's consider some common variables. First of all each resource have it's ```ID```. The ```ID``` needs to be unique in every ```group```. As you can see some of the constructors allow you not to specify the group. In that cases object is assigned to the UserAssets (see ```Assets.h``` for more information). Currently there are two types of files that are accepted by the method.```.png```and ```.ttf```. The ```name``` variable specify the local path of an object. What is the local path? Let's assume that we want to load ```image.png```. It's path is C:/MyFiles/image.png. Now let's take a step back to the application initialization as you probably remember we specified ```resources``` path. In that case let it be ```resources = C:/MyFiles/``` . The local path will be image.png isn't it? No actually MEP **does not** want you to use ```.png``` so the local path of the C:/MyFiles/image.png will be ```image```. Some of the constructors allows you to input a ```nofFrames``` of images in that case u just need to keep proper naming. Let's say that we want to input 10 images. First of all they all need to have the same ```local path name``` second of all frames does need to be numered from ```0 - 9```. In that case ```../image0.png```,  ```../image1.png```, ...,  ```../image9.png```. If you want to initialize a ```font``` you will need to use **1.** or **2.** constructor and specify the ```MEP::RecourceType::Font```. Finally, we have ```transparency``` if set to true code will create an alpha channel mask. This is especially useful in the ```MEP::Button``` class. All of the aforementioned steps will lead to creation of one of the two things ```sf::Font``` in case of initialization of the font and ```MEP::Object``` otherwise.

Finally, we can execute our code with the following main.
```cpp
#include"MainApp.h"

int main()
{
	TreeDrawer object;
	object.initApp();
	object.setFramerateLimit(120);
	object.run();
}
```
I highly, recommend you to limit your framerate at some point of the development. ```setFraerateLimit(...)``` does that.

This is the end of 1. Simple Window 