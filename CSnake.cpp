#include "CSnake.h"
#include "CScene.h"

CSnake::CSnake() : maxLength(0) {
}

CSnake::CSnake(int yy, int xx) : maxLength(0) {
    lastInput = KEY_LEFT;
    this->y = yy;
    this->x = xx;
    body.push_back({ y, x });
    body.push_back({ y, x + 1 });
    body.push_back({ y, x + 2 });
    maxLength = body.size(); // Initialize maxLength
}

CSnake::~CSnake() {
}

void CSnake::Update(CScene *Scene, int input) {
    // Prevent moving in the opposite direction
    if ((input == KEY_UP && lastInput == KEY_DOWN) ||
        (input == KEY_DOWN && lastInput == KEY_UP) ||
        (input == KEY_LEFT && lastInput == KEY_RIGHT) ||
        (input == KEY_RIGHT && lastInput == KEY_LEFT)) {
        Scene->SetDie(true);
        return;
    }
    if (input == KEY_UP || input == KEY_DOWN || input == KEY_LEFT || input == KEY_RIGHT) {
        lastInput = input;
    }

    switch (lastInput) {
    case KEY_UP:
        --y;
        break;
    case KEY_DOWN:
        ++y;
        break;
    case KEY_LEFT:
        --x;
        break;
    case KEY_RIGHT:
        ++x;
        break;
    default:
        break;
    }
    currentMapW = Scene->GetMapW(y, x);
    GoSnake(Scene);
}

void CSnake::GoSnake(CScene *Scene) {
    if (currentMapW == 7) {
        Scene->GateCollision(y, x, lastInput);
        Scene->GateOn();
        isWarp = true;
        gatey = y;
        gatex = x;
        currentMapW = Scene->GetMapW(y, x);
    }

    switch (currentMapW) {
    case 0:
        break;
    case -1:
    case 1:
    case 2:
    case 3:
    case 4:
        Scene->SetDie(true);
        break;
    case 5:
        body.push_back({ 1, 1 });
        if (body.size() > maxLength) {
            maxLength = body.size(); // Update maxLength
        }
        Scene->ItemCollision(y, x);
        break;
    case 6:
        body.pop_back();
        Scene->ItemCollision(y, x);
        if (body.size() < MIN_SNAKEBODY) {
            Scene->SetDie(true);
        }
        break;
    case 7:
        Scene->GateCollision(y, x, lastInput);
        break;
    default:
        break;
    }

    for (int i = body.size() - 1; i > 0; i--) {
        body[i].first = body[i - 1].first;
        body[i].second = body[i - 1].second;
        Scene->SetMapW(body[i].first, body[i].second, 4);
    }
    if (isWarp) {
        if (body[body.size() - 1].first == gatey && body[body.size() - 1].second == gatex) {
            Scene->GateOff();
            isWarp = false;
        }
    }

    body[0] = { y, x };
    Scene->SetMapW(body[0].first, body[0].second, 3);
}

void CSnake::SetPos(int y, int x) {
    this->y = y;
    this->x = x;
}

void CSnake::SetDir(int dir) {
    lastInput = dir;
}

int CSnake::GetLength() const {
    return body.size();
}

int CSnake::GetMaxLength() const {
    return maxLength;
}
