# Building BOOST

# Downloading BOOST sources
[BOOST](http://www.boost.org) 1.53 or newer is required
http://sourceforge.net/projects/boost/files/boost/1.53.0/ 

## Building BOOST on Mac for Apple LLVM compiler 4.2
```bash
./b2 -a --with-filesystem --with-chrono --layout=tagged --toolset=clang link=static threading=multi \
cxxflags="-arch i386 -arch x86_64 -stdlib=libc++ -std=c++11 -mmacosx-version-min=10.7 \
-fvisibility-inlines-hidden" stage debug release
```

## Building BOOST on Mac for LLVM GCC 4.2 (NOT USED)
```bash
./b2 --with-filesystem --with-chrono --toolset=clang --layout=tagged link=static stage debug release
```

## Building BOOST on Windows
```bash
./b2  --with-filesystem --with-chrono link=static stage debug release
```

### Usefull b2 flags
  `./b2 -a`: rebuild al

  `./b2 -d+2`: print commands before execution

  `./b2 cxxflags="-v"`: print compiler info (add it to both XCode properties and b2 command line then compare versions)