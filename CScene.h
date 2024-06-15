#pragma once
#include "CSnake.h"
#include "CMap.h"
#include "CItems.h"
#include "CGates.h"
#include "Mission.h"

class CScene
{
private:
    int map[30][30][2]{0};
    CSnake *Snake;
    CMap *CurrentMap;
    CItems *Items;
    CGates *Gates;
    Mission *mission; // Pointer to Mission object.
    int snakey, snakex;
    int input;
    bool youDie;
    int stage; // Current stage number

    int totalGrow;
    int totalPoison;
    int totalGate;

public:
    CScene();
    ~CScene();
    void Run();
    void Init();
    void Update();
    void Render();
    void MapUpdate();
    void SetDie(bool isDie);
    int GetMapW(int y, int x);
    void SetMapW(int y, int x, int w);
    void SetMapW(int y, int x, int w, int w2);
    void ItemCollision(int y, int x);
    void GateCollision(int y, int x, int dir);
    void GateOn();
    void GateOff();
    void NextStage(); // Method to advance to the next stage
};
