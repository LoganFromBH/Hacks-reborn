#pragma once

#include "SAMPFUNCS_API.h"
#include "game_api.h"
#include "Hack.h"

#include <future>
#include <fstream>


enum class Priority
{
	HIGH,
	MIDDLE,
	LOW,
	DEFAULT
};

enum class HACK_TYPE
{
	VISUAL,
	SHOOTING,
	MISC
};

typedef std::tuple<Priority, HACK_TYPE, IHack*> Hack;

class HacksManager : public Lippets::LUtils::Classes::NonCopyable
{
private:
	HacksManager();
	std::vector<Hack> m_hacks;
public:

	static HacksManager* getInstance();
	const std::vector<Hack>* getHacks();
	void destroy();
	bool drawHacks();
	void drawInterface();
	void drawMenu();
	void read();
	void save();
	bool procRakNetHook(stRakNetHookParams* params, RakNetScriptHookType procFunc);
	bool procKeys();
	void procEveryTickAction();
	void initHacksOnce();
};
