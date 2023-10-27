# cub3D - Raycasting in C

## Description

This project was made as a collaborative effort between [samih713](https://github.com/samih713/) and [Taanviir](https://github.com/Taanviir)

This is a project from the 42 school curriculum. The goal is to create a raycasting engine in C, using the miniLibX library. Using the raycasting technique, the program will display a 3D view of a maze, with a first person perspective much like the legendary game [Wolfenstein 3D](https://en.wikipedia.org/wiki/Wolfenstein_3D). The program will also be able to display a textured walls, floor and ceiling with different colors.

The user or player in this case can move around the maze using the WASD keys, and rotate the camera using the left and right arrow keys. (See more in the [Usage](#usage) section below)

...attach gif here...

---

## Installation

To install the program, simply run the following command in the root directory of your choice:

`git clone https://github.com/Taanviir/cub3D.git`

---

## Usage

Use `cd cub3D` to go into the root directory of the project.

Run `make` to compile the program. This will create an executable called `cub3D`.

To run the program, type `./cub3D <map.cub>` in the root directory of the project. The program will read the map file and display the maze in a new window.

Maps can be found in the `maps` directory. The program will only accept maps with the `.cub` extension.

To move around the maze, use the `W` `A` `S` `D` keys.

To move the camera left and right, use the `←` `→` keys.

To exit the program, press the ESC key or click the red cross in the top left corner of the window.

---

## Resources

- [Lode's Computer Graphics Tutorial](https://lodev.org/cgtutor/raycasting.html)
