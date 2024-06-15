#pragma once
#include"Game.h"
class CMapBuilder;
class CMap
{
private:
    CMapBuilder * Map1Builder;
public:

    CMap(/* args */);
    ~CMap();
    void Init(int mapNum);
    int map[30][30]{0};
};