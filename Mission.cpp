#include "Mission.h"

Mission::Mission(int stage) {
    // Set goals based on the stage number
    goal[0] = 0; // Assuming the score goal is not used
    goal[1] = 4 + stage - 1; // Goal Grow
    goal[2] = 1 + stage - 1; // Goal Poison
    goal[3] = 1 + stage - 1; // Goal Gate

    for(int i = 0; i < 4; i++) {
        progress[i] = 0; // Initialize progress to 0.
    }
}

int Mission::getGoalScore() {
    return goal[0];
}

int Mission::getGoalGrow() {
    return goal[1];
}

int Mission::getGoalPoison() {
    return goal[2];
}

int Mission::getGoalGate() {
    return goal[3];
}

void Mission::updateProgress(int index, int value) {
    if(index >= 0 && index < 4) {
        progress[index] += value;
    }
}

int Mission::getProgress(int index) {
    if(index >= 0 && index < 4) {
        return progress[index];
    }
    return 0;
}

bool Mission::isMissionComplete() {
    return progress[1] >= goal[1] && progress[2] >= goal[2] && progress[3] >= goal[3];
}

void Mission::resetMission() {
    for(int i = 0; i < 4; i++) {
        progress[i] = 0;
    }
}
