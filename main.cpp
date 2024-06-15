#include "CScene.h"

int main(int, char**){
    CScene *Scene = new CScene(); // Create a new scene.
    Scene->Init(); // Initialize the scene.
    Scene->Run(); // Run the main game loop.
    delete Scene; // Clean up the scene.
    Scene = NULL;
}
