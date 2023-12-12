# cub3D - Raycasting in C

## Description

This project was made as a collaborative effort between [samih713](https://github.com/samih713/) and [Taanviir](https://github.com/Taanviir)

This is a project from the 42 school curriculum. The goal is to create a raycasting engine in C, using the miniLibX library. Using the raycasting technique, the program will display a 3D view of a maze, with a first person perspective much like the legendary game [Wolfenstein 3D](https://en.wikipedia.org/wiki/Wolfenstein_3D). The program will also be able to display a textured walls, floor and ceiling with different colors.

The user or player in this case can move around the maze using the WASD keys, and rotate the camera using the left and right arrow keys. (See more in the [Usage](#usage) section below)

![gif of gameplay](./gameplay.gif)

## Installation

To install the program, simply run the following command in the root directory of your choice:

```
git clone https://github.com/Taanviir/cub3D.git
```

To go into the root directory of the project, use:
```
cd cub3D
```

To compile the program and create the executable file, `cub3D`, use:
```
make
```

## Usage

Run the program using:
```
./cub3D <map.cub>
```

The program will read the map file and display the maze in a new window.

Maps can be found in the `maps` directory. The program will only accept maps with the `.cub` extension.

Use the `W` `A` `S` `D` keys to move around the maze.

Use the `←` `→` keys to move the camera left and right.

Use the `ESC` key or click the red cross in the top left corner of the window to exit the program.

## Resources

- [Lode's Computer Graphics Tutorial](https://lodev.org/cgtutor/raycasting.html)
