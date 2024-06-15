#include "CItems.h"
#include"CScene.h"
CItems::CItems(int sizeGrow,int sizePoison)
{
    tick=respawn=ITEMCOOLTIME;
    this->count[0]=sizeGrow;
    this->count[1]=sizePoison;
}

CItems::~CItems()
{

}

void CItems::Update(CScene *Scene)
{
    tick++;
    if(tick>=respawn)
    {
        tick=0;
        Refresh(Scene,0);
        Refresh(Scene,1);
    }
    for (int i = 0; i < items[0].size(); i++)
    {
        int y,x;
        y=items[0][i].first;
        x=items[0][i].second;
        Scene->SetMapW(y,x,5,i);
    }
    for (int i = 0; i < items[1].size(); i++)
    {
        int y,x;
        y=items[1][i].first;
        x=items[1][i].second;
        Scene->SetMapW(y,x,6,i);
    }
}

void CItems::Refresh(CScene *Scene,int isMinus)
{
    items[isMinus].clear();
    for (int i = 0; i < count[isMinus]; i++)
    {
        int y,x;
        y=1+rand()%21;
        x=1+rand()%21;
        while (Scene->GetMapW(y,x)!=0)
        {
            y=1+rand()%21;
            x=1+rand()%21;
        }
        items[isMinus].push_back({y,x});
    }
}

void CItems::Collision(int index,int isMinus)
{
    items[isMinus].erase(items[isMinus].begin()+index);
}
