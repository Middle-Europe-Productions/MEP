### Welcome to the Middle Europe Productions begginers tutorial here is the list of the lessons:
 1. Simple Window
 2. Simple Objects, Text and custom Window
 3. Handling events and simple animations.
 4. Static objects, position, scale and rect rect forulas, following animations and moving view.

### 1. Simple Window
To create a simple window we will need to create a new class and inherit MEP::Window::Template::Application. 
``` cpp
class TreeDrawer : public MEP::Window::Template::Application {
     ...
}
```
Secondly, you will need to properly create a constructor. MEP::Window::Template::Application takes up to five arguments.
First is a title of the window (const char *), second resolution of the window (sf::Vector2u), third style of the window (U_int32), fourth setting (sf::ContextSettings). At this point, I would like to highlight some things. As you can see all of those methods are strictly related to the SFML library. That is because MEP is using it to display the output. In the following example, I am using one of the futures (sf::Style::Modern_Resize) that is not available in the SFML. To get this working you will need to build SFML on your own using CMake with [this](https://github.com/Middle-Europe-Productions/MEP/tree/master/SFML_2.5.1_Changes) files replaced.
``` cpp
TreeDrawer::TreeDrawer() :
	MEP::Window::Template::Application("Tree Drawer", "resources/", { 500, 500 }, sf::Style::Modern_Resize)
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
    addWindow(new MEP::Window::Template::Hub(1, *this, sf::Color::Blue));
    latestWindow().changeStatus(MEP::Window::BaseWindow::Status::Main);
}
```
In the aforementioned example I am using addWindow() method which is designed to load the MEP::BaseWindow into the application memory. In the basic example we will use one of the other build in Templates a Hub. Hub class adds an interactive bar which is capable of repositioning, closing and minimizing the window. Second method latestWindow() outputs the latest added window. Third method changeStatus() changes the status of the window. In the library we have five states of the window:
 - ```MEP::Window::BaseWindow::Status::Entrance``` - enables all of the animations with the RunAtEntry and RunAtEntryAndEnd tag and then switches the state to Main.
- ```MEP::Window::BaseWindow::Status::Exit``` - examples of the animations with the RunAtEnd and RunAtEntryAndEnd tag waits for them to finish the execution and then changes the tag to NullAction
- ```MEP::Window::BaseWindow::Status::InProgress``` - windows with this tag is visible but events are not processed.
- ```MEP::Window::BaseWindow::Status::NullAction``` - windows with the tag is not visible.

```createResources()``` is used to load resources into the memory. Resources are loaded thanks to the initResources(...) method.
``` cpp
void TreeDrawer::createResources()
{
    initResources(MEP::Resource(1, "kw"), MEP::Resource(MEP::ResourceType::Font, 1, "Arialn.ttf"));
}
```
initResources() method accepts MEP::Recource() and this is a point where you will need to remember some rules in order to use resource management efficiently and effectively. Those are the constructors of the ```MEP::Resource```
```cpp
1. Resource(const ResourceType type, const U_int32 ID, const std::string& name, unsigned int nofFrames = 1, bool transparency = false) :
2. Resource(const ResourceType type, const U_int32 ID, const U_int32 group, const std::string& name, unsigned int nofFrames = 1, bool transparency = false) :
3. Resource(const U_int32 ID, const std::string& name, unsigned int nofFrames = 1, bool transparency = false) :
4. Resource(const U_int32 ID, const U_int32 group, const std::string& name, unsigned int nofFrames = 1, bool transparency = false) :
5. Resource(const U_int32 ID, std::list<sf::Image>& images, const std::string& name, bool transparency = false) :
6. Resource(const U_int32 ID, const U_int32 group, std::list<sf::Image>& images, const std::string& name, bool transparency = false) :
```	
Let's consider some common variables. First of all, each resource has its ```ID```. The ```ID``` needs to be unique in every ```group```. As you can see some of the constructors allow you not to specify the group. In that case, the object is assigned to the UserAssets (see ```Assets.h``` for more information). Currently, two types of files are accepted by the method.```.png```and ```.ttf```. The ```name``` variable specifies the local path of an object. What is the local path? Let's assume that we want to load ```image.png```. Its path is C:/MyFiles/image.png. Now let's take a step back to the application initialization as you probably remember we specified ```resources``` path. In that case, let it be ```resources = C:/MyFiles/``` . The local path will be image.png isn't it?  No, MEP **does not** want you to use ```.png``` so the local path of the C:/MyFiles/image.png will be ```image```. Some of the constructors allow you to input a ```nofFrames``` of images in that case u just need to keep proper naming. Let's say that we want to input 10 images. First of all, they all need to have the same ```local path name``` second of all frames do need to be numbered from ```0 - 9```. In that case ```../image0.png```,  ```../image1.png```, ...,  ```../image9.png```. If you want to initialize a ```font``` you will need to use **1.** or **2.** constructor and specify the ```MEP::RecourceType::Font```. Finally, we have ```transparency``` if set to true code will create an alpha channel mask. This is especially useful in the ```MEP::Button``` class. All of the aforementioned steps will lead to the creation of one of the two things ```sf::Font``` in case of initialization of the font and ```MEP::Object``` otherwise.

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

This is the end of _1. Simple Window_ 


### 2. Simple Objects, Text and custom Window
To create your custom window you will need to develop a new class and inherit ```MEP::Window::BaseWindow.```
```cpp
class TreeRenderer : public MEP::Window::BaseWindow {
	....
};
```
The only thing that is left is a proper constructor. ```MEP::Window::BaseWindow``` forces us to specify an ```ID``` which needs to be unique. 
```cpp
TreeRenderer::TreeRenderer(MEP::Window::Template::Application& base) :
	MEP::Window::BaseWindow(10),
{}
```
Having all of that done we can start to develop our window content. In that tutorial, I am going to create a ```MEP::TextureObject``` and a ```MEP::Text```. The first is capable of displaying a ```.png``` file and the second displays the text using ```.ttf```. Lets add them to the private members of the class.
```cpp
private:
    MEP::TextureObject object;
    MEP::Text* text;
```
Keep in mind that neither MEP::TextureObject nor MEP::Text have a default constructor. It means that we will need to initialize ```object``` in the constructor, ```text```  is a pointer so you can construct it whenever you would like I will do that in the constructor body.
```cpp
TreeRenderer::TreeRenderer(MEP::Window::Template::Application& base) :
	MEP::Window::BaseWindow(10),
	object(MEP::TextureObject(base.get<MEP::Object>(1), {200, 200}))
{
    text = new MEP::Text("It is simple :)", base.get<sf::Font>(1), 40, {100, 100});
}
```
At this stage, you can start exploring MEP library functionalities you can for example change the color of the ```text```.
```cpp
text->setColor(sf::Color::Blue);
```
To display our objects on the screen, u will need to add them to the ```MEP::BaseWindow``` objects list.
```cpp
newObjects(object, text);
```
Of course, do not forget about the destruction of the text.
```cpp
TreeRenderer::~TreeRenderer()
{
	delete text;
}
```
Finally, to display our custom window we will go back to the ```createWindow()``` method in ```MainApp.cpp```.  
```cpp
void TreeDrawer::createWindows()
{
	...
	addWindow(new TreeRenderer(*this));
	latestWindow().changeStatus(MEP::Window::BaseWindow::Status::InProgress);
}
```

This is the end of _2. Simple Objects, Text and custom Window_

### 3. Handling events and simple animations.
**Events**
Handling events should always be done using ```handleEvent(...)``` method build inside of the ```MEP::BaseWindow``` class. The event handling process is done thanks to the SFML library for more information look [here](https://www.sfml-dev.org/tutorials/2.5/window-events.php). The method should be overwritten in the following way.
```cpp
void TreeRenderer::handleEvent(sf::RenderWindow& Window, sf::Event& event)
{
    ...
}
```
Remember that u need to change the status of the window. InProgress and NullAction will not handle events.
```cpp
void TreeDrawer::createWindows()
{
    ...
    addWindow(new TreeRenderer(*this));
    latestWindow().changeStatus(MEP::Window::BaseWindow::Status::Main);
}
```
**Animations**
MEP library provides a variety of animations. In that part I am going to describe two of them ```MEP::AnimationPosition``` and ```MEP::AnimationColor``` they both work similarly. Here are the constructors:
```cpp
AnimationPosition(const double entry, const double exit, sf::Time length, const float frameRate = 120, const double begin = 0, const double end = 100, std::function<double(double x)> function = [](double x)->double{ return x; }) :
AnimationColor(sf::Color entry, sf::Color exit, sf::Time length, const float frameRate = 120, const double begin = 0,const double end = 10, std::function<double(double x)> function = [](double x)->double { return x; }) :		
```
First, two input parameters are responsible for the ```entry``` and ```exit``` state of the animations in the case of ```MEP::AnimationPosition``` it is always a **change**. This means that when you apply the animation on an object with the position **{x, y}** on an **x** axis. The actual position of an object will be **{x + change, y}**. On the other hand ```MEP::AnimationColor``` apply the current color of animation to the object. The third argument defines the ```length``` of the animation. The fourth argument stands for the number of frames of the animation. Remember that high framerate generates a high amount of calculations but low framerate will result in an unnatural 'teleportation'. The rest of the arguments stands for the function parameters. Let ```function``` be **F(x)** and **x ∈ <```begin```, ```end```>**. **x** will be generated in the distance ```length```/(1/```frameRate```) from the predecessor, furthermore, **F(x)** will need to satisfy the following statement: **max(F(0), F(1), F(2), ..., F(number_of_frames - 1)) = exit** and **min(F(0), F(1), F(2), ..., F(number_of_frames - 1)) = entry**. As a result of that, the graph of a function is shifted and ten each **m * F(0), m * F(1), m * F(2), ..., m * F(number_of_frames - 1)** is calculated. Now lets move to the practically applicable. Firsly, we should add our objects as a private members of the class.
```cpp
private:
	MEP::AnimationPosition* animation;
	MEP::AnimationColor* color_animation;
```
And construct them somewhere in the class.
```cpp
animation = new MEP::AnimationPosition(0, 100, sf::milliseconds(1000));
color_animation = new MEP::AnimationColor(sf::Color::Green, sf::Color::Blue, sf::milliseconds(1000), 120, 0, 100, [](double in) { return std::pow(in, 3); });
```
If you would like to apply the animation to the MEP members you will need to use **setFollow()** method. In case of ```MEP::AnimationPosition```.
```cpp
object.setFollow(*animation, MEP::Following::FollowType);
```
Where MEP::Following::FollowType in that case can be used with.
 * MEP::Following::FollowType::X_Scale - X scale change of an object,
 * MEP::Following::FollowType::Y_Scale - Y scale change of an object,
 * MEP::Following::FollowType::X_Pos - X position change on an object,
 * MEP::Following::FollowType::Y_Pos - Y position change on an object,

On the other hand, ```MEP::AnimationColor``` can be constructed slightly differently.
```cpp
object.setFollow(*color_animation, MEP::U_int32 toFollow);
```
Thanks to the **toFollow** u can pick up the channel which you would like to apply on objects. Each object has an RGBA channel (R-red, G-green, B-blue, A-alpha), ```MEP::ColorAnimations``` also operates on RGBA. Thanks to the second parameter you can pick up which channel you would like to **change**, use ```MEP::ColorChannel``` for that. For example, if you would like to apply the animation on R-red and A-alpha channel you should use **setFollow(...)** in the following way:
```cpp
object.setFollow(*color_animation, MEP::ColorChannel::R | MEP::ColorChannel::A);
```
Finally, your animation will not work if you do not add it to the objects list.
```
newObjects(animation, color_animation);
```
This is the end of _3. Handling events and simple animations_.