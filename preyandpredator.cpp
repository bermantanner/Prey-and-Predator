#include <iostream>
#include <vector>
#include <ctime>
#include <algorithm>
#include <random>
#include <chrono>
#include <thread>

using namespace std;
/*
* @class Organism
* Abstract class for basic functionalty for all organisms.
*/
class Organism {
private:
    int numSteps;           // Number of steps that organism has moved.
    int numStepsNoFood;     // Steps since this organism last ate.
    bool hasMoved;          // Indication that this organism has moved this current time step.
    const char character;   // Symbol that disguishes "Bird" from "Worm" (Prey from Predator).

public:
    Organism(char ch);      // Constructor.
    virtual ~Organism();    // Destructor.

    // move() attempts to move the organism to an adjacent empty space.
    void move(vector<vector<Organism*> >& grid, int row, int col, default_random_engine& rng);

    // moveToEat() attempts to have the organism eat (move to adjacent cell containing prey), if unable, calls move().
    void moveToEat(vector<vector<Organism*> >& grid, int row, int col, default_random_engine& rng);

    // findValidMove() attempts to find a valid move based on whether the organism
    // is looking to eat or not.
    bool findValidMove(vector<vector<Organism*> >& grid, int row, int col, int& newRow, int& newCol, default_random_engine& rng, bool lookingToEat);

    char getCharacter() const;      // Get character symbol.
    bool getHasMoved() const;       // Get hasMoved flag.
    int getNumSteps() const;        // Get number of steps.
    int getNumStepsNoFood() const;  // Get number of steps since last eating.

    void setHasMoved(bool hasMoved); // Set movement flag.

    // starve() deletes the organism from the grid.
    void starve(vector<vector<Organism*> >& grid, int row, int col);

    // breed() is abstract to handle how an organism breeds. Must be implemented for specific organism.
    virtual void breed(vector<vector<Organism*> >& grid, int row, int col, default_random_engine& rng) = 0;
};

class Worm : public Organism {
public:
    Worm();
    // breed() for Worm calls findValidMove() and spawns a new worm if a blank spot is found.
    void breed(vector<vector<Organism*> >& grid, int row, int col, default_random_engine& rng) override;
};

class Bird : public Organism {
public:
    Bird();
    // breed() for Bird calls findValidMove() and spawns a new bird if a blank spot is found.
    void breed(vector<vector<Organism*> >& grid, int row, int col, default_random_engine& rng) override;
};

class Simulation {
private:
    default_random_engine rng;          // Random number generator.
    const int gridSize = 20;            // The grid's size.
    vector<vector<Organism*> > grid;    // The 2D grid itself.

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


int main()
{
    Simulation sim;
    sim.generateGrid();
    sim.populateGrid();
    int steps = 0;

    while (steps < 100) {
        sim.displayGrid();
        sim.displayStats();
        sim.timeStep();
        steps++;
        this_thread::sleep_for(chrono::milliseconds(600));
    }

    return 0;
}

// ORGANISM CLASS IMPLEMENTATIONS

Organism::Organism(char ch) : character(ch), hasMoved(false), numSteps(0), numStepsNoFood(0) {}

Organism::~Organism() {}

void Organism::move(vector<vector<Organism*> >& grid, int row, int col, default_random_engine& rng) {
    bool lookingToEat = false;
    numSteps++;
    int newRow;
    int newCol;
    if (findValidMove(grid, row, col, newRow, newCol, rng, lookingToEat)) {
        grid[newRow][newCol] = grid[row][col];
        grid[row][col] = nullptr;
        grid[newRow][newCol]->setHasMoved(true);
    }
}

void Organism::moveToEat(vector<vector<Organism*> >& grid, int row, int col, default_random_engine& rng) {
    bool lookingToEat = true;
    int newRow;
    int newCol;
    if (findValidMove(grid, row, col, newRow, newCol, rng, lookingToEat)) {
        return;
    }
    numStepsNoFood++;
    move(grid, row, col, rng);
}

bool Organism::findValidMove(vector<vector<Organism*> >& grid, int row, int col, int& newRow, int& newCol, default_random_engine& rng, bool lookingToEat) {
    bool doAction = false;
    vector<int> direction;
    direction.push_back(1);
    direction.push_back(2);
    direction.push_back(3);
    direction.push_back(4);
    shuffle(direction.begin(), direction.end(), rng);

    for (int i = 0; i < 4; i++) {
        newRow = row;
        newCol = col;
        switch (direction[i]) {
            case 1: newRow--; 
            break;
            case 2: newRow++; 
            break;
            case 3: newCol++; 
            break;
            case 4: newCol--; 
            break;
        }
        if (newRow >= 0 && newRow < grid.size() && newCol >= 0 && newCol < grid[0].size()) {
            if (!lookingToEat) { // If not looking to eat...
                if (grid[newRow][newCol] == nullptr) {
                    doAction = true;
                    return doAction;
                }
            } else {
                Organism* target = grid[newRow][newCol];
                if (target != nullptr && target->getCharacter() == 'o') {
                    doAction = true;
                    numSteps++;
                    numStepsNoFood = 0;
                    delete target;
                    grid[newRow][newCol] = grid[row][col];
                    grid[row][col] = nullptr;
                    grid[newRow][newCol]->setHasMoved(true);
                    return doAction;
                }
            }
        }
    }
    return doAction;
}

char Organism::getCharacter() const {
    return character;
}

bool Organism::getHasMoved() const {
    return hasMoved;
}

int Organism::getNumSteps() const {
    return numSteps;
}

int Organism::getNumStepsNoFood() const {
    return numStepsNoFood;
}

void Organism::setHasMoved(bool hasMovedValue) {
    hasMoved = hasMovedValue;
}

void Organism::starve(vector<vector<Organism*> >& grid, int row, int col) {
    delete grid[row][col];
    grid[row][col] = nullptr;
}

// WORM CLASS IMPLEMENTATIONS

Worm::Worm() : Organism('o') {}

void Worm::breed(vector<vector<Organism*> >& grid, int row, int col, default_random_engine& rng) {
    bool lookingToEat = false;
    int newRow;
    int newCol;
    if (findValidMove(grid, row, col, newRow, newCol, rng, lookingToEat)) {
        grid[newRow][newCol] = new Worm;
    }
}

// BIRD CLASS IMPLEMENTATIONS

Bird::Bird() : Organism('X') {}

void Bird::breed(vector<vector<Organism*> >& grid, int row, int col, default_random_engine& rng) {
    bool lookingToEat = false;
    int newRow;
    int newCol;
    if (findValidMove(grid, row, col, newRow, newCol, rng, lookingToEat)) {
        grid[newRow][newCol] = new Bird;
    }
}

// SIMULATION CLASS IMPLEMENTATIONS

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

