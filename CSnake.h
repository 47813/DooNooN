#pragma once
#include <vector>
#include <iostream>
#include <ncurses.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

class CScene;

class CSnake {
private:
    std::vector<std::pair<int, int>> body; // Vector to store the body parts of the snake.
    int dir; // Current direction of the snake.
    int y, x; // Current position of the snake's head.
    int gatey, gatex; // Position of the gate.
    bool isWarp; // Indicates if the snake is in warp state.
    int lastInput; // Stores the last input direction.
    int currentMapW; // Stores the current map value at the snake's position.
    int maxLength; // Maximum length the snake has ever reached.

public:
    CSnake();
    CSnake(int yy, int xx);
    ~CSnake();
    void Update(class CScene *Scene, int input); // Update the snake's state.
    void GoSnake(class CScene *Scene); // Update the snake's position and handle collisions.
    void SetPos(int y, int x); // Set the snake's position.
    void SetDir(int dir); // Set the snake's direction.
    int GetLength() const; // Method to get the snake's current length.
    int GetMaxLength() const; // Method to get the snake's maximum length.
};
