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

This is the end of 2. Simple Objects, Text and custom Window