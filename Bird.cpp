#include "Bird.h"

Bird::Bird() : Organism('X') {}

void Bird::breed(vector<vector<Organism*> >& grid, int row, int col, default_random_engine& rng) {
    bool lookingToEat = false;
    int newRow;
    int newCol;
    if (findValidMove(grid, row, col, newRow, newCol, rng, lookingToEat)) {
        grid[newRow][newCol] = new Bird;
    }
}