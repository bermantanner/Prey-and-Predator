#include "Worm.h"
#include <vector>

using namespace std;

Worm::Worm() : Organism('o') {}

void Worm::breed(vector<vector<Organism*> >& grid, int row, int col, default_random_engine& rng) {
    bool lookingToEat = false;
    int newRow;
    int newCol;
    if (findValidMove(grid, row, col, newRow, newCol, rng, lookingToEat)) {
        grid[newRow][newCol] = new Worm;
    }
}