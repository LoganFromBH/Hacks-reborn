#pragma once
#include "SAMPFUNCS_API.h"
#include "game_api.h"
extern SAMPFUNCS *SF;
#include "nlohmann/json.hpp"

class CMFont
{
public:
	char name[32] = { '0' };
	char FontName[64] = { '0' };
	int FontSize = 0;
	stFontInfo* f = nullptr;
	CMFont(const char*);
	void Init(char*, int, DWORD);
	void Init();
	void Release();
	void ReInit();
	void save(nlohmann::json&);
	void read(nlohmann::json&);

};