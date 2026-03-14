#pragma once

#ifndef PACMAN_REFERENCE_H
#define PACMAN_REFERENCE_H

// This is a reference implementation for getting Pacman's position and direction
// This code should be integrated into your project structure

class PacmanReference {
public:
    // Constructor - pass the actual Pacman object
    PacmanReference(Pacman* pacmanPtr) : pacman(pacmanPtr) {}

    // Get Pacman's current X grid position
    int getX() const {
        if (pacman) {
            return pacman->getX();
        }
        return 0;
    }

    // Get Pacman's current Y grid position
    int getY() const {
        if (pacman) {
            return pacman->getY();
        }
        return 0;
    }

    // Get Pacman's current direction
    Character::Direction getDirection() const {
        if (pacman) {
            return pacman->getCurrentDirection();
        }
        return Character::NONE;
    }

private:
    Pacman* pacman;
};

// Note: You would need to modify the Pacman class to expose its current direction
// Add this method to the Pacman class:

/*
Character::Direction getCurrentDirection() const {
    return currentDirection;
}
*/

#endif // PACMAN_REFERENCE_H