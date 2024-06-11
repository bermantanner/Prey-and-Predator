#ifndef ORGANISM_H
#define ORGANISM_H
#include <vector>
#include <random>

using namespace std;

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

#endif