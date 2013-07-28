# Building BOOST

### Downloading BOOST sources
[BOOST 1.53](http://sourceforge.net/projects/boost/files/boost/1.53.0/) is required. You can use newer versions too, 
but you have to change include dir path in projects properties.

1. Download this archive and extract it into the dir `boost_1_53_0` on the same level as source folder
2. Launch `bootstrap.bat` for Windows and `bootstrap.sh` for Mac
 
### Building BOOST on Mac for Apple LLVM compiler 4.2
```bash
./b2 -a --layout=tagged --toolset=clang link=static threading=multi \
cxxflags="-arch i386 -arch x86_64 -stdlib=libc++ -std=c++11 -mmacosx-version-min=10.7 \
-fvisibility-inlines-hidden" stage debug release
```

### ~~Building BOOST on Mac for LLVM GCC 4.2 (NOT USED)~~
```bash
./b2 --toolset=clang --layout=tagged link=static stage debug release
```

### Building BOOST on Windows
```bash
./b2 link=static stage debug release
```

#### Usefull b2 flags
* `./b2 -a`: rebuild al
* `./b2 -d+2`: print commands before execution
* `./b2 cxxflags="-v"`: print compiler info (add it to both XCode properties and b2 command line then compare versions)
* `./b2 --with-filesystem --with-chrono`: Build only specified libraries
