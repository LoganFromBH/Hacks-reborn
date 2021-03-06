#pragma once
#include "Hack.h"
#include "FIles\Numbers.h"

class ChatBubble
{
public:
	UINT16 PlayerID = 0;
	UINT32 color = 0;
	DWORD timer = 0;
	float drawDistance = 0.f;
	char message[128];
	ChatBubble(UINT16 PlayerID,
		UINT32 color,
		UINT32 expiretime,
		float drawDistance,
		char* message);
	ChatBubble() {}
};



HACK_CLASS(WallHack)
{
public:
	WallHack(const char* name);
private:
	CMFont font = CMFont("WallHack");
	std::list<ChatBubble> chatBubbles;
	// wallhack
	bool bNoNameTags = 0;
	int activationKey = 0;
	float fOrigDrawDistance = 100.f;
	bool wallHack = true;
	bool drawWallHack = false;
	bool  bDrawBones = false;
	bool  bShowGun = false;
	bool  bShowVeh = false;
	bool  bShowScore = false;
	// nametags
	int iBoxHight = 0;
	int iYBoxOffset = 0;
	float fYChatBubleOffset = 0.f;
	float fNameTagYOffset = 0.0;
	//
	OVERRIDE_RELEASE;
	OVERRIDE_INIT;
	OVERRIDE_SAVE_READ;
	OVERRIDE_EVERY_TICK;
	OVERRIDE_DRAWGUI;

	OVERRIDE_SWITCH_HACK;
	OVERRIDE_WNDPROC;
	OVERRIDE_RPC_INC;
	OVERRIDE_DRAW_HACK;

};