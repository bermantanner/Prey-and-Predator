# Prey-and-Predator

## Project Overview

This repository contains my "Prey and Predator" simulation project, which models dynamic interactions between predators "Birds" and their prey "Worms" in a 2D grid environment. The simulation demonstrates realistic mechanics like movement, hunting, breeding, and starvation, with Organism as a base class from which both Bird and Worm classes inherit their properties and behaviors. I plan to implement a visual, interactive display using SFML.

## Recent Improvements

- **General Refactoring**: Significantly refactored the existing code for better efficiency and maintainability
- **findValidMove() Function**: Created a general findValidMove() function to eliminate duplicate code across classes. Optimized the logic by reordering checks to prevent unnecessary iterations.
- **Bad Practices**: Changed public data attributes like character and hasMoved to private and created appropriate getters and setters. Split the code into separate files.
- **Code Organization**: Rearranged the order of functions to improve readability.
- **Comments**: Created more concise, helpful comments.

## Running

How to run this version:

```bash
# Clone the repository
git clone https://github.com/bermantanner/Prey-and-Predator.git

# Navigate to the project directory
cd Prey-and-Predator

# Compile the project (specific commands depend on your environment)
g++ -o simulation preyandpredator.cpp Organism.cpp Bird.cpp Worm.cpp Simulation.cpp -I.

# Run the simulation
./simulation
