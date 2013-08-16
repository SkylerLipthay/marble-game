# Marble Game

## Synopsis

This is a simple OpenGL powered 3D video game that consists of moving a marble around platforms using the WASD keys to move, the space bar to jump, and the mouse to look around. The goal is to get to a *finish platform* and keep the timer low.

![The Marble Game in action.](www/screenshot.png?raw=true)

## Dependencies

- [Bullet Physics Library](http://bulletphysics.org/) (included in source)
- [JsonCpp](http://jsoncpp.sourceforge.net/) (I really should have used Boost for JSON parsing)
- [Boost](http://www.boost.org/)
- [SDL](http://www.libsdl.org/)
- OpenGL
- The infamous SkyLib (modified, included)

## Details

The source code is shamefully messy. I never even bothered to rename the game source folder from *skylib_test* to *marble_game*.

Marble Game is currently targeted for Windows using MinGW. I started developing it on Mac OS X, but I guess finished on Windows. Apparently I was getting really lazy here with cross-platform compatibility. Good luck compiling.

This is all just really a messy OpenGL demo; don't judge too hard.