#pragma once
#ifndef HELPERS_H
#define HELPERS_H
#include "headers_which_you_need.h"

constexpr int TITLE_SIZE = 16;
constexpr int PLAYER_GUN_SPEED = 3; // per second
constexpr int GOLEM_DMG = 45;
constexpr int PLAYER_HP = 100;
constexpr int MAX_DOUBLE_JUMP_POINTS = 15;
constexpr int PLAYER_BULLETS = 100;
enum class State { right, left, up, down, jump, stay };
enum class Monsters { none, golem, bossGolem };
using Point = sf::Vector2f;
static std::vector<std::thread *> threads(MAX_DOUBLE_JUMP_POINTS);


#endif //HELPERS_H