# Eden

> **A modern cross platform c++ game engine built with vulkan, opengl and c++17.**

## Building

Eden uses cmake as it's build system. With this it can be compiled on Windows, Mac and Linux. Eden uses C++17 so a 
compiler with C++17 features is required (see [tested toolchains](#tested-toolchains) for more details). For external dependencies
Eden has them as git submodules. Make sure that you initialize and update your git submodules before trying to use Eden.

```bash
$ git submodule update --init --recursive
$ cmake . -Bbuild
$ cmake --build build
```

## Development

Eden is currently in development and is not feature complete. The design and structure of eden is being tested so big 
refactoring changes happen quite frequently. This is a side project that I work on in my free time so developement
is scattered and not structured.

## Dependencies

All Dependencies used under their respective licenses. Copyright is held by their respective owners.

* Catch : A single file header only unit testing library.
* Glfw : A free, Open Source, multi-platform library for OpenGL, OpenGL ES and Vulkan application development.
* Pride : My core library
* Scaffold : A template/scaffolding/helper library for cmake files in your project

## Tested toolchains
| Compiler     | Operating System              | Architecture | Version String |
| -------------|-------------------------------|--------------|----------------|
| Clang 4.0    | Arch linux                    | x64          | gcc version ...|
