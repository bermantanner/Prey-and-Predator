#ifndef BIRD_H
#define BIRD_H
#include "Organism.h"

using namespace std;

class Bird : public Organism {
public:
    Bird();
    // breed() for Bird calls findValidMove() and spawns a new bird if a blank spot is found.
    void breed(vector<vector<Organism*> >& grid, int row, int col, default_random_engine& rng) override;
};

#endif