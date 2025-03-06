# MazeRunner3D

Recreating the Iconic Wolfenstein 3D game by implementing the raycasting technology wish enables rendering 3D environments from 2D maps.

![MazeRunner3D](https://fmi4cg1yoq.ufs.sh/f/cVtZuJ9vUYxc9SFNW4svORFVz5YWksKl8DIZ7rgL2duh3Ajw)

## Features

- **Wall Collision:** The player is not able to go through walls
- **Texture Mapping:** Applying textures to the walls of the map
- **Animated Sprites:** Implementing animating sprites that are interactive with user input
- **Customizable Maps And Sprites:** You can create any map you like with any texture you like by just following simple rules.

## Map Costumization

!! Texture should be in a .xpm file format and preferably not exceeding 256x256 in the size

!! The map is formed by 1 and 0, 1 means there is a wall, and 0 means it's empty. The map should always have walls and no empty spaces are allowed if they are not surrounded by walls

F is the color of the floor

C is the color of the ceiling

Each map should be a file of .cub extention and in this form:
```
EA <path to the texture>
NO <path to the texture>
SO <path to the texture>
WE <path to the texture>
 
 
F r,g,b 
C r,g,b
 
111
101
111
```

## How To Run

**Warning: This project is only tested and garranted to work on apple devices, it is not tested in linux**

```bash
git clone https://github.com/Hek3er/MazeRunner3D.git
cd MazeRunner3D
make bonus
```

## Usage

```bash
./Cub3D_bonus maps/bonus/map8.cub
```