#pragma once
#include "Game.h"
class CScene;
class CGates
{
private:
    pair<int,int> gates[2];
    int tick;
    int respawn;
    bool isWarp;
    int y,x;
public:
    CGates();
    ~CGates();
    void Update(CScene * Scene);
    void Refresh(CScene *Scene);
    pair<pair<int,int>,int> Collision(CScene *Scene,int num,int dir);
    bool isWall(int w);
    void SetWarp(bool isWarp);
};

