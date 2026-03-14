//#pragma once
//
//
//
//
//#pragma once
//
//#ifndef PACMAN_H
//#define PACMAN_H
//
//#include <SFML/Graphics.hpp>
//#include "maze.h"
//#include <iostream>
//#include <string>
//#include <cmath>
//
//#include <vector>
//#define M_PI 3.14159265358979323846 // Define M_PI if not already defined
//
//
//using namespace std;
//using namespace sf;
//
//class Pacman {
//public:
//    // Constants
//    static const float DEFAULT_SPEED;       // Base movement speed
//    static const float ANIMATION_INTERVAL;  // Time between animation frames
//    static const int ANIMATION_FRAMES = 4;  // Number of animation frames
//
//    // Directions
//    enum Direction {
//        NONE = 0,
//        RIGHT = 1,
//        LEFT = 2,
//        UP = 3,
//        DOWN = 4
//    };
//
//    // Constructor
//    Pacman(Maze* mazeRef) {
//        cout << "Pacman class OK" << endl;
//        maze = mazeRef;
//
//        // Find the 'c' character in the maze pattern to set starting position
//        findStartPosition();
//
//        // Setup Pacman graphics
//        setupGraphics();
//
//        // Set initial position
//        updatePosition();
//
//        // Initialize animation properties
//        animationFrame = 0;
//        animationTimer = 0.0f;
//        animationDirection = 1; // 1 = opening, -1 = closing
//
//        // Initialize movement properties
//        currentDirection = NONE;
//        nextDirection = NONE;
//        speed = DEFAULT_SPEED;
//    }
//
//    // Update pacman state (called each frame)
//    void update(float deltaTime) {
//        // Animation update
//        updateAnimation(deltaTime);
//
//        // Movement update
//        updateMovement(deltaTime);
//
//        // Check if we consumed a dot
//        checkDotConsumption();
//    }
//
//    // Draw pacman to the window
//    void draw(RenderWindow& window) {
//        // Draw the pacman shape
//        window.draw(pacmanShape);
//    }
//
//    // Handle keyboard input
//    void handleInput() {
//        // Check keyboard for direction changes
//        if (Keyboard::isKeyPressed(Keyboard::Right)) {
//            nextDirection = RIGHT;
//        }
//        else if (Keyboard::isKeyPressed(Keyboard::Left)) {
//            nextDirection = LEFT;
//        }
//        else if (Keyboard::isKeyPressed(Keyboard::Up)) {
//            nextDirection = UP;
//        }
//        else if (Keyboard::isKeyPressed(Keyboard::Down)) {
//            nextDirection = DOWN;
//        }
//    }
//
//    // Get current score
//    int getScore() const {
//        return score;
//    }
//
//    // Reset Pacman to starting position
//    void reset() {
//        findStartPosition();
//        currentDirection = NONE;
//        nextDirection = NONE;
//        offsetX = 0.0f;
//        offsetY = 0.0f;
//        updatePosition();
//        score = 0;
//    }
//
//private:
//    // Reference to maze
//    Maze* maze;
//
//    // Grid position (in maze cells)
//    int gridX;
//    int gridY;
//
//    // Position offset within grid cell (for smooth movement)
//    float offsetX = 0.0f;
//    float offsetY = 0.0f;
//
//    // Movement properties
//    Direction currentDirection;
//    Direction nextDirection;
//    float speed;
//
//    // Animation properties
//    int animationFrame;
//    float animationTimer;
//    int animationDirection; // 1 = opening, -1 = closing
//
//    // Visual representation
//    CircleShape pacmanShape;
//
//    // Gameplay state
//    int score = 0;
//
//    // Setup Pacman graphics
//    void setupGraphics() {
//        // Create the pacman shape as a circle
//        float radius = Maze::cellSize / 2.0f - 2.0f;
//        pacmanShape.setRadius(radius);
//        pacmanShape.setFillColor(Color::Yellow);
//        pacmanShape.setOrigin(radius, radius);
//
//        // Use more points for smoother circle
//        pacmanShape.setPointCount(30);
//
//        // Set initial points for the circle (full circle)
//        updateMouthShape(0);
//    }
//
//    // Update the mouth shape based on animation frame
//    void updateMouthShape(int frame) {
//        // Get the circle radius and point count
//        float radius = pacmanShape.getRadius();
//        int pointCount = pacmanShape.getPointCount();
//
//        // The animation frames (0 = closed, ANIMATION_FRAMES-1 = fully open)
//        // These values create a more authentic Pacman look
//        float mouthAngle;
//
//        if (frame == 0) {
//            // Almost closed (just a small triangular cutout)
//            mouthAngle = 10.0f;
//        }
//        else if (frame == ANIMATION_FRAMES - 1) {
//            // Fully open (larger triangular cutout)
//            mouthAngle = 55.0f;
//        }
//        else {
//            // Intermediate frames
//            float percentage = static_cast<float>(frame) / (ANIMATION_FRAMES - 1);
//            mouthAngle = 10.0f + percentage * 45.0f;
//        }
//
//        // Determine direction-based rotation
//        float rotation = 0.0f;
//        switch (currentDirection) {
//        case LEFT:  rotation = 180.0f; break;
//        case UP:    rotation = 270.0f; break;
//        case DOWN:  rotation = 90.0f; break;
//        default:    rotation = 0.0f; break; // RIGHT or NONE
//        }
//
//        // Calculate the start and end angles for the mouth cutout
//        float startAngle = rotation - mouthAngle;
//        float endAngle = rotation + mouthAngle;
//
//        // Convert to radians for calculations
//        float startRad = startAngle * M_PI / 180.0f;
//        float endRad = endAngle * M_PI / 180.0f;
//
//        // Update the shape points
//        for (int i = 0; i < pointCount; i++) {
//            // Calculate angle for this point
//            float angle = 2.0f * M_PI * i / pointCount;
//
//            // Check if this point is in the mouth area
//            bool isInMouth = false;
//            if (startAngle <= endAngle) {
//                float angleDeg = angle * 180.0f / M_PI;
//
//                isInMouth = (angleDeg >= startAngle && angleDeg <= endAngle);
//            }
//            else {
//                // Handle wrap-around case (e.g. 350° to 10°)
//                float angleDeg = angle * 180.0f / M_PI;
//                isInMouth = (angleDeg >= startAngle || angleDeg <= endAngle);
//            }
//
//            // Set the point position
//            if (!isInMouth) {
//                // Regular circle point
//                float x = cos(angle) * radius;
//                float y = sin(angle) * radius;
//                pacmanShape.setPoint(i, Vector2f(x, y));
//            }
//            else {
//                // Mouth point - set to center to create the triangular cutout
//                pacmanShape.setPoint(i, Vector2f(0, 0));
//            }
//        }
//    }
//
//    // Find Pacman's starting position based on 'c' in the maze pattern
//    void findStartPosition() {
//        // Look for 'c' character in maze pattern
//        for (int y = 0; y < Maze::mazeH; y++) {
//            for (int x = 0; x < Maze::mazeW; x++) {
//                if (maze->getCellAt(x, y) == "c") {
//                    gridX = x;
//                    gridY = y;
//                    return;
//                }
//            }
//        }
//
//        // Fallback if 'c' not found
//        gridX = 11;
//        gridY = 18;
//    }
//
//    // Update position based on grid coordinates
//    void updatePosition() {
//        Vector2f screenPos = maze->gridToScreen(gridX, gridY);
//        pacmanShape.setPosition(screenPos.x + offsetX, screenPos.y + offsetY);
//    }
//
//    // Update animation state
//    void updateAnimation(float deltaTime) {
//        animationTimer += deltaTime;
//
//        if (animationTimer >= ANIMATION_INTERVAL) {
//            animationTimer = 0.0f;
//
//            // Update animation frame
//            animationFrame += animationDirection;
//
//            // Check bounds and change direction if needed
//            if (animationFrame >= ANIMATION_FRAMES - 1) {
//                animationFrame = ANIMATION_FRAMES - 1;
//                animationDirection = -1; // Start closing
//            }
//            else if (animationFrame <= 0) {
//                animationFrame = 0;
//                animationDirection = 1; // Start opening
//            }
//
//            // Update mouth shape based on new frame
//            updateMouthShape(animationFrame);
//        }
//    }
//
//    // Check if a move in the given direction is valid
//    bool canMove(Direction dir) {
//        int nextX = gridX;
//        int nextY = gridY;
//
//        // Calculate the target cell based on direction
//        switch (dir) {
//        case RIGHT: nextX++; break;
//        case LEFT: nextX--; break;
//        case UP: nextY--; break;
//        case DOWN: nextY++; break;
//        default: break;
//        }
//
//        // Check for tunnel wrap-around
//        if (nextX < 0) nextX = Maze::mazeW - 1;
//        if (nextX >= Maze::mazeW) nextX = 0;
//
//        // Check if the target cell is a wall
//        return !maze->isWall(nextX, nextY);
//    }
//
//    // Update pacman's movement
//    void updateMovement(float deltaTime) {
//        // Calculate movement speed for this frame
//        float moveDistance = speed * deltaTime;
//
//        // If we're perfectly aligned with the grid (no offset), check for direction changes
//        if (offsetX == 0.0f && offsetY == 0.0f) {
//            // Try to change direction if requested
//            if (nextDirection != NONE && canMove(nextDirection)) {
//                currentDirection = nextDirection;
//                // Update mouth direction immediately when changing direction
//                updateMouthShape(animationFrame);
//            }
//
//            // If we can't move in the current direction, stop
//            if (currentDirection != NONE && !canMove(currentDirection)) {
//                currentDirection = NONE;
//            }
//        }
//
//        // If we have a direction, move in that direction
//        if (currentDirection != NONE) {
//            switch (currentDirection) {
//            case RIGHT:
//                offsetX += moveDistance;
//                if (offsetX >= Maze::cellSize) {
//                    gridX++;
//                    offsetX = 0;
//                    checkTunnel();
//                }
//                break;
//
//            case LEFT:
//                offsetX -= moveDistance;
//                if (offsetX <= -Maze::cellSize) {
//                    gridX--;
//                    offsetX = 0;
//                    checkTunnel();
//                }
//                break;
//
//            case UP:
//                offsetY -= moveDistance;
//                if (offsetY <= -Maze::cellSize) {
//                    gridY--;
//                    offsetY = 0;
//                }
//                break;
//
//            case DOWN:
//                offsetY += moveDistance;
//                if (offsetY >= Maze::cellSize) {
//                    gridY++;
//                    offsetY = 0;
//                }
//                break;
//
//            default:
//                break;
//            }
//
//            // Update the position
//            updatePosition();
//        }
//    }
//
//    // Check if pacman is in a tunnel and handle warping
//    void checkTunnel() {
//        // Left tunnel (pacman leaves left side)
//        if (gridX < 0) {
//            gridX = Maze::mazeW - 1;
//        }
//        // Right tunnel (pacman leaves right side)
//        else if (gridX >= Maze::mazeW) {
//            gridX = 0;
//        }
//    }
//
//    // Check for dot consumption at current position
//    void checkDotConsumption() {
//        // Only check for dot consumption when perfectly aligned with grid
//        if (offsetX == 0.0f && offsetY == 0.0f && maze->hasDot(gridX, gridY)) {
//            // Remove the dot and update score
//            maze->removeDot(gridX, gridY);
//
//            // Score is updated in the maze's removeDot method
//            score = maze->score;
//        }
//    }
//};
//
//// Define constants
//const float Pacman::DEFAULT_SPEED = 100.0f;      // Pixels per second
//const float Pacman::ANIMATION_INTERVAL = 0.08f;  // Seconds between animation frames (faster animation)
//
//#endif // PACMAN_H
