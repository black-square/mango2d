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
