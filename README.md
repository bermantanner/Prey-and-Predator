# Prey-and-Predator

## Project Overview

This repository contains my "Prey and Predator" simulation project, which models dynamic interactions between predators "Birds" and their prey "Worms" in a 2D grid environment. The simulation demonstrates realistic mechanics like movement, hunting, breeding, and starvation, with Organism as a base class from which both Bird and Worm classes inherit their properties and behaviors. I have implemented a visual display of the grid with SFML, which I demonstrate in the video below. 

This was super fun to make!!

## Demonstration 
Dark Blue squares are the PREDATORS ("Birds"), Teal squares are the PREY ("Worms"), White squares are empty.

https://github.com/user-attachments/assets/e8e96309-8805-497f-94f8-73772beafb53

Full Video:
[![Prey-Predator Demonstration](https://img.youtube.com/vi/A04MbpMclvs/0.jpg)](https://www.youtube.com/watch?v=A04MbpMclvs)

## Recent Improvements

- **Visual Display with SFML**: Transitioned from a text-based terminal display to a graphical grid using SFML for an intuitive, interactive simulation.
- **General Refactoring**: Significantly refactored the existing code for better efficiency and maintainability
- **findValidMove() Function**: Created a general findValidMove() function to eliminate duplicate code across classes. Optimized the logic by reordering checks to prevent unnecessary iterations.
- **Bad Practices**: Changed public data attributes like character and hasMoved to private and created appropriate getters and setters. Split the code into separate files.
- **Code Organization**: Rearranged the order of functions to improve readability.
- **Comments**: Created more concise, helpful comments.

## Running

How to run this version:

```bash
# Install first
brew install freetype libvorbis

# Update the DYLD_LIBRARY_PATH
export DYLD_LIBRARY_PATH=/opt/homebrew/lib:./lib:$DYLD_LIBRARY_PATH

# Clone the repository
git clone https://github.com/bermantanner/Prey-and-Predator.git

# Navigate to the project directory
cd Prey-and-Predator

# Compile 
make

# Run the simulation
./preyandpredator

# Clean after
make clean
