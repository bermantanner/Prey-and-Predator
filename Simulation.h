#include "SFML/Graphics.hpp"

#include "Organism.h"
#include "Worm.h"
#include "Bird.h"
#include <iostream>

class Simulation {
private:
    default_random_engine rng;          // Random number generator.
    const int gridSize;                 // The grid's size.
    int cellSize;                       // rendering cell size
    vector<vector<Organism*> > grid;    // The 2D grid.
    sf::RenderWindow* window;           // pointer to SFML window

public:
    Simulation(int gridSize, sf::RenderWindow* window, int windowSize);
    ~Simulation();

    // render() generates, populates, and displays the grid (using SFML)
    void render();

    // timeStep() holds a lot of logic for each "time step" of the simulation.
    // In order: sets all hasMoved flags to false, starves OR attempts to eat for all predators, 
    //           attempts to move for all prey, attempts to breed prey, attempts to breed predators.
    void timeStep();

    // generateGrid() initializes a 2D grid of size gridSize.
    // void generateGrid();

    // displayGrid() uses a nested loop to display the 2D grid using character symbols organisms and blank spaces.
    // void displayGrid() const;

    // populateGrid() randomly selects a spot, checks if its blank, then places a prey or predator there. Populates the gird.
    // (This function could definitely be optimized, possibly in future update).
    // void populateGrid();

    

    // displayStats() simply counts up and displays the number of worms and birds.
    // void displayStats() const;
};