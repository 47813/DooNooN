#include "CMap.h"
#include"CMapBuilder.h"
CMap::CMap()
{
}

CMap::~CMap()
{
}

void CMap::Init(int mapNum)
{
    switch (mapNum)
    {
        case 1:
            Map1Builder=new CMapBuilder;
            Map1Builder->BuildMap1(this);
            break;
        case 2:
            Map1Builder=new CMapBuilder;
            Map1Builder->BuildMap2(this);
            break;
        case 3:
            Map1Builder=new CMapBuilder;
            Map1Builder->BuildMap3(this);
            break;
        case 4:
            Map1Builder=new CMapBuilder;
            Map1Builder->BuildMap4(this);
            break;
        default:
            break;
    }
} // CMap/cpp