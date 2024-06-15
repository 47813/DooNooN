#pragma once
#include"Game.h"
class CScene;

class CItems
{
private:
    vector<pair<int, int>> items[2];
    int tick;
    int respawn;
    int count[2];
public:
    CItems(int sizeGrow,int sizePoison);
    ~CItems();
    void Update(CScene * Scene);
    void Refresh(CScene * Scene,int isMinus);
    void Collision(int index,int isMinus);
};

