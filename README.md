# mango2d

### Rapid 2D Game Prototyping Engine
**mango2d** is a cross platform 2D game engine specially designed for fast 2D games prototyping. It uses **C++11** and [BOOST libraries](http://wwww.boost.org) to provide powerful yet easy-to-use features out of the box. It is highly modulized and based on [SDL Framework] (http://www.libsdl.org/), but uses only **OpenGL** for rendering. 

### Features
* Cross platform developing on Windows and Mac OS
* [Mit licence](http://choosealicense.com/licenses/mit/)
* Components oriented: you can use only modules that you want
* [Logging](../blob/master/Core/Log.h), [common macroses](../blob/master/Core/CommonMacros.h), [easy string formating](../blob/master/Core/StrFormat.h) (`boost::format` based)
* Powerful [Point](../blob/master/Core/Point.hpp), [Rect](../blob/master/Core/Rect.hpp), [Size](../blob/master/Core/Size.hpp) and [Color](../blob/master/Graphics/Color.hpp) classes that interact with each other
* Many [interpolation functions](../blob/master/Core/Interp.hpp) including physically reliable spring formula
* [Intrusive lists](../blob/master/Core/TinyList.hpp) for fast collection manipulating without memory allocations 
* [Sprite](../blob/master/Graphics/Texture.h) loading from common formats (PNG, JPG, TIFF) and drawing with scale, transparency and color blending. One texture can contain many frames
* [Font](../blob/master/Graphics/Font.h) loading from TTF format
* [Sound engine](../blob/master/Audio/)
* [Particles engine](../blob/master/Particles/)
* [GUI framework](../blob/master/Gui/): collection of GUI widgets and GUI states for rapid interface development
* Special `boost::shared_ptr` [delete strategy](../blob/master/Logic/DefferedSharedPtrDeleter.hpp) that keeps object destruction until `Update()` method finishes, but weak pointers become expired immediately. It simplifies AI logic
* etc.
