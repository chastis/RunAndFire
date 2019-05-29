#pragma once
#ifndef HELPERS_H
#define HELPERS_H
#include "headers_which_you_need.h"

constexpr auto TITLE_SIZE			= 16;
constexpr auto PLAYER_GUN_SPEED		= 3; // per second
constexpr auto GOLEM_DMG			= 45;
constexpr auto PLAYER_HP			= 100;
constexpr auto MAX_DJBOXES_COUNT	= 15;
constexpr auto CRATES_RESPAWN		= 3000ll; // in milliseconds
constexpr auto MED_KIT_HP_BOOST		= 50;
constexpr auto MAP_H				= 30;
constexpr auto MAP_W				= 40;
constexpr auto PLAYET_BULLETS		= 10000;
constexpr auto MAP_FILE				= "images/map.png";
constexpr auto FONT_FILE			= "terminal.TTF";

using Point = sf::Vector2f;
enum class LootType { AMMO, HP };
enum class State { right, left, up, down, jump, stay };
enum class Monsters { none, golem, bossGolem };
enum class Direcions { u, d, l, r, ur, ul, dr, dl};
static bool gameOn = true;

#endif //HELPERS_H