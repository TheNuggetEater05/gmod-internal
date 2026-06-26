#pragma once

#ifndef IVENGINECLIENT_H
#define IVENGINECLIENT_H

#include <string>
#include <cstdint>

struct Vec2;

typedef struct player_info_s
{
	char name[32];
	std::uint8_t data[292];
} player_info_t;

class IVEngineClient
{
public:
	void GetScreenSize(int& width, int& height);
	std::string GetPlayerName(int ent_num);
	bool IsInGame();
	bool IsConnected();
};

#endif // !IVENGINECLIENT_H
