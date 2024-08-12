#ifndef SIMULATION_CONFIG_H
#define SIMULATION_CONFIG_H

// SimulationConfig's setters return true if the value was succesfully set.
class SimulationConfig {
public: 
    // gridSize MIN 3, MAX 100
    bool setGridSize(int gridSize);
    // Number of worms <= gridSize^2 (So that number of worms does not exceed number of spaces)
    bool setNumWorms(int numWorms);
    // Number of birds <= (gridSize^2 - numWorms) (So that number of birds does not exceed remaining spots)
    bool setNumBirds(int numBirds);
    // Number of time steps MIN 1, MAX 1000
    bool setNumTimeSteps(int numTimeSteps);
    // Time between each time step (ms) MIN 50, MAX 2000
    bool setTickSpeed(int tickSpeed);

    // The time step interval in which worms breed, DEFAULT 3, MIN 1
    bool setWormBreedTimeStep(int wormBreedTimeStep);
    // The time step interval in which birds breed, DEFAULT 8, MIN 1
    bool setBirdBreedTimeStep(int birdBreedTimeStep);
    // The time step interval in which birds starve, DEFAULT 3, MIN 1
    bool setBirdStarveTimeStep(int birdStarveTimeStep);

    int getGridSize() const;
    int getNumWorms() const;
    int getNumBirds() const;
    int getNumTimeSteps() const;
    int getTickSpeed() const;
    int getWormBreedTimeStep() const;
    int getBirdBreedTimeStep() const;
    int getBirdStarveTimeStep() const;

    int calculateDefaultWorms(); // DEFAULT = (1/4 * gridSize^2)
    int calculateDefaultBirds(); // DEFAULT = (1/10 * numWorms)

private:
                                // --Parameter Brainstorm--
    int gridSize = 20;          // min 3 max ? 
    int numWorms = 100;         // min 0 max (gridSize)
    int numBirds = 10;          // min 0 max (gridSize - numWorms)
    int numTimeSteps = 100;     // min 1 max ?
    int tickSpeed = 600;        // min 50 max 2000
    
                                // "advanced"
    int wormBreedTimeStep = 3;  // default 3
    int birdBreedTimeStep = 8;  // default 8
    int birdStarveTimeStep = 3; // default 3

};

#endif