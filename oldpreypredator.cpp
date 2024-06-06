#include <iostream>
#include <vector>
#include <ctime>
#include <algorithm>
#include <random>
#include <chrono>
#include <thread>
using namespace std;

class Organism {
    private:
        int numSteps;
        int numStepsNoFood;

    public:
        virtual ~Organism() {}
        bool hasMoved; //I'm choosing to make this public because it's going to perform changes hundreds of times.
        const char character; 
        Organism(char ch) : character(ch), hasMoved(false), numSteps(0) {}
        void move(vector<vector<Organism*> >& grid, int row, int col, default_random_engine& rng) {
            numSteps++;
            vector<int> direction;
            direction.push_back(1);
            direction.push_back(2);
            direction.push_back(3);
            direction.push_back(4);
            shuffle(direction.begin(), direction.end(), rng); //Creating a shuffled deck of directions

            for (int i = 0; i < 3; i++) {
                int newRow = row;
                int newCol = col;
                switch(direction[i]) {
                    case 1:
                        newRow--;
                        break;
                    case 2:
                        newRow++;
                        break;
                    case 3:
                        newCol++;
                        break;
                    case 4:
                        newCol--;
                        break;
                }
                //Checking if newRow/newCol are in bounds and not occupied
                if (newRow >= 0 && newRow < grid.size() && newCol >= 0 && newCol < grid[0].size() && grid[newRow][newCol] == nullptr) {
                    grid[newRow][newCol] = grid[row][col];
                    grid[row][col] = nullptr;
                    grid[newRow][newCol]->hasMoved = true;
                    return;
                }
            }
        }
        void moveSpecial(vector<vector<Organism*> >& grid, int row, int col, default_random_engine& rng) {
            vector<int> direction;
            direction.push_back(1);
            direction.push_back(2);
            direction.push_back(3);
            direction.push_back(4);
            shuffle(direction.begin(), direction.end(), rng); //Creating a shuffled deck of directions

            for (int i = 0; i < 4; i++) {
                int newRow = row;
                int newCol = col;
                switch (direction[i]) {
                    case 1:
                        newRow--;
                        break;
                    case 2:
                        newRow++;
                        break;
                    case 3:
                        newCol++;
                        break;
                    case 4:
                        newCol--;
                        break;
                }
                // Check if newRow/newCol are in bounds
                if (newRow >= 0 && newRow < grid.size() && newCol >= 0 && newCol < grid[0].size()) {
                    Organism* target = grid[newRow][newCol];
                    if (target != nullptr && target->character == 'o') {
                        numSteps++;
                        numStepsNoFood = 0;
                        // if worm is found, eat.
                        delete target; //eating worm
                        grid[newRow][newCol] = grid[row][col]; //moving to worm spot
                        grid[row][col] = nullptr; //removing old slot
                        grid[newRow][newCol]->hasMoved = true; //marking as moved.
                        return;
                    }
                }
            }

            // if no worms are found the bird will move normally. this is super cool you can call the base class function
            numStepsNoFood++;
            Organism::move(grid, row, col, rng);
        }
        int getNumSteps() {
            return numSteps;
        }
        int getNumStepsNoFood() {
            return numStepsNoFood;
        }
        void starve(vector<vector<Organism*> >& grid, int row, int col) {
            delete grid[row][col];
            grid[row][col] = nullptr;
        }
        virtual void breed(vector<vector<Organism*> >& grid, int row, int col, default_random_engine& rng) = 0;
};

class Worm : public Organism {
    private:
        
    public:
        Worm() : Organism('o') {}
        void breed(vector<vector<Organism*> >& grid, int row, int col, default_random_engine& rng) override{
        vector<int> direction;
        direction.push_back(1);
        direction.push_back(2);
        direction.push_back(3);
        direction.push_back(4);
        shuffle(direction.begin(), direction.end(), rng); //Creating a shuffled deck of directions

        for (int i = 0; i < 3; i++) {
            int newRow = row;
            int newCol = col;
            switch(direction[i]) {
                case 1:
                    newRow--;
                    break;
                case 2:
                    newRow++;
                    break;
                case 3:
                    newCol++;
                    break;
                case 4:
                    newCol--;
                    break;
            }
            //Checking if newRow/newCol are in bounds and not occupied
            if (newRow >= 0 && newRow < grid.size() && newCol >= 0 && newCol < grid[0].size() && grid[newRow][newCol] == nullptr) {
                grid[newRow][newCol] = new Worm;
                return;
            }
        }
    }
};

class Bird : public Organism {
    private:
        
    public:
        Bird() : Organism('X') {}
        void breed(vector<vector<Organism*> >& grid, int row, int col, default_random_engine& rng) override{
        vector<int> direction;
        direction.push_back(1);
        direction.push_back(2);
        direction.push_back(3);
        direction.push_back(4);
        shuffle(direction.begin(), direction.end(), rng); //Creating a shuffled deck of directions

        for (int i = 0; i < 3; i++) {
            int newRow = row;
            int newCol = col;
            switch(direction[i]) {
                case 1:
                    newRow--;
                    break;
                case 2:
                    newRow++;
                    break;
                case 3:
                    newCol++;
                    break;
                case 4:
                    newCol--;
                    break;
            }
                //Checking if newRow/newCol are in bounds and not occupied
            if (newRow >= 0 && newRow < grid.size() && newCol >= 0 && newCol < grid[0].size() && grid[newRow][newCol] == nullptr) {
                grid[newRow][newCol] = new Bird;
                return;
                }
            }
    }

};

class Simulation {
    private:
    default_random_engine rng;

    public:
    const int gridSize = 20;
    vector<vector<Organism*> > grid;
    void generateGrid() {
        grid.resize(gridSize, vector<Organism*>(gridSize, nullptr));
    }
    void displayGrid() {
        for (int row = 0; row < gridSize; row++) {
            for (int col = 0; col < gridSize; col++) {
                if (grid[row][col] == nullptr) {
                    cout << '-';
                } 
                else {
                    cout << grid[row][col]->character;
                }
                cout << ' ';
            }
            cout << endl;
        }
    }
    void populateGrid() {
        srand(static_cast<unsigned>(time(nullptr)));
        int numWorms = 100;
        int numBirds = 5;
        int wormsAdded = 0;
        int birdsAdded = 0;

        //spawning worms.
        while (wormsAdded < numWorms) {
            int row = rand() % gridSize;
            int col = rand() % gridSize;
            if (grid[row][col] == nullptr) {
                grid[row][col] = new Worm;
                wormsAdded++;
            }
        }
        //spawning birds.
        while (birdsAdded < numBirds) {
            int row = rand() % gridSize;
            int col = rand() % gridSize;
            if (grid[row][col] == nullptr) {
                grid[row][col] = new Bird;
                birdsAdded++;
            }
        }
    }
    void timeStep() {
        //changing all the "hasMoved"'s to false
        for (int row = 0; row < grid.size(); row++) {
            for (int col = 0; col < grid[0].size(); col++) {
                if (grid[row][col] != nullptr) {
                    grid[row][col]->hasMoved = false;
                }
            }
        }

        //performing edited move function on birds but first checking if they should starve
        for (int row = 0; row < grid.size(); row++) {
            for (int col = 0; col < grid[0].size(); col++) {
                Organism* currentOrganism = grid[row][col];
                if (currentOrganism != nullptr && grid[row][col]->character == 'X' && grid[row][col]->hasMoved == false) { 
                    if (currentOrganism->getNumStepsNoFood() >= 3) {
                        currentOrganism->starve(grid, row, col);
                    }
                    else {
                        grid[row][col]->moveSpecial(grid, row, col, rng);
                    }
                }
            } 
        }
        
        //moving the worms
        for (int row = 0; row < grid.size(); row++) {
            for (int col = 0; col < grid[0].size(); col++) {
                Organism* currentOrganism = grid[row][col];
                if (currentOrganism != nullptr && grid[row][col]->character == 'o' && grid[row][col]->hasMoved == false) { 
                    grid[row][col]->move(grid, row, col, rng);
                }
            } 
        }

        //breeding worms
        for (int row = 0; row < grid.size(); row++) {
            for (int col = 0; col < grid[0].size(); col++) {
                Organism* currentOrganism = grid[row][col];
                if (currentOrganism != nullptr && grid[row][col]->character == 'o') { 
                    if (currentOrganism->getNumSteps() % 3 == 0 && currentOrganism->getNumSteps() != 0) {
                    grid[row][col]->breed(grid, row, col, rng);
                    }
                }
            } 
        }
        //breeding birds
        for (int row = 0; row < grid.size(); row++) {
            for (int col = 0; col < grid[0].size(); col++) {
                Organism* currentOrganism = grid[row][col];
                if (currentOrganism != nullptr && grid[row][col]->character == 'X') { 
                    if (currentOrganism->getNumSteps() % 8 == 0 && currentOrganism->getNumSteps() != 0) {
                    grid[row][col]->breed(grid, row, col, rng);
                    }
                }
            } 
        }
    }
    void displayStats() {
    int wormCount = 0;
    int birdCount = 0;

    for (int row = 0; row < gridSize; ++row) {
        for (int col = 0; col < gridSize; ++col) {
            Organism* currentOrganism = grid[row][col];
            if (currentOrganism != nullptr) {
                if (currentOrganism->character == 'o') {
                    wormCount++;
                } else if (currentOrganism->character == 'X') {
                    birdCount++;
                }
            }
        }
    }

    std::cout << "Number of Worms: " << wormCount << std::endl;
    std::cout << "Number of Birds: " << birdCount << std::endl;
    }
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
        this_thread::sleep_for(chrono::milliseconds(300));
    }

    return 0;
}
