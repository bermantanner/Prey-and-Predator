#include "SFML/Graphics.hpp"

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
    int gridSize;
    int tickSpeed;
    cout << "Enter size of grid (n x n): " << endl;
    cin >> gridSize;
    cout << "Enter tick speed (100 is faster, 500 is slower):" << endl;
    cin >> tickSpeed;
    const int windowSize = 1000;
   
    // create the SFML window
    sf::RenderWindow window(sf::VideoMode(windowSize, windowSize), "Prey and Predator");

    // initialize the simulation
    Simulation sim(gridSize, &window, windowSize);

     // clock for controlling tick speed
    sf::Clock clock;

    // main loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // call timeStep at regular intervals
        if (clock.getElapsedTime().asMilliseconds() > tickSpeed) {
            sim.timeStep();
            clock.restart();
        }

        // Render the grid
        sim.render();
    }

    return 0;
}

