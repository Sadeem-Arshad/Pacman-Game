#  Pac-Man Game (C++ / SFML)

A **Pac-Man clone built in C++ using the SFML graphics library**.
The game recreates the classic arcade gameplay where Pac-Man navigates a maze, eats dots and power pellets, and avoids or hunts ghosts depending on the game state.

This project demonstrates **object-oriented design, AI movement strategies, and real-time game programming** using the **SFML graphics framework**.

---

#  Project Overview

This Pac-Man implementation features:

* A fully playable **maze environment**
* **Four ghosts** with different AI strategies
* **Power pellet mechanics** that temporarily allow Pac-Man to eat ghosts
* **Score tracking and life system**
* **Real-time keyboard controls**

The game uses **C++ object-oriented programming concepts** including classes, inheritance, and the **Strategy Design Pattern** to implement ghost behaviors.

---

#  Game Features

* Classic **Pac-Man gameplay**
* Smooth **real-time movement**
* **Four unique ghosts** with different AI behaviors
* **Power pellet mode** where ghosts become frightened
* **Score and lives system**
* **Ghost house and release timing**
* **Collision detection**
* **Game reset functionality**

---

#  Ghost AI Strategies

Each ghost uses a different strategy to chase Pac-Man:

| Ghost             | Behavior                                         |
| ----------------- | ------------------------------------------------ |
| 🔴 Red (Blinky)   | Direct pursuit of Pac-Man                        |
| 🌸 Pink (Pinky)   | Ambush strategy targeting tiles ahead of Pac-Man |
| 🔵 Blue (Inky)    | Patrol and chase combination                     |
| 🟠 Orange (Clyde) | Random movement                                  |

These behaviors are implemented using the **Strategy Design Pattern**, allowing flexible AI behavior switching.

---

#  Game Mechanics

### Pac-Man Abilities

* Eat **dots** to increase score
* Eat **power pellets** to frighten ghosts
* Eat frightened ghosts for bonus points

### Ghost States

Ghosts can be in different states:

* **Normal** – chasing Pac-Man
* **Frightened** – moving away after power pellet
* **Eaten** – returning to ghost house

### Ghost Release System

Ghosts leave the ghost house based on a timer:

| Ghost  | Release Time |
| ------ | ------------ |
| Red    | 1 second     |
| Pink   | 3 seconds    |
| Blue   | 5 seconds    |
| Orange | 7 seconds    |

---

#  Controls

| Key     | Action                          |
| ------- | ------------------------------- |
| ⬆ Arrow | Move Up                         |
| ⬇ Arrow | Move Down                       |
| ⬅ Arrow | Move Left                       |
| ➡ Arrow | Move Right                      |
| **R**   | Reset Game                      |
| **F**   | Trigger Frightened Mode (Debug) |
| **L**   | Release All Ghosts (Debug)      |
| **ESC** | Exit Game                       |

---

#  Technologies Used

* **C++**
* **SFML (Simple and Fast Multimedia Library)**
* **Object-Oriented Programming**
* **Strategy Design Pattern**

---


### Main Components

**Maze**

* Handles map layout
* Draws maze and dots
* Tracks score

**Pacman**

* Handles player movement
* Manages lives and power mode
* Collision with dots and ghosts

**Ghost**

* Handles ghost movement
* Implements different AI strategies
* Manages ghost states

---

#  Concepts Demonstrated

This project demonstrates several important **game development concepts**:

* Object-Oriented Programming (OOP)
* Strategy Design Pattern
* Real-time game loops
* Collision detection
* AI movement algorithms
* Event handling with SFML
* Game state management

---

#  Contributors

Developed by:

**Sadeem Arshad**
**Hamza Sheikh**

FAST National University of Computer and Emerging Sciences (FAST-NUCES), Lahore.

---

#  Acknowledgment

Inspired by the **classic Pac-Man arcade game** originally developed by **Namco**.

---

If you like the project, consider **starring the repository**!
