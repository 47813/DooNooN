#ifndef __Mission__
#define __Mission__

#include <iostream>
#include <string>

class Mission {
public:
    int goal[4];
    int progress[4]; // Array to store current progress for each goal.

    Mission() {};
    Mission(int stage);

    int getGoalScore();
    int getGoalGrow();
    int getGoalPoison();
    int getGoalGate();

    void updateProgress(int index, int value); // Method to update progress.
    int getProgress(int index); // Method to get current progress.
    bool isMissionComplete(); // Method to check if the mission is complete.
    void resetMission(); // Method to reset the mission progress.
};

#endif
