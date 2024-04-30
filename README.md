# Cub3d

Cub3d is our project attempting to be the most simplistic version of Wolfenstein 3D developed by John Carmak and John Romero. In it, you will find a 3D world seen from a FPS view, meaning you cannot see the player. The game initself is comprised of 4 sets of walls, each of them having their own texture depending on their orientation (North, South, West, East).<br />

Our player, just like the set of walls can also be orientated towards a particular orientation. The player can move sideways, front and back. Wall colisions are enabled so that the player may not go through a wall.<br />

To execute the game, you have to compile this repo which will give you: `./cub3d`. Pair it with any other map of your choice, some examples are included in this repo in `maps/`. The program only accepts one map per execution, try and run more it will throw an error.<br />

## Parsing

As mentionned above, to execute the game, a map needs to be passed to the executable. The map has to end by `.cub` and must be composed of only 6 possible characters: 0 for an empty space, 1 for a wall, and N,S,E or W for the player’s start position and spawning orientation.

The file containing the map has to contain the paths for the respective texture of each orientation as well as the colors of the floor and ceiling of the game.

The parsing is very methodic in that it makes a great use of pointers, at least much better use than my previous graphical project [42_Fractol](https://github.com/PGCL1/42_Fractol). Each function only receive the elements in needs from the structure as opposed to receiving the whole structure. In hindsight, I should have created the windown, only if the map was valid as opposed to after. The window has to be creaed before parsing the textures as those images when read are pushed in the memory of the window.

## Raycasting

This is the interesting part so to speak. Raycasting is a method by which one can find the closest distance from a object to another object. It is cleverly used in computer graphics to map out the distance between a player and its surrondings and to draw out these surrondings in function of the player's distance to those. Sounds a bit confusing, I'm aware. Basically, the closer the player is to an object the bigger the object looks; the further the object is relative to the player, the smaller it seems.

To create the raycaster, we made use of the DDA algorithm, here's a great video about it [Youtube link](https://www.youtube.com/watch?v=W5P8GlaEOSI).

## Installation

```bash
git clone git@github.com:PGCL1/cub3D.git
cd cub3D && make
./cub3D [maps/all_floor.cub]
```
## Some visuals 

![](gif/cub3d.mov)
