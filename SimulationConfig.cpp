#include "SimulationConfig.h"

bool SimulationConfig::setGridSize(int gridSize) {
    if (gridSize > 3 && gridSize <= 100) {
        this->gridSize = gridSize;
        return true; // Success, valid input.
    }
    return false; // Failed, invalid input.
}

bool SimulationConfig::setNumWorms(int numWorms) {
    if (numWorms >= 0 && numWorms <= (gridSize * gridSize)) {
        this->numWorms = numWorms;
        return true;
    }
    return false;
}

bool SimulationConfig::setNumBirds(int numBirds) {
    if (numBirds >= 0 && numBirds <= (gridSize * gridSize - numWorms)) {
        this->numBirds = numBirds;
        return true;
    }
    return false;
}

bool SimulationConfig::setNumTimeSteps(int numTimeSteps) {
    if (numTimeSteps >= 1 && numTimeSteps <= 1000) {
        this->numTimeSteps = numTimeSteps;
        return true;
    }
    return false;
}

bool SimulationConfig::setTickSpeed(int tickSpeed) {
    if (tickSpeed >= 50 && tickSpeed <= 2000) {
        this->tickSpeed = tickSpeed;
        return true;
    }
    return false;
}

bool SimulationConfig::setWormBreedTimeStep(int wormBreedTimeStep) {
    if (wormBreedTimeStep >= 1) {
        this->wormBreedTimeStep = wormBreedTimeStep;
        return true;
    }
    return false;
}

bool SimulationConfig::setBirdBreedTimeStep(int birdBreedTimeStep) {
    if (birdBreedTimeStep >= 1) {
        this->birdBreedTimeStep = birdBreedTimeStep;
        return true;
    }
    return false;
}

bool SimulationConfig::setBirdStarveTimeStep(int birdStarveTimeStep) {
    if (birdStarveTimeStep >= 1) {
        this->birdStarveTimeStep = birdStarveTimeStep;
        return true;
    }
    return false;
}

int SimulationConfig::getGridSize() const {
    return gridSize;
}

int SimulationConfig::getNumWorms() const {
    return numWorms;
}

int SimulationConfig::getNumBirds() const {
    return numBirds;
}

int SimulationConfig::getNumTimeSteps() const {
    return numTimeSteps;
}

int SimulationConfig::getTickSpeed() const {
    return tickSpeed;
}

int SimulationConfig::getWormBreedTimeStep() const {
    return wormBreedTimeStep;
}

int SimulationConfig::getBirdBreedTimeStep() const {
    return birdBreedTimeStep;
}

int SimulationConfig::getBirdStarveTimeStep() const {
    return birdStarveTimeStep;
}

int SimulationConfig::calculateDefaultWorms() {
    return (0.25 * (gridSize * gridSize));
}

int SimulationConfig::calculateDefaultBirds() {
    return (0.10 * numWorms);
}