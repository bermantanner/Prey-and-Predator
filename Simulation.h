#include "Organism.h"
#include "Worm.h"
#include "Bird.h"
#include <iostream>

class Simulation {
private:
    default_random_engine rng;          // Random number generator.
    const int gridSize = 20;            // The grid's size.
    vector<vector<Organism*> > grid;    // The 2D grid.

public:
    Simulation();

    // generateGrid() initializes a 2D grid of size gridSize.
    void generateGrid();

    // displayGrid() uses a nested loop to display the 2D grid using character symbols organisms and blank spaces.
    void displayGrid() const;

    // populateGrid() randomly selects a spot, checks if its blank, then places a prey or predator there. Populates the gird.
    // (This function could definitely be optimized, possibly in future update).
    void populateGrid();

    // timeStep() holds a lot of logic for each "time step" of the simulation.
    // In order: sets all hasMoved flags to false, starves OR attempts to eat for all predators, 
    //           attempts to move for all prey, attempts to breed prey, attempts to breed predators.
    void timeStep();

    // displayStats() simply counts up and displays the number of worms and birds.
    void displayStats() const;
};