# How to install and use
mongo2d requires [SDL Framework] (http://www.libsdl.org/) with several additional libraries and 
[BOOST libraries](http://wwww.boost.org). Also, it requres up-to-date compilers from Microsoft and Apple.

## Compilers
* **Windows**: `MS Visual Studio 2012 (11.0.60610.01 Update 3)` and newer
* **Mac**: `XCode 4.6.2` and newer

## How to build BOOST
Please have a look to [this page](Building-BOOST.md)

## How to install SDL
### Windows
1. Download [SDL-devel-1.2.15-VC.zip](http://www.libsdl.org/download-1.2.php), 
   [SDL_image-devel-1.2.12-VC.zip](http://www.libsdl.org/projects/SDL_image/) and 
   [SDL_ttf-devel-2.0.11-VC.zip](http://www.libsdl.org/projects/SDL_ttf/)
2. Extract these archives to the dir `SDL` on the same level as project source folder to obtain this dirs structure: 
    
    ```
    SDL\SDL_image-1.2.12\
    SDL\SDL_ttf-2.0.11\
    SDL\SDL-1.2.15\
    boost_1_53_0\
    <your_project_dir>\
    ```

### Mac
1. Download [SDL-1.2.15.dmg](http://www.libsdl.org/download-1.2.php),
   [SDL_image-1.2.12.dmg](http://www.libsdl.org/projects/SDL_image/) and 
   [SDL_ttf-2.0.11.dmg](http://www.libsdl.org/projects/SDL_ttf/)

2. Copy the `*.framework` folders to `/Library/Frameworks`


## How to create a new project

1. Create new dir for your project (see `<your_project_dir>` above)
2. `git init .`
3. `git submodule add -b master https://github.com/black-square/mango2d.git Engine`
4. Copy files from [demo project] (https://github.com/black-square/GemsGame):

   ```
   MacProject.xcodeproj\*
   MacResources\*
   .gitignore
   EngineParams.cpp
   stdafx.cpp
   project.vcxproj.filters
   Resource.h
   stdafx.h
   targetver.h
   main.ico
   small.ico
   project.rc
   project.sln
   project.vcxproj.user
   project.vcxproj
   ```
5. Launch `project.sln` on Windows or `MacProject.xcodeproj` on Mac
6. Correct source files list added to project (Sometimes it is much easier to exclude all 
   files and then to add them from scratch)
7. Change `struct EngineParamsImpl` implementation
8. Rename `Project` in MSVC on Windows or `Target` in XCODE on Mac as you want
