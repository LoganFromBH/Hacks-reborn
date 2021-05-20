#include "plog\Log.h"
#include "HacksManager.h"

#include "AirBrake.h"	   
#include "WallHack_NewNameTags.h"
#include "1LineHacks.h"
#include "AutoShot.h"
#include "InputHelper.h"
#include "BMXSpeedHack.h"
#include "TurboControl.h"
#include "Fix.h"
#include "PlayersList.h"
#include "OneBulletKill.h"
#include "AltClicker.h"
#include "Binder.h"
#include "AimBot.h"
#include "WallShot.h"
#include "ArizonaLEmulator.h"
#include "CustomRender.h"
#include "Collision.h"


#include "nameof/nameof.hpp"
#include <chrono>
using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::duration;
using std::chrono::milliseconds;


namespace g
{
	extern std::string settingsPath;	
	extern bool isWindowOpen;
};


HacksManager::HacksManager()
{
}

HacksManager* HacksManager::getInstance()
{
	static HacksManager instance;
	return &instance;
}

void HacksManager::initHacksOnce()
{
	static bool isInitialized = false;
	if (isInitialized)
		return;

	m_hacks.clear();

	m_hacks.emplace_back(std::make_tuple(Priority::HIGH, HACK_TYPE::MISC, new PlayersList("Players List")));
	m_hacks.emplace_back(std::make_tuple(Priority::HIGH, HACK_TYPE::SHOOTING, new OneBulletKill("One Bullet Kill")));
	m_hacks.emplace_back(std::make_tuple(Priority::DEFAULT, HACK_TYPE::SHOOTING, new WallShot("Wall Shot")));
	m_hacks.emplace_back(std::make_tuple(Priority::DEFAULT, HACK_TYPE::SHOOTING, new Aimbot("Aimbot")));
	m_hacks.emplace_back(std::make_tuple(Priority::DEFAULT, HACK_TYPE::VISUAL, new WallHack("Wall Hack")));
	m_hacks.emplace_back(std::make_tuple(Priority::DEFAULT, HACK_TYPE::SHOOTING, new AutoShot("Auto Shot")));
	m_hacks.emplace_back(std::make_tuple(Priority::DEFAULT, HACK_TYPE::MISC, new  AirBrake("Air Brake")));
	m_hacks.emplace_back(std::make_tuple(Priority::DEFAULT, HACK_TYPE::MISC, new InputHelper("Input Helper")));
	m_hacks.emplace_back(std::make_tuple(Priority::DEFAULT, HACK_TYPE::MISC, new BMXspeedhack("BMX Speedhack")));
	m_hacks.emplace_back(std::make_tuple(Priority::DEFAULT, HACK_TYPE::MISC, new TurboControl("Turbo Control")));
	m_hacks.emplace_back(std::make_tuple(Priority::DEFAULT, HACK_TYPE::MISC, new AltClicker("Alt Clicker")));
	m_hacks.emplace_back(std::make_tuple(Priority::DEFAULT, HACK_TYPE::MISC, new Binder("Binder")));
	m_hacks.emplace_back(std::make_tuple(Priority::DEFAULT, HACK_TYPE::MISC, new Fix("Fix")));
	m_hacks.emplace_back(std::make_tuple(Priority::DEFAULT, HACK_TYPE::MISC, new OneLineHacks("OneLineHacks")));
	m_hacks.emplace_back(std::make_tuple(Priority::DEFAULT, HACK_TYPE::MISC, new ArizonaLEmulator("Arizona Launcher Emulator")));
	m_hacks.emplace_back(std::make_tuple(Priority::DEFAULT, HACK_TYPE::VISUAL, new CustomRender("Custom Render")));
	m_hacks.emplace_back(std::make_tuple(Priority::DEFAULT, HACK_TYPE::MISC, new CollisionHack("Collision")));
	std::sort(m_hacks.begin(), m_hacks.end(), [](const std::tuple<Priority, HACK_TYPE, IHack*> pair1, const std::tuple<Priority, HACK_TYPE, IHack*>  pair2)
	{
		return std::get<Priority>(pair1) < std::get<Priority>(pair2);
	});

	read();
	for (auto&& hack : m_hacks)
	{
		std::get<IHack*>(hack)->init();
		std::get<IHack*>(hack)->switchHack();
	}

	isInitialized = true;
}

std::vector<std::tuple<Priority, HACK_TYPE, IHack*>>* HacksManager::getHacks()
{
	return &m_hacks;
}

void HacksManager::destroy()
{
	save();
	for (auto&& hack : m_hacks)
	{
		auto&& pHack = std::get<IHack*>(hack);
		pHack->m_bEnabled = false;
		pHack->switchHack();
		pHack->release();
		delete pHack;
	}
	m_hacks.clear();
}

void HacksManager::read()
{
	for (auto&& hack : m_hacks)
	{
		try
		{
			if (!Lippets::Computer::isFileExits(g::settingsPath + std::get<IHack*>(hack)->m_sHackName + ".json"))
				continue;
			std::ifstream in(g::settingsPath + std::get<IHack*>(hack)->m_sHackName + ".json");

			if (!in.is_open())
				continue;

			std::string str;
			getline(in, str);
			in.close();
			nlohmann::json data;

			data = nlohmann::json::parse(str);
			if (!data.is_null())
				std::get<IHack*>(hack)->read(data);
		}
		catch (...)
		{

		}
	}

}
void HacksManager::save()
{
	for (auto&& hack : m_hacks)
	{
		nlohmann::json data;
		data.clear();
		std::get<IHack*>(hack)->save(data);
		std::ofstream out(g::settingsPath + std::get<IHack*>(hack)->m_sHackName + ".json");
		out << data.dump();
		out.close();
	}
}
bool HacksManager::drawHacks()
{
	bool bImGuiNewFrameWasCalled = false;

	for (auto &&hack : m_hacks)
	{
		auto&& pHack = std::get<IHack*>(hack);
		if (pHack->m_bEnabled && !pHack->m_bitsDontCall__.test(DRAW_HACK))
		{
			//PLOGI << "[DRAW HACK]" + pHack->m_sHackName;
			if (!bImGuiNewFrameWasCalled && pHack->m_bDrawHackNeedImGui)
			{
				bImGuiNewFrameWasCalled = true;
				ImGui_ImplDX9_NewFrame();
				ImGui_ImplWin32_NewFrame();
				ImGui::NewFrame();
			}
			pHack->onDrawHack();
			//PLOGI << "[DRAW HACK]" << pHack->m_sHackName << " taked " << (bnchStart - high_resolution_clock::now()).count();
		}
	}


	return bImGuiNewFrameWasCalled;
}
void HacksManager::drawInterface()
{
	ImGui::SetNextWindowPos(ImVec2(iScrResX / 2, iScrResY / 2), ImGuiCond_Once, ImVec2(0.5F, 0.5F));
	ImGui::SetNextWindowSize(ImVec2(550.f, 450.f), ImGuiCond_::ImGuiCond_FirstUseEver);
	ImGui::Begin("hakcs", &g::isWindowOpen);
	{
		g::keyButtonSplitter = 0;
		static uint8 currentGuiMenu = 0;
		if (ImGui::Button("Hacks"))
			currentGuiMenu = 0;
		ImGui::SameLine();
		if (ImGui::Button("Settings"))
			currentGuiMenu = 1;

		ImGui::Separator();

		if (currentGuiMenu == 0)
			drawMenu();
		else
			drawSettings();
	}
	ImGui::End();
}

void HacksManager::drawMenu()
{
	static HACK_TYPE choosedHackType = HACK_TYPE::MISC;
	for (byte i = (byte)HACK_TYPE::VISUAL; i <= (byte)HACK_TYPE::MISC; i++)
	{
		if (ImGui::Button(nameof::nameof_enum((HACK_TYPE)i).data()))
			choosedHackType = (HACK_TYPE)i;
		if (i != (byte)HACK_TYPE::MISC)
			ImGui::SameLine();
	}
	for (auto &&hack : m_hacks)
		if (std::get<HACK_TYPE>(hack) == choosedHackType)
			std::get<IHack*>(hack)->onDrawGUI();

}

void HacksManager::drawSettings()
{
	for (auto &&hack : m_hacks)
		std::get<IHack*>(hack)->onDrawSettings();
}

bool HacksManager::procKeys(WPARAM wParam, UINT msg)
{
	bool bNeedImGuiProcKeys = false;
	for (auto &&hack : m_hacks)
	{
		auto&& pHack = std::get<IHack*>(hack);
		if (pHack->m_bEnabled && !pHack->m_bitsDontCall__.test(WND_PROC))
		{
			//PLOGI << "[PROC KEYS]" << pHack->m_sHackName;
			if (pHack->m_bDrawHackNeedImGui)
				bNeedImGuiProcKeys = true;
			pHack->onWndProc(wParam, msg);
		}
	}
	return bNeedImGuiProcKeys;
}

bool HacksManager::procRakNetHook(stRakNetHookParams* params, RakNetScriptHookType procFunc)
{

	switch (procFunc)
	{
	case RakNetScriptHookType::RAKHOOK_TYPE_INCOMING_RPC:
	{
		for (auto &&hack : m_hacks)
		{
			auto&& pHack = std::get<IHack*>(hack);
			if (pHack->m_bEnabled && !pHack->m_bitsDontCall__.test(RPC_INC))
			{
				//PLOGI << "[INC RPC]" << pHack->m_sHackName;
				if (!pHack->onRPCIncoming(params))
					return false;
			}
		}

		return true;
	}
	case RakNetScriptHookType::RAKHOOK_TYPE_OUTCOMING_RPC:
	{
		for (auto &&hack : m_hacks)
		{
			auto&& pHack = std::get<IHack*>(hack);
			if (pHack->m_bEnabled && !pHack->m_bitsDontCall__.test(RPC_OUT))
			{
				//PLOGI << "[OUT RPC]" << pHack->m_sHackName;
				if (!pHack->onRPCOutcoming(params))
					return false;
			}
		}

		return true;
	}
	case RakNetScriptHookType::RAKHOOK_TYPE_INCOMING_PACKET:
	{
		for (auto &&hack : m_hacks)
		{
			auto&& pHack = std::get<IHack*>(hack);
			if (pHack->m_bEnabled && !pHack->m_bitsDontCall__.test(PACKET_INC))
			{
				//PLOGI << "[INC PACKET]" << pHack->m_sHackName;
				if (!pHack->onPacketIncoming(params))
					return false;
			}
		}

		return true;
	}
	case RakNetScriptHookType::RAKHOOK_TYPE_OUTCOMING_PACKET:
	{
		for (auto &&hack : m_hacks)
		{
			auto&& pHack = std::get<IHack*>(hack);
			if (pHack->m_bEnabled && !pHack->m_bitsDontCall__.test(PACKET_OUT))
			{
				//PLOGI << "[OUT PACKET]" << pHack->m_sHackName;
				if (!pHack->onPacketOutcoming(params))
					return false;
			}
		}

		return true;
	}
	default: break;
	}

	return true;
}
void HacksManager::procEveryTickAction()
{
	for (auto &&hack : m_hacks)
	{
		auto&& pHack = std::get<IHack*>(hack);
		if (pHack->m_bEnabled && !pHack->m_bitsDontCall__.test(EVERY_TICK))
		{
			//PLOGI << "[EVERY TICK ACTION]" << pHack->m_sHackName;
			pHack->everyTickAction();
			//PLOGI << "[EVERY TICK ACTION]" << pHack->m_sHackName << " taked " << (bnchStart - high_resolution_clock::now()).count();
		}
	}
}
