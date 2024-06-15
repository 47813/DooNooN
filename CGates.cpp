#include "CGates.h"
#include "CScene.h"

// CGates 클래스 생성자
CGates::CGates() {
    tick = respawn = GATECOOLTIME; // Gate 초기화 및, Gate 초기화 기준 (tick = respawn) 초기화
    isWarp = false; // 현재 warp 사용 여부 (기본 = false)
    y = x = 0; // 게이트 지정 좌표 초기화
}

// CGates 클래스 소멸자
CGates::~CGates() {
}

// CGates 클래스 중 Update 메서드
void CGates::Update(CScene *Scene) {
    tick++; // tick 증가
    if (tick >= respawn) { // gate 초기화 기준
        tick = 0; // tick 초기화
        if (!isWarp) { // 현재 warp 사용 여부가 false 면
            Refresh(Scene); // 게이트 새로 생성
        }
    }
    // 게이트 위치 출력
    for (int i = 0; i < 2; i++) {
        int a, b;
        a = gates[i].first;
        b = gates[i].second;
        Scene->SetMapW(a, b, 7, i); // 맵에 게이트 표시 (값 7)
    }
}

// CGates 클래스 중 Refresh 메서드
void CGates::Refresh(CScene *Scene) {
    // 두 개의 게이트 위치 생성
    for (int i = 0; i < 2; i++) {
        int a, b;
        a = 1 + rand() % 21;
        b = 1 + rand() % 21;  // 무작위 값을 위해 rand 함수 사용
        // 무작위 좌표가 벽(1)인지 확인. 만약 벽이 아니면 새로운 좌표 설정
        while (Scene->GetMapW(a, b) != 1) {
            a = 1 + rand() % 21;
            b = 1 + rand() % 21;
        }
        gates[i] = {a, b}; // 게이트 위치 설정
    }
}

// CGates 클래스 중 Collision 메서드
// Snake 와 Gate 의 상호 작용
pair<pair<int, int>, int> CGates::Collision(CScene *Scene, int num, int dir) {
    int w, d;
    isWarp = true; // 현재 Gate 사용 여부 변경
    y = gates[1 - num].first; // 반대편 게이트 y 좌표
    x = gates[1 - num].second; // 반대편 게이트 x 좌표

    // Snake 가 나올 방향을 결정
    switch (dir) {
        case KEY_UP:
            if (!isWall(Scene->GetMapW(y - 1, x))) {
                y = y - 1;
                d = KEY_UP;
            } else if (!isWall(Scene->GetMapW(y, x + 1))) {
                x = x + 1;
                d = KEY_RIGHT;
            } else if (!isWall(Scene->GetMapW(y, x - 1))) {
                x = x - 1;
                d = KEY_LEFT;
            } else if (!isWall(Scene->GetMapW(y + 1, x))) {
                y = y + 1;
                d = KEY_DOWN;
            } else {
                Scene->SetDie(true); // 모든 방향이 막혀 있으면 게임 종료
            }
            break;
        case KEY_DOWN:
            if (!isWall(Scene->GetMapW(y + 1, x))) {
                y = y + 1;
                d = KEY_DOWN;
            } else if (!isWall(Scene->GetMapW(y, x - 1))) {
                x = x - 1;
                d = KEY_LEFT;
            } else if (!isWall(Scene->GetMapW(y, x + 1))) {
                x = x + 1;
                d = KEY_RIGHT;
            } else if (!isWall(Scene->GetMapW(y - 1, x))) {
                y = y - 1;
                d = KEY_UP;
            } else {
                Scene->SetDie(true); // 모든 방향이 막혀 있으면 게임 종료
            }
            break;
        case KEY_LEFT:
            if (!isWall(Scene->GetMapW(y, x - 1))) {
                x = x - 1;
                d = KEY_LEFT;
            } else if (!isWall(Scene->GetMapW(y - 1, x))) {
                y = y - 1;
                d = KEY_UP;
            } else if (!isWall(Scene->GetMapW(y + 1, x))) {
                y = y + 1;
                d = KEY_DOWN;
            } else if (!isWall(Scene->GetMapW(y, x + 1))) {
                x = x + 1;
                d = KEY_RIGHT;
            } else {
                Scene->SetDie(true); // 모든 방향이 막혀 있으면 게임 종료
            }
            break;
        case KEY_RIGHT:
            if (!isWall(Scene->GetMapW(y, x + 1))) {
                x = x + 1;
                d = KEY_RIGHT;
            } else if (!isWall(Scene->GetMapW(y + 1, x))) {
                y = y + 1;
                d = KEY_DOWN;
            } else if (!isWall(Scene->GetMapW(y - 1, x))) {
                y = y - 1;
                d = KEY_UP;
            } else if (!isWall(Scene->GetMapW(y, x - 1))) {
                x = x - 1;
                d = KEY_LEFT;
            } else {
                Scene->SetDie(true); // 모든 방향이 막혀 있으면 게임 종료
            }
            break;
        default:
            break;
    }
    return {{y, x}, d}; // 새로운 좌표와 방향 반환
}

// CGates 클래스의 isWall 메서드
// 주어진 값이 벽인지 확인
bool CGates::isWall(int w) {
    return (w == -1 || w == 1 || w == 2 || w == 7);
}

// CGates 클래스의 SetWarp 메서드
// isWarp 값을 설정
void CGates::SetWarp(bool isWarp) {
    this->isWarp = isWarp;
}
