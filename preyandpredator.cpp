#include <iostream>
#include <vector>
#include <ctime>
#include <algorithm>
#include <random>
#include <chrono>
#include <thread>
#include "Organism.h"
#include "Worm.h"
#include "Bird.h"
#include "Simulation.h"

using namespace std;

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

