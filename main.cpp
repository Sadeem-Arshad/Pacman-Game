


#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>
#include "maze.h"
#include "character.h"
#include "pacman.h"
#include "ghost.h"
#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>

using namespace std;
using namespace sf;

int main()
{
    // Initialize random seed
    srand(static_cast<unsigned int>(time(nullptr)));

    // Create the window
    RenderWindow window(VideoMode({ 644, 700 }), "PacMan");

    // Set frame rate limit
    window.setFramerateLimit(60);

    // Create the maze
    Maze maze;

    // Create Pacman
    Pacman pacman(&maze);

    // Create Ghosts with different strategies
    Ghost redGhost(&maze, &pacman, Ghost::RED);
    Ghost pinkGhost(&maze, &pacman, Ghost::PINK);
    Ghost blueGhost(&maze, &pacman, Ghost::BLUE);
    Ghost orangeGhost(&maze, &pacman, Ghost::ORANGE);

    // Assign strategies
    redGhost.setStrategy(new DirectPursuitStrategy());    // Blinky - Direct chase
    pinkGhost.setStrategy(new AmbushStrategy());          // Pinky - Ambush ahead
    blueGhost.setStrategy(new PatrolStrategy());          // Inky - Patrol/chase combo
    orangeGhost.setStrategy(new RandomStrategy());        // Clyde - Random movement

    // Store all ghosts in a vector for easy updating and drawing
    vector<Ghost*> ghosts = { &redGhost, &pinkGhost, &blueGhost, &orangeGhost };

    // Initialize ghosts - ensure they are all set to not leave initially
    cout << "Initializing ghosts..." << endl;
    for (auto ghost : ghosts) {
        ghost->reset();  // Makes sure positions are reset
        ghost->setCanLeave(false);
    }

    // Clock for delta time
    Clock clock;

    // Game timer for ghost release
    int gameTimer = 0;

    // Flag to track if game is active
    bool gameActive = true;


    // Add this variable near the beginning of the main function, 
// after other variable declarations:
    bool wasPowerMode = false;


    // Main game loop
    while (window.isOpen())
    {
        // Calculate delta time
        float deltaTime = clock.restart().asSeconds();

        // Increment game timer (used to release ghosts)
        gameTimer++;

        // Handle events
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();

            if (event.type == Event::KeyPressed)
            {
                // Close window with Escape key
                if (Keyboard::isKeyPressed(Keyboard::Key::Escape))
                    window.close();

                // Reset game with R key
                if (Keyboard::isKeyPressed(Keyboard::Key::R))
                {
                    maze.redrawDots();
                    maze.setScore(0);
                    pacman.reset();

                    // Reset all ghosts
                    for (auto ghost : ghosts) {
                        ghost->reset();
                        ghost->setCanLeave(false);
                    }

                    gameTimer = 0;
                    gameActive = true;
                }

                // Test key: Make ghosts frightened with F key
                if (Keyboard::isKeyPressed(Keyboard::Key::F))
                {
                    for (auto ghost : ghosts) {
                        ghost->setState(Ghost::FRIGHTENED, 300); // 5 seconds at 60 FPS
                    }
                }

                // Test key: Release all ghosts with L key
                if (Keyboard::isKeyPressed(Keyboard::Key::L))
                {
                    for (auto ghost : ghosts) {
                        ghost->setCanLeave(true);
                    }
                }
            }
        }

        // Release ghosts based on timer
        if (gameActive) {
            // Release red ghost after 1 second (60 frames at 60fps)
            if (gameTimer == 60) {
                redGhost.setCanLeave(true);
                cout << "Red ghost released" << endl;
            }
            // Release pink ghost after 3 seconds
            else if (gameTimer == 180) {
                pinkGhost.setCanLeave(true);
                cout << "Pink ghost released" << endl;
            }
            // Release blue ghost after 5 seconds
            else if (gameTimer == 300) {
                blueGhost.setCanLeave(true);
                cout << "Blue ghost released" << endl;
            }
            // Release orange ghost after 7 seconds
            else if (gameTimer == 420) {
                orangeGhost.setCanLeave(true);
                cout << "Orange ghost released" << endl;
            }
        }

        // Handle Pacman input and update if game is active
        if (gameActive) {
            pacman.handleInput();
            pacman.update(deltaTime);


            // And add these lines after pacman.update(deltaTime); in the game loop:
 // Check if Pacman just ate a power pellet
            if (pacman.isPowerMode() && !wasPowerMode) {
                // Pacman just entered power mode, set ghosts to frightened
                for (auto ghost : ghosts) {
                    ghost->setState(Ghost::FRIGHTENED, 300); // 5 seconds at 60 FPS
                }
            }
            wasPowerMode = pacman.isPowerMode();


            // Update all ghosts
            for (auto ghost : ghosts) {
                ghost->update(deltaTime);

                // Debug output for ghost states (every 120 frames)
                if (gameTimer % 120 == 0) {
                    cout << "Ghost state: " << ghost->getGhostName()
                        << " at (" << ghost->getX() << "," << ghost->getY()
                        << "), Can leave: " << (ghost->canLeave() ? "YES" : "NO")
                        << ", Has left house: " << (ghost->hasLeftGhostHouse ? "YES" : "NO")
                        << ", In ghost house: " << (ghost->isInGhostHouse() ? "YES" : "NO")
                        << ", Direction: " << ghost->getDirection() << endl;
                }

                // Check for collision with Pacman only if ghost can leave
                if (ghost->canLeave() && ghost->checkCollision(pacman.getX(), pacman.getY())) {
                    if (ghost->isFrightened()) {
                        // Ghost is frightened - Pacman eats ghost
                        pacman.eatGhost();
                        ghost->getEaten();
                    }
                    else if (!ghost->isEaten()) {
                        // Ghost is normal - Pacman loses life
                        pacman.loseLife();

                        // Reset all ghosts to their starting positions
                        for (auto g : ghosts) {
                            g->reset();
                            g->setCanLeave(false);
                        }

                        // Reset ghost release timer
                        gameTimer = 0;

                        // Check if game over
                        if (pacman.getLives() <= 0) {
                            gameActive = false;
                        }

                        break;
                    }
                }
            }
        }

        // Clear the window
        window.clear(Color::Black);

        // Draw the maze
        maze.draw(window);

        // Draw Pacman
        pacman.draw(window);

        // Draw all ghosts
        for (auto ghost : ghosts) {
            ghost->draw(window);
        }

        // Display everything
        window.display();
    }

    return 0;
}