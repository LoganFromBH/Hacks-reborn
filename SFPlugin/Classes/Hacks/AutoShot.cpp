#include "AutoShot.h"


AutoShot::AutoShot(const char* name)
{
	m_sHackName = name;
}

void AutoShot::onDrawGUI()
{
	ImGui::Checkbox(m_sHackName.c_str(), &m_bEnabled);
	ImGui::SameLine();
	Lippets::ImGuiSnippets::KeyButton(activationKey, g::keyButtonSplitter);
}
void AutoShot::onWndProc(WPARAM wParam, UINT msg,  crTickLocalPlayerInfo* info)
{
	if (msg != WM_KEYDOWN && msg != WM_LBUTTONDOWN && msg != WM_SYSKEYDOWN)
		return;
	if (activationKey != 0 && wParam == activationKey)
	{
		autoShot = !autoShot;
		notify("Auto Shot", autoShot);
	}
}
void AutoShot::everyTickAction( crTickLocalPlayerInfo* info)
{
	if (!info->isExist || !autoShot || info->isInCar)
		return;
	if (*(DWORD*)PEDSELF->GetMemoryValue(0x79C))
		SF->getGame()->emulateGTAKey(17, 255);
}
void AutoShot::save(nlohmann::json& data)
{
	data["ActivationKey"] = activationKey;
	data[m_sHackName] = m_bEnabled;

}
void AutoShot::read(nlohmann::json& data)
{
	m_bEnabled = data[m_sHackName].get<bool>();
	activationKey = data["ActivationKey"].get<int>();
}