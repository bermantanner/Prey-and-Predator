# Prey-and-Predator

## Project Overview

This repository contains my "Prey and Predator" simulation project. This originally developed as part of my early school work. It is an older project that I am revisiting with fresh eyes and new skills as a side project over the summer. I aim to continue to refactor this project from it's rough early stages and implement it into an easy to access website.

This project simulates dynamic interactions between predators "Birds" and their prey "Worms" in a 2D grid. The Organism class serves as a common base class from which Birds and Worms are derived, inheriting its properties. The simulation includes mechanics for moving, hunting, breeding, and starvation.

## Changelog from Rough Draft
Here are my improvements so far since revisiting this project:

- **General Refactoring**: Significantly refactored the existing code for better efficiency and maintainability
- **findValidMove() Function**: Created a general findValidMove() function to eliminate duplicate code across classes. Optimized the logic by reordering checks to prevent unnecessary iterations.
- **Bad Practices**: Changed public data attributes like character and hasMoved to private and created appropriate getters and setters. Split the code into seperate files.
- **Code Organization**: Rearranged the order of functions to improve readability.
- **Comments**: Created more consistent and concise comments.

## Objectives for Revival

As I work to revive this project, this is what I plan to do (may continue to add to this):

- **Refactoring and Optimization**: Continue enhancing the codebase for improved performance and easier maintainability. Make sure that every parameter intended for user control are configurable through user input, not hard-coded. 
- **Implementation onto website**: Prepare the codebase for web implementation. Learn about Emscripten and WebAssembly, attempt to implement the C++ logic onto a webpage. Learn the basics of Javascript, HTML, and CSS to build this simple website. Implement interactive controls allowing users to configure various simulation parameters directly through the web interface.

## Running

How to run this version:

```bash
# Clone the repository
git clone https://github.com/bermantanner/Prey-and-Predator.git

# Navigate to the project directory
cd Prey-and-Predator

# Compile the project (specific commands depend on your environment)
gcc -o simulation preyandpredator.c

# Run the simulation
./simulation

