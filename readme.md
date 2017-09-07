# Eden [![Build Status](https://travis-ci.org/CruizeMissile/Eden.svg?branch=master)](https://travis-ci.org/CruizeMissile/Eden)
Eden is a cross platform c++ game engine. It is archetected around Entity-Component-System and a multi api renderer.

# Quick start
#### Note: Currently Eden is developed on windows and linux (manjaro/arch). Eden uses the lastest and greatest c++ 17 features.

### Windows
``` bash
$ git submodule init ; git submodule update
$ mkdir build ; cd build
$ cmake -G "Visual Studio 15 2017" ..
$ cmake --build .
```

### Linux
``` bash
$ git submodule init ; git submodule update
$ mkdir build ; cd build
$ cmake ..
$ cmake --build .
```

# In development
Eden is currently in development and is not feature complete.

# Dependencies
All Dependencies used under their respective licenses. Copyright is held by their respective owners.
* [Catch](https://github.com/philsquared/Catch)
* [Glew](http://glew.sourceforge.net)
* [Gsl](https://github.com/Microsoft/GSL)
* [Loguru](https://github.com/emilk/loguru)
* [Vulkan](https://www.khronos.org/vulkan/)
