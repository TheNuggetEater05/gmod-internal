#pragma once

#ifndef IVENGINECLIENT_H
#define IVENGINECLIENT_H

struct Vec2;

typedef struct player_info_s
{
	static void* m_DataMap;
	static void* GetBaseMap();
	template <typename T> friend void DataMapAccess(T*, void** p);
	template <typename T> friend void* DataMapInit(T*);

	char name[32];
	int userID;
} player_info_t;

class IVEngineClient
{
public:
	void GetScreenSize(int& width, int& height);
	bool GetPlayerName(int ent_num, player_info_t* pinfo);
};

#endif // !IVENGINECLIENT_H
