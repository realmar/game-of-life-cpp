Game Of Life
============

Reference: [Wikipedia: Game of Life](https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life) and [Wikipedia: Cellular Automata](https://en.wikipedia.org/wiki/Cellular_automaton)

This is a simple implementation of the game of life in a finite space using c++ and opengl.

With finite space I mean that the cells will interact with the border of the window as if their world ends there.

### Controls

```sh
c: clear screen
s: start simulation
r: randomize cells

mouse click: toggle cell
mouse drag: revive cells

# models
1: glider gun
2: acron
```

### Compile

```sh
$ git clone https://github.com/realmar/game-of-life-cpp.git
$ cd game-of-life-cpp

# install depedencies
$ vcpkg install opengl freeglut

# compile
$ cmake CMakeLists.txt

# linux
$ make
# windows
$ msbuild game-of-life.sln
```
