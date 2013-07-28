# mango2d

### Rapid 2D Game Prototyping Engine
**mango2d** is a cross platform 2D game engine specially designed for fast 2D games prototyping. 
It uses **C++11** and [BOOST libraries](http://wwww.boost.org) to provide powerful yet easy-to-use 
features out of the box. It is highly modulized and based on [SDL Framework] (http://www.libsdl.org/), 
but uses only **OpenGL** for rendering. 

### Features
* Cross platform developing on Windows and Mac OS
* [Mit licence](http://choosealicense.com/licenses/mit/)
* Components oriented: you can use only modules that you want
* [Logging](Core/Log.h), [common macroses](Core/CommonMacros.h), 
  [easy string formating](Core/StrFormat.h) (`boost::format` based)
* Powerful [Point](Core/Point.hpp), [Rect](Core/Rect.hpp), [Size](Core/Size.hpp) and 
  [Color](Graphics/Color.hpp) classes that interact with each other
* Many [interpolation functions](Core/Interp.hpp) including physically reliable spring formula
* [Intrusive lists](Core/TinyList.hpp) for fast collection manipulating without memory allocations 
* [Sprite](Graphics/Texture.h) loading from common formats (PNG, JPG, TIFF) and drawing with scale, 
  transparency and color blending. One texture can contain many frames
* [Font](Graphics/Font.h) loading from TTF format
* [Sound engine](Audio/)
* [Particles engine](Particles/)
* [GUI framework](Gui/): collection of GUI widgets and GUI states for rapid interface development
* Special `boost::shared_ptr` [delete strategy](Logic/DefferedSharedPtrDeleter.hpp) that keeps 
  object destruction until `Update()` method finishes, but weak pointers become expired immediately. 
  It simplifies AI logic
* etc.

### Demo
#### GemsGame
![GemsGame screenshot](https://raw.github.com/wiki/black-square/mango2d/img/GemsGame2.jpg)

**[More info and Mac/Win binaries links >>>](https://github.com/black-square/GemsGame/README.md)**

#### TagGame
![TagGame screenshot](https://raw.github.com/wiki/black-square/mango2d/img/TagGame.png)

**[More info and Mac/Win binaries links >>>](https://github.com/black-square/TagGame/README.md)**
