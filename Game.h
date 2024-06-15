#pragma once
#include <vector>
#include <iostream>  // 사용 안됨????
#include <ncurses.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

#define TICKTIME 500000 // Tick time for the game loop in microseconds.
#define ITEMCOOLTIME 20 // Cooldown time for items in ticks.
#define GATECOOLTIME 40 // Cooldown time for gates in ticks.
#define MIN_SNAKEBODY 3 // Minimum length of the snake body.
#define GROW_MAKE 2 // Amount the snake grows when it consumes a growth item.
#define POISON_MAKE 1 // Amount the snake shrinks when it consumes a poison item.
