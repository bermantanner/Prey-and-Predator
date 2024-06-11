#ifndef WORM_H
#define WORM_H
#include "Organism.h"
#include <vector>

using namespace std;

class Worm : public Organism {
public:
    Worm();
    // breed() for Worm calls findValidMove() and spawns a new worm if a blank spot is found.
    void breed(vector<vector<Organism*> >& grid, int row, int col, default_random_engine& rng) override;
};

#endif