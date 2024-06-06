# Prey-and-Predator

## Project Overview

This repository contains the initial rough draft of my "Prey-and-Predator" simulation. This project, originally developed as part of my earlier work, aims to simulate the dynamic interactions between predators "Birds" and their prey "Worms" in a 2D grid. The Organism class serves as a common base class from which Birds and Worms are derived, inheriting its properties. The simulation includes mechanics for moving, hunting, breeding and starvation.

## Current Status: Rough Draft

The current version of the codebase is a **rough draft**. It is an older project that I am revisiting with fresh eyes and new skills. As such, the code and documentation reflect an early stage of development and are subject to significant changes. In this version, worms breed every three timesteps, birds breed every eight. If a bird goes three timesteps without eating a worm, it will starve. Birds will look at adjacent grid spaces for worms to eat. 

## Objectives for Revival

As I work to revive this project, this is what I plan to do (may continue to add to this):

- **Refactoring and Optimization**: Enhance the codebase for improved performance and easier maintainability...Removing public data variables and other bad practices. Additionally, split the code into multiple files.
- **Implementation onto website**: Learn about Emscripten and WebAssembly, attempt to implement the C++ logic onto a webpage. Learn the basics of Javascript, HTML, and CSS to build this simple website. Implement interactive controls allowing users to configure various simulation parameters directly through the web interface.

## Running

How to run this version:

```bash
# Clone the repository
git clone https://github.com/bermantanner/Prey-and-Predator.git

# Navigate to the project directory
cd Prey-and-Predator

# Compile the project (specific commands depend on your environment)
gcc -o simulation main.c

# Run the simulation
./simulation

