#include "1lineHacks.h"

void EnableNoAnims(bool bEnable)
{
	static const char16_t temp = 35669;//*(char16_t*)dwFUNC_DANIM;
	if (bEnable)
		WriteMem<char16_t>((SF->getSAMP()->getSAMPAddr() + 0x16FA0), 2, 50064);
	else
		WriteMem<char16_t>((SF->getSAMP()->getSAMPAddr() + 0x16FA0), 2, temp);
};

void EnableNoFreeze(bool bEnable)
{
	static const char16_t temp = 18921;//*(char16_t*)dwFUNC_Freez;
	if (bEnable)
		WriteMem<char16_t>((SF->getSAMP()->getSAMPAddr() + 0x168E0), 2, 50064);
	else
		WriteMem<char16_t>((SF->getSAMP()->getSAMPAddr() + 0x168E0), 2, temp);
}

void EnableAntiStun(bool bEnable)
{
	if (bEnable)
		*(uint8_t*)(*(uint32_t*)(0x00B6F5F0) + 0x478) = 0x04;
	else
		*(uint8_t*)(*(uint32_t*)(0x00B6F5F0) + 0x478) = 0x00;
}

void EnableDriveOrWalkUnderWater(bool bEnable)
{
	*(byte*)0x6C2759 = bEnable;
}

void EnableFireProtection(bool bEnable)
{
	WriteMem<byte>(0xB7CEE6, 1U, bEnable);
}

void EnableFastCrosshair(bool bEnable)
{
	static const byte temp = 116;//*(byte*)0x0058E1D9;`
	if (bEnable)
		WriteMem<byte>(0x0058E1D9, 1, 235);
	else
		WriteMem<byte>(0x0058E1D9, 1, temp);
}

void EnableInfOxygenAndStamina(bool bEnable)
{
	WriteMem<byte>(0x96916E, 1U, bEnable);
	WriteMem<byte>(0xB7CEE4, 1U, bEnable);
}

void EnableMegaJump(bool bEnable)
{
	WriteMem<byte>(0x96916C, 1, bEnable);
}

void EnableNoSpread(bool bEnable)
{
	*reinterpret_cast<float*>(0x008D6114) = (!bEnable * 100.f) / 20.f;
}

void EnableNoCamRestore(bool bEnable)
{
	static const byte temp1 = 122;//*(byte*)0x5109AC;
	static const byte temp2 = 122;// *(byte*)0x5109C5;
	static const byte temp3 = 117;// *(byte*)0x5231A6;
	static const byte temp4 = 117;// *(byte*)0x52322D;
	static const byte temp5 = 117;// *(byte*)0x5233BA;
	if (bEnable)
	{
		WriteMem<byte>(0x5109AC, 1, 235);
		WriteMem<byte>(0x5109C5, 1, 235);
		WriteMem<byte>(0x5231A6, 1, 235);
		WriteMem<byte>(0x52322D, 1, 235);
		WriteMem<byte>(0x5233BA, 1, 235);
	}
	else
	{
		WriteMem<byte>(0x5109AC, 1, temp1);
		WriteMem<byte>(0x5109C5, 1, temp2);
		WriteMem<byte>(0x5231A6, 1, temp3);
		WriteMem<byte>(0x52322D, 1, temp4);
		WriteMem<byte>(0x5233BA, 1, temp5);
	}

}

void EnableWallShot(bool bEnable)
{

	if (bEnable) {
		WriteMem(0x00740701, false, true);
		WriteMem(0x00740703, false, true);
		WriteMem(0x00740709, false, true);

		WriteMem(0x00740B49, false, true);
		WriteMem(0x00740B4B, false, true);
		WriteMem(0x00740B51, false, true);

		WriteMem(0x0073620D, false, true);
		WriteMem(0x0073620F, false, true);
		WriteMem(0x00736215, false, true);
	}
	else {
		WriteMem(0x00740701, true, true);
		WriteMem(0x00740703, true, true);
		WriteMem(0x00740709, true, true);

		WriteMem(0x00740B49, true, true);
		WriteMem(0x00740B4B, true, true);
		WriteMem(0x00740B51, true, true);

		WriteMem(0x0073620D, true, true);
		WriteMem(0x0073620F, true, true);
		WriteMem(0x00736215, true, true);
	}

}

void EnableNoFallDamage(bool bEnable)
{
	if (bEnable)
		SF->getSAMP()->getPlayers()->pLocalPlayer->pSAMP_Actor->pGTAEntity->flags = (0 | 0 | 64 | 0);
	else
		SF->getSAMP()->getPlayers()->pLocalPlayer->pSAMP_Actor->pGTAEntity->flags = (0 | 0 | 0 | 0);
}

void EnableWaterDrive(bool bEnable)
{
	WriteMem<UINT>(0x969152, 4, bEnable);
}

void EnableNewDL(bool bEnable)
{
	if (bEnable)
	{
		DWORD NewProtection;
		VirtualProtect((DWORD*)(SF->getSAMP()->getSAMPAddr() + 0xD83A8), 0x87, PAGE_EXECUTE_READWRITE, &NewProtection);
		memcpy((DWORD*)(SF->getSAMP()->getSAMPAddr() + 0xD83A8), "[id: %d, type: %d subtype: %d Health: %.1f]", 0x87);
		VirtualProtect((DWORD*)(SF->getSAMP()->getSAMPAddr() + 0xD83A8), 0x87, NewProtection, &NewProtection);

	}
	else
	{
		DWORD NewProtection;
		VirtualProtect((DWORD*)(SF->getSAMP()->getSAMPAddr() + 0xD83A8), 0x87, PAGE_EXECUTE_READWRITE, &NewProtection);
		memcpy((DWORD*)(SF->getSAMP()->getSAMPAddr() + 0xD83A8), "[id: %d, type: %d subtype: %d Health: %.1f preloaded: %u]\nDistance: %.2fm\nPassengerSeats: %u\ncPos: %.3f,%.3f,%.3f\nsPos: %.3f,%.3f,%.3f", 0x87);
		VirtualProtect((DWORD*)(SF->getSAMP()->getSAMPAddr() + 0xD83A8), 0x87, NewProtection, &NewProtection);
	}
}

void EnableWaterProofEng(bool bEnable)
{
	static const byte temp = 122;//*(byte*)0x6A90C5;
	if (bEnable)
		WriteMem<byte>(0x6A90C5, 1, 235);
	else
		WriteMem<byte>(0x6A90C5, 1, temp);
}

void Enable160HPbar(bool bEnable)
{
	static const float temp1 = 569.0f;//*(float*)12030944;
	if (bEnable)
		*(float*)12030944 = 930.f;
	else
		*(float*)12030944 = temp1;
}

void GiveWeapon(eWeaponType eWeapon, uint32_t ammo)
{
	PEDSELF->GiveWeapon(eWeapon, ammo, eWeaponSkill::WEAPONSKILL_MAX_NUMBER);
}



OneLineHacks::OneLineHacks(const char* name)
{
	hackName = name;
	isEnable = true;
	SF->getSAMP()->registerChatCommand("setskin", [](std::string args)
	{
		if (Players::isLocalPlayerExist())
		{
			uint32_t iSkinID = atoi(args.c_str());
			if (iSkinID > 0 && iSkinID < 311)
				RPC_emulating::setskin(MYID, iSkinID);
		}
	});
	SF->getSAMP()->registerChatCommand("die", [](std::string args)
	{
		if (Players::isLocalPlayerExist())
			PEDSELF->SetHealth(0.0f);
	});
	SF->getSAMP()->registerChatCommand("delgun", [](std::string args)
	{
		if (Players::isLocalPlayerExist())
		{
			eWeaponSlot eWSlot = PEDSELF->GetCurrentWeaponSlot();
			if (eWSlot != 0)
				PEDSELF->GetWeapon(eWSlot)->Remove();
		}
	});
	SF->getSAMP()->registerChatCommand("parashut", [](std::string args)
	{
		GiveWeapon(eWeaponType::WEAPONTYPE_PARACHUTE, 1);
		PEDSELF->SetCurrentWeaponSlot(eWeaponSlot::WEAPONSLOT_TYPE_PARACHUTE);
	});
	SF->getSAMP()->registerChatCommand("fafk", [](std::string args)
	{
		hacksSettings::bFakeAfk ^= true;
		notify("Fake AFK", hacksSettings::bFakeAfk);
	});
	SF->getSAMP()->registerChatCommand("fasth", [](std::string args)
	{
		hacksSettings::bFastHelper ^= true;
		notify("Fast Helper", hacksSettings::bFastHelper);
	});
}


void OneLineHacks::onDrawGUI()
{
	if (ImGui::Checkbox("Anti Stun", &bAntiStun))
		EnableAntiStun(bAntiStun);
	if (ImGui::Checkbox("Drive Walk UnderWater", &bDriveWalkUnderWater))
		EnableDriveOrWalkUnderWater(bDriveWalkUnderWater);
	if (ImGui::Checkbox("Fire Protection", &bFireProtection))
		EnableFireProtection(bFireProtection);
	if (ImGui::Checkbox("Fast Crosshair", &bFastCrosshair))
		EnableFastCrosshair(bFastCrosshair);
	if (ImGui::Checkbox("Infinity Oxygen | Stamina", &bInfOxygenAndStamina))
		EnableInfOxygenAndStamina(bInfOxygenAndStamina);
	if (ImGui::Checkbox("Mega Jump", &bMegaJump))
		EnableMegaJump(bMegaJump);
	if (ImGui::Checkbox("No Spread", &bNoSpread))
		EnableNoSpread(bNoSpread);
	if (ImGui::Checkbox("No Freeze", &bNoFreeze))
		EnableNoFreeze(bNoFreeze);
	if (ImGui::Checkbox("No Anims", &bNoAnims))
		EnableNoAnims(bNoAnims);
	if (ImGui::Checkbox("No Cam Restore", &bNoCamrestore))
		EnableNoCamRestore(bNoCamrestore);
	ImGui::Checkbox("No Fall", &bNoFall);
	ImGui::Checkbox("Surf On Vehicles", &bSurfOnVehicles);
	if (ImGui::Checkbox("Wall Shot", &bWallShot))
		EnableWallShot(bWallShot);
	ImGui::Checkbox("Press Nitro", &bPressNitro);
	if (ImGui::Checkbox("No Fall Damage", &bNoFallDamage))
		EnableNoFallDamage(bNoFallDamage);
	ImGui::Checkbox("No Bike", &bNoBike);
	if (ImGui::Checkbox("Water Drive", &bWaterDrive))
		EnableWaterDrive(bWaterDrive);
	if (ImGui::Checkbox("New DL", &bNewDl))
		EnableNewDL(bNewDl);
	if (ImGui::Checkbox("Water Proof Engine", &bWaterProofEngine))
		EnableWaterProofEng(bWaterProofEngine);
	if (ImGui::Checkbox("160 HP bar", &bBar160hp))
		Enable160HPbar(bBar160hp);
	ImGui::Checkbox("No Reload", &bNoReload);
	ImGui::Checkbox("Auto Bike", &bAutoBike);
	ImGui::Checkbox("Dont Give Me Bat", &bDontGiveMeBat);
}

void OneLineHacks::onDrawHack(const crTickLocalPlayerInfo& info)
{
	SF->getRender()->DrawPolygon(iScrResX - 10, iScrResY - 10, 10, 10, 0, 7, 0xFF0000FF);
}

void OneLineHacks::switchHack()
{
	EnableAntiStun(bAntiStun);
	EnableDriveOrWalkUnderWater(bDriveWalkUnderWater);
	EnableFireProtection(bFireProtection);
	EnableFastCrosshair(bFastCrosshair);
	EnableInfOxygenAndStamina(bInfOxygenAndStamina);
	EnableMegaJump(bMegaJump);
	EnableNoSpread(bNoSpread);
	EnableNoFreeze(bNoFreeze);
	EnableNoAnims(bNoAnims);
	EnableNoCamRestore(bNoCamrestore);
	EnableWallShot(bWallShot);
	EnableNoFallDamage(bNoFallDamage);
	EnableWaterDrive(bWaterDrive);
	EnableNewDL(bNewDl);
	EnableWaterProofEng(bWaterProofEngine);
	Enable160HPbar(bBar160hp);
}
void OneLineHacks::everyTickAction(const crTickLocalPlayerInfo& info)
{
	if (hacksSettings::bFakeAfk)
		SF->getGame()->emulateGTAKey(4, 255);
	if (info.isDriver)
	{
		if (bNoBike)
		{
			if (Vehicles::getVehicleType(Vehicles::getVehicleCVehicle(Vehicles::getVehicleInfo(VEHICLE_SELF, false))) != Vehicles::eVehicleType::CBike)
				return;
			if (PEDSELF->GetVehicle()->IsDrowning())
			{
				if (PEDSELF->GetCantBeKnockedOffBike() == 1)
					PEDSELF->SetCantBeKnockedOffBike(0);
			}
			else
				if (PEDSELF->GetCantBeKnockedOffBike() == 0)
					PEDSELF->SetCantBeKnockedOffBike(1);
		}
		if (bAutoBike)
		{
			static uint8 eBikeState = 1;
			static DWORD dwBikeTime = 0;
			if (PEDSELF->GetVehicle()->GetGasPedal() == 1.f && !SF->getSAMP()->getInput()->iInputEnabled && !Vehicles::isVehicleInAir(2.5f, VEHICLE_SELF)) //GetAsyncKeyState(87)
			{
				if (GetTickCount() > dwBikeTime)
				{
					if (eBikeState == 1)
					{
						dwBikeTime = GetTickCount() + 30;
						eBikeState = 2;
					}
					else if (eBikeState == 2)
					{
						keybd_event(VK_BACK, 0, 0, 0);
						dwBikeTime = GetTickCount() + 5;
						eBikeState = 3;
					}
					else if (eBikeState == 3)
					{
						keybd_event(VK_BACK, 0, KEYEVENTF_KEYUP, 0);
						eBikeState = 1;
					}
				}
			}
			else
				if (eBikeState == 3)
				{
					keybd_event(VK_BACK, 0, KEYEVENTF_KEYUP, 0);
					eBikeState = 1;
				}
		}
	}


}
void OneLineHacks::onWndProc(WPARAM wParam, UINT msg, const crTickLocalPlayerInfo& info)
{
	if (bPressNitro && info.isDriver)
		if (wParam == 0 || wParam == 1)
			if (msg == WM_KEYDOWN || msg == WM_LBUTTONDOWN || msg == WM_SYSKEYDOWN)
			{
				*reinterpret_cast<byte*>(0x969165) = 1;
			}
			else  if (msg == WM_KEYUP || msg == WM_LBUTTONUP || msg == WM_SYSKEYUP)
			{
				*reinterpret_cast<byte*>(0x969165) = 0;
				PEDSELF->GetVehicle()->RemoveVehicleUpgrade(1010);
			}
}

bool OneLineHacks::onRPCIncoming(stRakNetHookParams *params, const crTickLocalPlayerInfo& info)
{
	if (!bDontGiveMeBat || params->packetId != 22)
		return true;
	UINT32 dWeaponID;
	params->bitStream->ResetReadPointer();
	params->bitStream->Read(dWeaponID);
	if (dWeaponID == 5)
		return false;
	return true;
}
bool OneLineHacks::onPacketOutcoming(stRakNetHookParams *param, const crTickLocalPlayerInfo& info)
{

	if ((bNoFall || bSurfOnVehicles || hacksSettings::bFakeAfk) && (param->packetId == ID_PLAYER_SYNC))
	{
		if (hacksSettings::bFakeAfk)
			return false;
		stOnFootData data;
		memset(&data, 0, sizeof(stOnFootData));
		byte packet;
		param->bitStream->ResetReadPointer();
		param->bitStream->Read(packet);
		param->bitStream->Read((PCHAR)&data, sizeof(stOnFootData));
		param->bitStream->ResetReadPointer();
		if (bNoFall)
			data.stSampKeys.keys_decel__jump = 0;
		if (bSurfOnVehicles)
			data.sSurfingVehicleID = 0;
		param->bitStream->ResetWritePointer();
		param->bitStream->Write(packet);
		param->bitStream->Write((PCHAR)&data, sizeof(stOnFootData));
		return true;
	}
	if (bNoReload && param->packetId == ID_BULLET_SYNC)
		PEDSELF->GetWeapon(PEDSELF->GetCurrentWeaponSlot())->SetAmmoInClip(2);
	return true;
}
void OneLineHacks::save(Json::Value& data)
{
	data["dontGiveMeBat"] = bDontGiveMeBat;
	data["antiStun"] = bAntiStun;
	data["driveWalkUnderWater"] = bDriveWalkUnderWater;
	data["fireProtection"] = bFireProtection;
	data["fastCrosshair"] = bFastCrosshair;
	data["infOxygenAndStamina"] = bInfOxygenAndStamina;
	data["megaJump"] = bMegaJump;
	data["noSpread"] = bNoSpread;
	data["noFreeze"] = bNoFreeze;
	data["noAnims"] = bNoAnims;
	data["noCamrestore"] = bNoCamrestore;
	data["noFall"] = bNoFall;
	data["surfOnVehicles"] = bSurfOnVehicles;
	data["wallShot"] = bWallShot;
	data["pressNitro"] = bPressNitro;
	data["noFallDamage"] = bNoFallDamage;
	data["noBike"] = bNoBike;
	data["waterDrive"] = bWaterDrive;
	data["noReload"] = bNoReload;
	data["autoBike"] = bAutoBike;
	data["NewDL"] = bNewDl;
	data["WaterProofEng"] = bWaterProofEngine;
	data["160hpbar"] = bBar160hp;
}
void OneLineHacks::read(Json::Value& data)
{
	bDontGiveMeBat = data["dontGiveMeBat"].asBool();
	bAntiStun = data["antiStun"].asBool();
	bDriveWalkUnderWater = data["driveWalkUnderWater"].asBool();
	bFireProtection = data["fireProtection"].asBool();
	bFastCrosshair = data["fastCrosshair"].asBool();
	bInfOxygenAndStamina = data["infOxygenAndStamina"].asBool();
	bMegaJump = data["megaJump"].asBool();
	bNoSpread = data["noSpread"].asBool();
	bNoFreeze = data["noFreeze"].asBool();
	bNoAnims = data["noAnims"].asBool();
	bNoCamrestore = data["noCamrestore"].asBool();
	bNoFall = data["noFall"].asBool();
	bSurfOnVehicles = data["surfOnVehicles"].asBool();
	bWallShot = data["wallShot"].asBool();
	bPressNitro = data["pressNitro"].asBool();
	bNoFallDamage = data["noFallDamage"].asBool();
	bNoBike = data["noBike"].asBool();
	bWaterDrive = data["waterDrive"].asBool();
	bNoReload = data["noReload"].asBool();
	bAutoBike = data["autoBike"].asBool();
	bNewDl = data["NewDL"].asBool();
	bWaterProofEngine = data["WaterProofEng"].asBool();
	bBar160hp = data["160hpbar"].asBool();
}