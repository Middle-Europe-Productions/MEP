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
    latestWindow().changeStatus(MEP::BaseWindow::Status::Main);
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