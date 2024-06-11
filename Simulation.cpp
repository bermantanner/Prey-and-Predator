#include "Simulation.h"

Simulation::Simulation() : rng(random_device()()) {}

void Simulation::generateGrid() {
    grid.resize(gridSize, vector<Organism*>(gridSize, nullptr));
}

void Simulation::displayGrid() const {
    for (int row = 0; row < gridSize; row++) {
        for (int col = 0; col < gridSize; col++) {
            if (grid[row][col] == nullptr) {
                cout << "- ";
            } else {
                cout << grid[row][col]->getCharacter() << ' ';
            }
        }
        cout << endl;
    }
}

void Simulation::populateGrid() {
    srand(static_cast<unsigned>(time(nullptr)));
    int numWorms = 100;
    int numBirds = 10;
    int wormsAdded = 0;
    int birdsAdded = 0;

    // Spawning worms.
    while (wormsAdded < numWorms) {
        int row = rand() % gridSize;
        int col = rand() % gridSize;
        if (grid[row][col] == nullptr) {
            grid[row][col] = new Worm;
            wormsAdded++;
        }
    }

    // Spawning birds.
    while (birdsAdded < numBirds) {
        int row = rand() % gridSize;
        int col = rand() % gridSize;
        if (grid[row][col] == nullptr) {
            grid[row][col] = new Bird;
            birdsAdded++;
        }
    }
}

void Simulation::timeStep() {
    // Changing all the "hasMoved"'s to false.
    for (int row = 0; row < grid.size(); row++) {
        for (int col = 0; col < grid[0].size(); col++) {
            if (grid[row][col] != nullptr) {
                grid[row][col]->setHasMoved(false);
            }
        }
    }

    // For each bird, check if they should starve, if not, attempt to eat and move, or just move.
    for (int row = 0; row < grid.size(); row++) {
        for (int col = 0; col < grid[0].size(); col++) {
            Organism* currentOrganism = grid[row][col];
            if (currentOrganism != nullptr && currentOrganism->getCharacter() == 'X' && !currentOrganism->getHasMoved()) {
                if (currentOrganism->getNumStepsNoFood() >= 3) {
                    currentOrganism->starve(grid, row, col);
                } else {
                    currentOrganism->moveToEat(grid, row, col, rng);
                }
            }
        }
    }

    // Moving the worms.
    for (int row = 0; row < grid.size(); row++) {
        for (int col = 0; col < grid[0].size(); col++) {
            Organism* currentOrganism = grid[row][col];
            if (currentOrganism != nullptr && currentOrganism->getCharacter() == 'o' && !currentOrganism->getHasMoved()) {
                currentOrganism->move(grid, row, col, rng);
            }
        }
    }

    // Breeding the worms.
    for (int row = 0; row < grid.size(); row++) {
        for (int col = 0; col < grid[0].size(); col++) {
            Organism* currentOrganism = grid[row][col];
            if (currentOrganism != nullptr && currentOrganism->getCharacter() == 'o') {
                if (currentOrganism->getNumSteps() % 3 == 0 && currentOrganism->getNumSteps() != 0) {
                    currentOrganism->breed(grid, row, col, rng);
                }
            }
        }
    }

    // Breeding the birds.
    for (int row = 0; row < grid.size(); row++) {
        for (int col = 0; col < grid[0].size(); col++) {
            Organism* currentOrganism = grid[row][col];
            if (currentOrganism != nullptr && currentOrganism->getCharacter() == 'X') {
                if (currentOrganism->getNumSteps() % 8 == 0 && currentOrganism->getNumSteps() != 0) {
                    currentOrganism->breed(grid, row, col, rng);
                }
            }
        }
    }
}

void Simulation::displayStats() const {
    int wormCount = 0;
    int birdCount = 0;

    for (int row = 0; row < gridSize; row++) {
        for (int col = 0; col < gridSize; col++) {
            Organism* currentOrganism = grid[row][col];
            if (currentOrganism != nullptr) {
                if (currentOrganism->getCharacter() == 'o') {
                    wormCount++;
                } else if (currentOrganism->getCharacter() == 'X') {
                    birdCount++;
                }
            }
        }
    }

    cout << "Number of Worms: " << wormCount << endl;
    cout << "Number of Birds: " << birdCount << endl;
}

