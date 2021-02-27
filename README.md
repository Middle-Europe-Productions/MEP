![Logo](https://github.com/Middle-Europe-Productions/MEP/tree/master/docs/mepdoc.png)
_alpha v1.3.2_
### Introduction
A MEP library is designed to provide easy to use templates:
 * MEP::Window::Teamplate::Application
    * Build in resource manager.
    * Build in windows manager.
    * All of the sf::RenderWindow futures.
* MEP::Window::Teamplate::Hub
    * Exit button.
    * Minimize button.
    * Integration with the MEP::ColorAnimation
    * Modern design.
* MEP::Window::Teamplate::BaseWindow
    * Easy to use view manager.
    * Automated animation activation.
    * Automated objects displaying.
    * Events handling.

Variety of Objects and Animations:
* MEP::TextureObject
* MEP::Text
* MEP::AnimationObject
* MEP::Button
* MEP::AnimationPosition
* MEP::AnimationColor

### Platforms information and installation
| Platform    |Test platform | Support |Additional features | 
| ----------- | ----------- | --- |------- | 
| Windows    |    Window 10, 64bit  | ✔️      |  ✔️ |
| MacOS      |   macOS Big Surr |   ❌  |    ❌  | 
|Linux |    Ubuntu 20.o4|  ✔️ |  ❌|  

In order to install the MEP library download SFML 2.5.1 from [official webside](https://www.sfml-dev.org/download/sfml/2.5.1/). Then include the [MEP](https://github.com/Middle-Europe-Productions/MEP/tree/master/MEP) file.
**Additional features**
First of all, I would like to highlight that the lack of installation of the additional features will not make the library stopped working. The only thing that you are going to miss is the resizable custom window. Unfortunately, SFML does not provide any support for that solution in a result I had to change some of the files listed in `SFML_2.5.1_Changes`. In order to make it work, you will need to download the SFML 2.5.1 source switch the files, and then build the library using CMake.
**Keep in mind that I do not own any rights to the files in the** `SFML_2.5.1_Changes`. 
All of the changes are marked in the following way:
```
/// <MEP Modification>
Implementation
/// </MEP Modification>
```
### How to learn
For an introduction, I do recommend taking a look at the [examples](https://github.com/Middle-Europe-Productions/MEP/tree/master/examples) folder. For more advanced users there is an open source project [MEP-Data-Structure](https://github.com/Middle-Europe-Productions/MEP-Data-Structures) u can take a look on the code there. 
### Documentation
The documentation is available here: [Middle Europe Productions Documentation](https://middle-europe-productions.github.io/MEP/)

##### Author
Piotr Skibiński