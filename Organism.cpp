#include "Organism.h"
#include <vector>
#include <random>

using namespace std;

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