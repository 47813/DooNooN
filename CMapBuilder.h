#pragma once
#include "Game.h"

class CMap;

class CMapBuilder {
public:
    CMapBuilder();
    ~CMapBuilder();

    void Garo(CMap * t, int y, int start, int end, int w);
    void Sero(CMap * t, int x, int start, int end, int w);
    void BuildMap1(CMap * t);
    void BuildMap2(CMap * t);
    void BuildMap3(CMap * t);
    void BuildMap4(CMap * t);
};
