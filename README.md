Game Of Life
============
Reference: https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life

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
# windows
g++ .\main.cpp -I"C:\TDM-GCC-64\include" -L"C:\TDM-GCC-64\bin" -lglu32 -lopengl32 -lfreeglut

# linux
g++  main.cpp -lGL -lglut -lGLU
```
