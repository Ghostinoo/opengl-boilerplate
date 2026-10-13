# OpenGL Boilerplate

![Status](https://img.shields.io/badge/status-work%20in%20progress-orange)
![C++](https://img.shields.io/badge/C%2B%2B-20-blue)
![OpenGL](https://img.shields.io/badge/OpenGL-4.6%2B-green)
![Build](https://img.shields.io/badge/build-Makefile-yellow)

A small, evolving OpenGL boilerplate for starting new graphics experiments.  
It bundles a custom helper library (`gh`) with basic abstractions for shaders, buffers, uniforms, and more.

> **Status:** Early development. APIs and structure may change. Not ready for production use.

## Overview

This project is meant to be a clean starting point for OpenGL projects.  
It currently provides the core setup (GLAD, window/context, shader loading) and a growing set of helper classes under `lib/gh`.

## Requirements

- C++20 compiler
- OpenGL 4.6+ capable GPU/drivers
- GLFW3 and GLM
- GLAD (included in `extlib/`)
- Make

## Build

```bash
make
./bin/app
```

## TODO

- [x] Makefile build setup
- [x] Window creation
- [x] OpenGL context initialization
- [x] Basic buffer and vertices handling
- [x] Basic shader handling
- [ ] Basic textures handling
- [ ] A lot of things

## License
See the LICENSE file for details.