#include "CScene.h"
#include "CSnake.h"
#include "CMap.h"
#include "CItems.h"
#include "CGates.h"
#include "Mission.h"
#include "CMapBuilder.h"
#include <ncurses.h>

CScene::CScene() : Snake(nullptr), CurrentMap(nullptr), Items(nullptr), Gates(nullptr), mission(nullptr), youDie(false), snakey(10), snakex(10), input(0), stage(1), totalGrow(0), totalPoison(0), totalGate(0) {
}

CScene::~CScene() {
    delete Snake;
    delete CurrentMap;
    delete Items;
    delete Gates;
    delete mission;
}

void CScene::Run() {
    snakey = snakex = 10;
    this->Init();

    while (!youDie) {
        this->Update();
        clear();
        this->Render();
        input = ERR;
        int ch;
        while ((ch = getch()) != ERR) {
            input = ch;
        }
        usleep(TICKTIME);
    }
    endwin();
}

void CScene::Init() {
    initscr();
    noecho();
    curs_set(FALSE);
    nodelay(stdscr, TRUE);
    keypad(stdscr, TRUE);

    srand(time(NULL));

    youDie = false;
    Snake = new CSnake(snakey, snakex);
    Items = new CItems(GROW_MAKE, POISON_MAKE);
    Gates = new CGates();
    CurrentMap = new CMap();
    mission = new Mission(stage); // Initialize mission for current stage.
    CurrentMap->Init(stage);
}

void CScene::Update() {
    MapUpdate();

    Items->Update(this);
    Gates->Update(this);
    Snake->Update(this, input);

    // Check if the mission is complete
    if (mission->isMissionComplete()) {
        NextStage();
    }
}

void CScene::Render() {
    // Render the game map
    for (int i = 1; i <= 21; i++) {
        for (int j = 1; j <= 21; j++) {
            if (map[i][j][0] == 0) {
                mvprintw(i, j * 2, ".");
            } else {
                mvprintw(i, j * 2, to_string(map[i][j][0]).c_str());
            }
        }
    }

    // Display the scoreboard
    mvprintw(1, 45, "Scoreboard:");
    mvprintw(2, 45, "Current Length: %d", Snake->GetLength());
    mvprintw(3, 45, "Max Length: %d", Snake->GetMaxLength());
    mvprintw(4, 45, "Grow: %d", totalGrow);
    mvprintw(5, 45, "Poison: %d", totalPoison);
    mvprintw(6, 45, "Gate: %d", totalGate);

    // Display mission goals with current progress
    mvprintw(8, 45, "Mission Goals:");
    mvprintw(9, 45, "Grow: %d / %d", mission->getProgress(1), mission->getGoalGrow());
    mvprintw(10, 45, "Poison: %d / %d", mission->getProgress(2), mission->getGoalPoison());
    mvprintw(11, 45, "Gate: %d / %d", mission->getProgress(3), mission->getGoalGate());
}

void CScene::MapUpdate() {
    for (int i = 0; i <= 22; i++) {
        for (int j = 0; j <= 22; j++) {
            map[i][j][0] = CurrentMap->map[i][j];
        }
    }
}

void CScene::SetDie(bool isDie) {
    youDie = isDie;
}

int CScene::GetMapW(int y, int x) {
    return map[y][x][0];
}

void CScene::SetMapW(int y, int x, int w) {
    map[y][x][0] = w;
}

void CScene::SetMapW(int y, int x, int w, int w2) {
    map[y][x][0] = w;
    map[y][x][1] = w2;
}

void CScene::ItemCollision(int y, int x) {
    switch (map[y][x][0]) {
    case 5:
        Items->Collision(map[y][x][1], 0);
        mission->updateProgress(1, 1); // Update grow progress
        totalGrow++; // Update total grow
        break;
    case 6:
        Items->Collision(map[y][x][1], 1);
        mission->updateProgress(2, 1); // Update poison progress
        totalPoison++; // Update total poison
        break;
    default:
        break;
    }
}

void CScene::GateCollision(int y, int x, int dir) {
    auto a = Gates->Collision(this, map[y][x][1], dir);
    Snake->SetPos(a.first.first, a.first.second);
    Snake->SetDir(a.second);
    mission->updateProgress(3, 1); // Update gate progress
    totalGate++; // Update total gate
}

void CScene::GateOn() {
    Gates->SetWarp(true);
}

void CScene::GateOff() {
    Gates->SetWarp(false);
}

void CScene::NextStage() {
    stage++;
    mission->resetMission();
    delete mission; // Delete the old mission object
    mission = new Mission(stage); // Create a new mission object with the new stage
    CurrentMap->Init(stage);

    // Set the snake position near the bottom-right corner
    int newSnakeY = 18 + rand() % 3; // Random y position in range [18, 20]
    int newSnakeX = 18 + rand() % 3; // Random x position in range [18, 20]
    snakey = newSnakeY;
    snakex = newSnakeX;
    Snake->SetPos(snakey, snakex); // Reset snake position
    Snake->SetDir(KEY_LEFT); // Reset snake direction

    MapUpdate(); // Ensure the new map is correctly loaded
}
