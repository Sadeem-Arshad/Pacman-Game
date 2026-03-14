//#pragma once
//
//#ifndef GHOST_STRATEGY_H
//#define GHOST_STRATEGY_H
//
//#include "ghost.h"
//#include "maze.h"
//#include <cstdlib>  // For rand()
//#include <ctime>    // For time()
//#include <queue>    // For priority_queue
//#include <vector>   // For vector
//#include <utility>  // For pair
//#include <cmath>    // For sqrt and pow
//
//using namespace std;
//
//// Base strategy class (already defined in ghost.h, repeated here for reference)
///*
//class GhostStrategy {
//public:
//    virtual ~GhostStrategy() {}
//    virtual void calculateNextMove(Ghost* ghost, Maze* maze, int pacmanX, int pacmanY) = 0;
//};
//*/
//
//// Helper functions for all strategies
//
//// Calculate Manhattan distance between two points
//int getManhattanDistance(int x1, int y1, int x2, int y2) {
//    return abs(x2 - x1) + abs(y2 - y1);
//}
//
//// Calculate Euclidean distance between two points
//float getEuclideanDistance(int x1, int y1, int x2, int y2) {
//    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
//}
//
//// Get best direction to reach a target using simple heuristics
//Direction getBestDirectionToTarget(Ghost* ghost, Maze* maze, int targetX, int targetY) {
//    int ghostX = ghost->getX();
//    int ghostY = ghost->getY();
//
//    // Store possible directions and their distances to target
//    vector<pair<Direction, float>> possibleMoves;
//
//    // Check each direction
//    if (ghost->canMove(Direction::RIGHT)) {
//        float distance = getEuclideanDistance(ghostX + 1, ghostY, targetX, targetY);
//        possibleMoves.push_back(make_pair(Direction::RIGHT, distance));
//    }
//
//    if (ghost->canMove(Direction::LEFT)) {
//        float distance = getEuclideanDistance(ghostX - 1, ghostY, targetX, targetY);
//        possibleMoves.push_back(make_pair(Direction::LEFT, distance));
//    }
//
//    if (ghost->canMove(Direction::UP)) {
//        float distance = getEuclideanDistance(ghostX, ghostY - 1, targetX, targetY);
//        possibleMoves.push_back(make_pair(Direction::UP, distance));
//    }
//
//    if (ghost->canMove(Direction::DOWN)) {
//        float distance = getEuclideanDistance(ghostX, ghostY + 1, targetX, targetY);
//        possibleMoves.push_back(make_pair(Direction::DOWN, distance));
//    }
//
//    // If no moves possible, return NONE
//    if (possibleMoves.empty()) {
//        return Direction::NONE;
//    }
//
//    // Sort by distance (closest first)
//    sort(possibleMoves.begin(), possibleMoves.end(),
//        [](const pair<Direction, float>& a, const pair<Direction, float>& b) {
//            return a.second < b.second;
//        });
//
//    // Return the direction that gets us closest to the target
//    return possibleMoves[0].first;
//}
//
//// Get opposite direction
//Direction getOppositeDirection(Direction dir) {
//    switch (dir) {
//    case Direction::RIGHT: return Direction::LEFT;
//    case Direction::LEFT: return Direction::RIGHT;
//    case Direction::UP: return Direction::DOWN;
//    case Direction::DOWN: return Direction::UP;
//    default: return Direction::NONE;
//    }
//}
//
//// Get random valid direction excluding the opposite of current direction (prevents 180° turns)
//Direction getRandomDirection(Ghost* ghost, Direction currentDir) {
//    vector<Direction> validDirections;
//    Direction oppositeDir = getOppositeDirection(currentDir);
//
//    if (ghost->canMove(Direction::RIGHT) && Direction::RIGHT != oppositeDir) {
//        validDirections.push_back(Direction::RIGHT);
//    }
//    if (ghost->canMove(Direction::LEFT) && Direction::LEFT != oppositeDir) {
//        validDirections.push_back(Direction::LEFT);
//    }
//    if (ghost->canMove(Direction::UP) && Direction::UP != oppositeDir) {
//        validDirections.push_back(Direction::UP);
//    }
//    if (ghost->canMove(Direction::DOWN) && Direction::DOWN != oppositeDir) {
//        validDirections.push_back(Direction::DOWN);
//    }
//
//    // If no valid directions (shouldn't happen in properly designed maze), allow 180° turn
//    if (validDirections.empty()) {
//        if (ghost->canMove(oppositeDir)) {
//            return oppositeDir;
//        }
//        return Direction::NONE;
//    }
//
//    // Return a random valid direction
//    return validDirections[rand() % validDirections.size()];
//}
//
//// Implementation of the Random Strategy (for frightened state)
//class RandomStrategy : public GhostStrategy {
//public:
//    RandomStrategy() {
//        srand(static_cast<unsigned int>(time(nullptr)));
//    }
//
//    void calculateNextMove(Ghost* ghost, Maze* maze, int pacmanX, int pacmanY) override {
//        // Get the current ghost direction (needed to avoid 180° turns)
//        Direction currentDir = static_cast<Direction>(ghost->getDirection());
//
//        // Choose a random valid direction that's not a 180° turn
//        Direction nextDir = getRandomDirection(ghost, currentDir);
//
//        // Set the ghost's next direction
//        ghost->setNextDirection(nextDir);
//    }
//};
//
//// Implementation of the Direct Pursuit Strategy (Blinky - Red Ghost)
//class DirectPursuitStrategy : public GhostStrategy {
//public:
//    void calculateNextMove(Ghost* ghost, Maze* maze, int pacmanX, int pacmanY) override {
//        // If ghost is frightened, use random movement
//        if (ghost->isFrightened()) {
//            RandomStrategy randomStrategy;
//            randomStrategy.calculateNextMove(ghost, maze, pacmanX, pacmanY);
//            return;
//        }
//
//        // If ghost is eaten, head back to ghost house
//        if (ghost->isEaten()) {
//            // Find ghost house coordinates
//            int ghostHouseX = 11; // Default, adjust based on your maze
//            int ghostHouseY = 11; // Default, adjust based on your maze
//
//            // Find exact ghost house position in maze if needed
//            for (int y = 0; y < Maze::mazeH; y++) {
//                for (int x = 0; x < Maze::mazeW; x++) {
//                    if (maze->getCellAt(x, y) == "*") {
//                        ghostHouseX = x;
//                        ghostHouseY = y;
//                        break;
//                    }
//                }
//            }
//
//            // Get best direction to ghost house
//            Direction bestDir = getBestDirectionToTarget(ghost, maze, ghostHouseX, ghostHouseY);
//            ghost->setNextDirection(bestDir);
//            return;
//        }
//
//        // For normal state: directly pursue Pacman (Blinky's behavior)
//        Direction bestDir = getBestDirectionToTarget(ghost, maze, pacmanX, pacmanY);
//        ghost->setNextDirection(bestDir);
//    }
//};
//
//// Implementation of the Ambush Strategy (Pinky - Pink Ghost)
//class AmbushStrategy : public GhostStrategy {
//public:
//    void calculateNextMove(Ghost* ghost, Maze* maze, int pacmanX, int pacmanY) override {
//        // If ghost is frightened, use random movement
//        if (ghost->isFrightened()) {
//            RandomStrategy randomStrategy;
//            randomStrategy.calculateNextMove(ghost, maze, pacmanX, pacmanY);
//            return;
//        }
//
//        // If ghost is eaten, head back to ghost house
//        if (ghost->isEaten()) {
//            // Find ghost house coordinates (same as in DirectPursuitStrategy)
//            int ghostHouseX = 11;
//            int ghostHouseY = 11;
//
//            for (int y = 0; y < Maze::mazeH; y++) {
//                for (int x = 0; x < Maze::mazeW; x++) {
//                    if (maze->getCellAt(x, y) == "*") {
//                        ghostHouseX = x;
//                        ghostHouseY = y;
//                        break;
//                    }
//                }
//            }
//
//            Direction bestDir = getBestDirectionToTarget(ghost, maze, ghostHouseX, ghostHouseY);
//            ghost->setNextDirection(bestDir);
//            return;
//        }
//
//        // For normal state: ambush Pacman by targeting 4 tiles ahead of Pacman's current direction
//        int targetX = pacmanX;
//        int targetY = pacmanY;
//
//        // Determine Pacman's direction and set target 4 tiles ahead
//        Direction pacmanDir = static_cast<Direction>(ghost->getPacmanDirection());
//
//        switch (pacmanDir) {
//        case Direction::RIGHT:
//            targetX += 4;
//            break;
//        case Direction::LEFT:
//            targetX -= 4;
//            break;
//        case Direction::UP:
//            targetY -= 4;
//            break;
//        case Direction::DOWN:
//            targetY += 4;
//            break;
//        default:
//            // If Pacman is not moving, just target Pacman directly
//            break;
//        }
//
//        // Make sure target is within maze bounds
//        targetX = max(0, min(targetX, Maze::mazeW - 1));
//        targetY = max(0, min(targetY, Maze::mazeH - 1));
//
//        // If target is a wall, find the closest non-wall cell
//        while (maze->isWall(targetX, targetY) &&
//            (targetX != pacmanX || targetY != pacmanY)) {
//            // Move target closer to Pacman until it's not a wall
//            if (targetX > pacmanX) targetX--;
//            else if (targetX < pacmanX) targetX++;
//
//            if (targetY > pacmanY) targetY--;
//            else if (targetY < pacmanY) targetY++;
//        }
//
//        // Move toward the target position
//        Direction bestDir = getBestDirectionToTarget(ghost, maze, targetX, targetY);
//        ghost->setNextDirection(bestDir);
//    }
//};
//
//// Implementation of the Flanking Strategy (Inky - Blue Ghost)
//// Inky targets a position that is twice the vector from Blinky to 2 tiles ahead of Pacman
//class FlankingStrategy : public GhostStrategy {
//private:
//    Ghost* blinky; // Reference to Blinky (red ghost)
//
//public:
//    FlankingStrategy(Ghost* blinkyRef) : blinky(blinkyRef) {}
//
//    void calculateNextMove(Ghost* ghost, Maze* maze, int pacmanX, int pacmanY) override {
//        // If ghost is frightened, use random movement
//        if (ghost->isFrightened()) {
//            RandomStrategy randomStrategy;
//            randomStrategy.calculateNextMove(ghost, maze, pacmanX, pacmanY);
//            return;
//        }
//
//        // If ghost is eaten, head back to ghost house
//        if (ghost->isEaten()) {
//            int ghostHouseX = 11;
//            int ghostHouseY = 11;
//
//            for (int y = 0; y < Maze::mazeH; y++) {
//                for (int x = 0; x < Maze::mazeW; x++) {
//                    if (maze->getCellAt(x, y) == "*") {
//                        ghostHouseX = x;
//                        ghostHouseY = y;
//                        break;
//                    }
//                }
//            }
//
//            Direction bestDir = getBestDirectionToTarget(ghost, maze, ghostHouseX, ghostHouseY);
//            ghost->setNextDirection(bestDir);
//            return;
//        }
//
//        // For normal state:
//        // 1. Find position 2 tiles ahead of Pacman
//        int intermediateX = pacmanX;
//        int intermediateY = pacmanY;
//
//        Direction pacmanDir = static_cast<Direction>(ghost->getPacmanDirection());
//
//        switch (pacmanDir) {
//        case Direction::RIGHT:
//            intermediateX += 2;
//            break;
//        case Direction::LEFT:
//            intermediateX -= 2;
//            break;
//        case Direction::UP:
//            intermediateY -= 2;
//            break;
//        case Direction::DOWN:
//            intermediateY += 2;
//            break;
//        default:
//            break;
//        }
//
//        // 2. Calculate vector from Blinky to this intermediate position
//        int blinkyX = blinky->getX();
//        int blinkyY = blinky->getY();
//
//        int vectorX = intermediateX - blinkyX;
//        int vectorY = intermediateY - blinkyY;
//
//        // 3. Double this vector to get the target position
//        int targetX = intermediateX + vectorX;
//        int targetY = intermediateY + vectorY;
//
//        // Make sure target is within maze bounds
//        targetX = max(0, min(targetX, Maze::mazeW - 1));
//        targetY = max(0, min(targetY, Maze::mazeH - 1));
//
//        // If target is a wall, find the closest non-wall cell
//        while (maze->isWall(targetX, targetY) &&
//            (targetX != intermediateX || targetY != intermediateY)) {
//            if (targetX > intermediateX) targetX--;
//            else if (targetX < intermediateX) targetX++;
//
//            if (targetY > intermediateY) targetY--;
//            else if (targetY < intermediateY) targetY++;
//        }
//
//        // Move toward the target position
//        Direction bestDir = getBestDirectionToTarget(ghost, maze, targetX, targetY);
//        ghost->setNextDirection(bestDir);
//    }
//};
//
//// Implementation of the Patrol Strategy (Clyde - Orange Ghost)
//// Clyde targets Pacman directly when far away, but retreats to a corner when close
//class PatrolStrategy : public GhostStrategy {
//private:
//    int cornerX, cornerY; // Patrol corner coordinates
//
//public:
//    PatrolStrategy() {
//        // Default to bottom-left corner, can be adjusted
//        cornerX = 1;
//        cornerY = Maze::mazeH - 2;
//    }
//
//    void calculateNextMove(Ghost* ghost, Maze* maze, int pacmanX, int pacmanY) override {
//        // If ghost is frightened, use random movement
//        if (ghost->isFrightened()) {
//            RandomStrategy randomStrategy;
//            randomStrategy.calculateNextMove(ghost, maze, pacmanX, pacmanY);
//            return;
//        }
//
//        // If ghost is eaten, head back to ghost house
//        if (ghost->isEaten()) {
//            int ghostHouseX = 11;
//            int ghostHouseY = 11;
//
//            for (int y = 0; y < Maze::mazeH; y++) {
//                for (int x = 0; x < Maze::mazeW; x++) {
//                    if (maze->getCellAt(x, y) == "*") {
//                        ghostHouseX = x;
//                        ghostHouseY = y;
//                        break;
//                    }
//                }
//            }
//
//            Direction bestDir = getBestDirectionToTarget(ghost, maze, ghostHouseX, ghostHouseY);
//            ghost->setNextDirection(bestDir);
//            return;
//        }
//
//        // For normal state: target Pacman directly if far away (> 8 tiles),
//        // target corner if close (≤ 8 tiles)
//        int ghostX = ghost->getX();
//        int ghostY = ghost->getY();
//        float distance = getEuclideanDistance(ghostX, ghostY, pacmanX, pacmanY);
//
//        int targetX, targetY;
//        if (distance > 8.0f) {
//            // Target Pacman directly when far
//            targetX = pacmanX;
//            targetY = pacmanY;
//        }
//        else {
//            // Retreat to corner when close
//            targetX = cornerX;
//            targetY = cornerY;
//        }
//
//        // Move toward the target position
//        Direction bestDir = getBestDirectionToTarget(ghost, maze, targetX, targetY);
//        ghost->setNextDirection(bestDir);
//    }
//
//    // Method to set a specific corner to patrol
//    void setPatrolCorner(int x, int y) {
//        cornerX = x;
//        cornerY = y;
//    }
//};
//
//// Factory method to create the appropriate strategy based on ghost type
//GhostStrategy* createGhostStrategy(Ghost::GhostType type, Ghost* blinkyRef = nullptr) {
//    switch (type) {
//    case Ghost::RED:
//        return new DirectPursuitStrategy();
//    case Ghost::BLUE:
//        return new FlankingStrategy(blinkyRef);
//    case Ghost::PINK:
//        return new AmbushStrategy();
//    case Ghost::ORANGE:
//        return new PatrolStrategy();
//    default:
//        return new RandomStrategy();
//    }
//}
//
//#endif // GHOST_STRATEGY_H