#include "includes.h"

DWORD WINAPI HackThread(HMODULE hmodule)
{

	if (VK_END)
	{
		Beep(5000, 150);
	}
	else if (!VK_END)
	{
		Beep(100, 150);
	}

	DWORD moduleBase = (DWORD)GetModuleHandle("client.dll");

	bool glow = false;
	bool bhop = false;
	bool trigger = false;
	int TriggerCustomDelay = 4;
	bool radar = false;
	bool nf = false;
	bool tPerson = false;
	bool fov = false;
	int iFov = 90;

	while (!GetAsyncKeyState(VK_END))
	{

		if (GetAsyncKeyState(VK_F1) & 1)
		{
			glow = !glow;
			if (glow)
			{
				Beep(1000, 150);
			}
			else
			{
				Beep(400, 150);
			}
		}

		if (GetAsyncKeyState(VK_F2) & 1)
		{
			bhop = !bhop;
			if (bhop)
			{
				Beep(1000, 150);
			}
			else
			{
				Beep(400, 150);
			}
		}

		if (GetAsyncKeyState(VK_F3) & 1)
		{
			trigger = !trigger;
			if (trigger)
			{
				Beep(1000, 150);
			}
			else
			{
				Beep(400, 150);
			}
		}

		if (GetAsyncKeyState(VK_F4) & 1)
		{
			radar = !radar;
			if (radar)
			{
				Beep(1000, 150);
			}
			else
			{
				Beep(400, 150);
			}
		}

		if (GetAsyncKeyState(VK_F9) & 1)
		{
			nf = !nf;
			if (nf)
			{
				Beep(1000, 150);
			}
			else
			{
				Beep(400, 150);
			}
		}

		if (GetAsyncKeyState(VK_F10) & 1)
		{
			tPerson = !tPerson;
			if (tPerson)
			{
				Beep(1000, 150);
			}
			else
			{
				Beep(400, 150);
			}
		}

		if (GetAsyncKeyState(VK_F11) & 1)
		{
			fov = !fov;
			if (fov)
			{
				Beep(1000, 150);
			}
			else
			{
				Beep(400, 150);
			}
		}

		if (glow)
		{
			DWORD LocalP = *(DWORD*)(moduleBase + hazedumper::signatures::dwLocalPlayer);
			DWORD GlowOM = *(DWORD*)(moduleBase + hazedumper::signatures::dwGlowObjectManager);
			DWORD EntityL = *(DWORD*)(moduleBase + hazedumper::signatures::dwEntityList);

			int LocalT = *(int*)(LocalP + hazedumper::netvars::m_iTeamNum);

			for (int i = 1; i < 32; i++)
			{
				DWORD ent = *(DWORD*)((moduleBase + hazedumper::signatures::dwEntityList) + i * 0x10);

				if (ent == NULL) continue;

				int glowI = *(int*)(ent + hazedumper::netvars::m_iGlowIndex);
				int entityT = *(int*)(ent + hazedumper::netvars::m_iTeamNum);

				if (entityT == LocalT)
				{
					*(float*)((GlowOM)+((glowI * 0x38) + 0x8)) = 0.f;
					*(float*)((GlowOM)+((glowI * 0x38) + 0x10)) = 0.f;
					*(float*)((GlowOM)+((glowI * 0x38) + 0xC)) = 1.f;
					*(float*)((GlowOM)+((glowI * 0x38) + 0x14)) = 1.7f;
				}
				else
				{
					*(float*)((GlowOM)+((glowI * 0x38) + 0x8)) = 1.f;
					*(float*)((GlowOM)+((glowI * 0x38) + 0x10)) = 0.f;
					*(float*)((GlowOM)+((glowI * 0x38) + 0xC)) = 0.f;
					*(float*)((GlowOM)+((glowI * 0x38) + 0x14)) = 1.7f;
				}
				*(bool*)((GlowOM)+((glowI * 0x38) + 0x28)) = true;
				*(bool*)((GlowOM)+((glowI * 0x38) + 0x29)) = false;
			}
		}

		if (bhop)
		{
			DWORD LocalP = *(DWORD*)(moduleBase + hazedumper::signatures::dwLocalPlayer);
			DWORD flag = *(BYTE*)(LocalP + hazedumper::netvars::m_fFlags);
			if (GetAsyncKeyState(VK_MBUTTON) && flag & (1 << 0))
			{
				*(DWORD*)(moduleBase + hazedumper::signatures::dwForceJump) = 6;
			}
			Sleep(2);
		}

		if (trigger)
		{
			DWORD LocalP = *(DWORD*)(moduleBase + hazedumper::signatures::dwLocalPlayer);
			int cross = *(int*)(LocalP + hazedumper::netvars::m_iCrosshairId);
			int LocalT = *(int*)(LocalP + hazedumper::netvars::m_iTeamNum);
			if (GetAsyncKeyState(VK_SPACE))
			{
				if (cross != 0 && cross < 64)
				{
					uintptr_t entity = *(uintptr_t*)(moduleBase + hazedumper::signatures::dwEntityList + (cross - 1) * 0x10);
					int eTeam = *(int*)(entity + hazedumper::netvars::m_iTeamNum);
					int eHealth = *(int*)(entity + hazedumper::netvars::m_iHealth);

					if (eTeam != LocalT && eHealth > 0 && eHealth < 101)
					{
						Sleep(TriggerCustomDelay);
						*(int*)(moduleBase + hazedumper::signatures::dwForceAttack) = 5;
						Sleep(20);
						*(int*)(moduleBase + hazedumper::signatures::dwForceAttack) = 4;
					}
				}
			}
			Sleep(2);
		}

		if (radar)
		{
			for (int i = 1; i < 64; i++)
			{
				DWORD EntityList = *(DWORD*)(moduleBase + hazedumper::signatures::dwEntityList + i * 0x10);
				if (EntityList)
				{
					*(bool*)(EntityList + hazedumper::netvars::m_bSpotted) = true;
				}
			}
			Sleep(2);
		}

		if (nf)
		{
			DWORD Player = *(DWORD*)(moduleBase + hazedumper::signatures::dwLocalPlayer);
			*(float*)(Player + hazedumper::netvars::m_flFlashMaxAlpha) = 0.0f;
		}
		else if (!nf)
		{
			DWORD Player = *(DWORD*)(moduleBase + hazedumper::signatures::dwLocalPlayer);
			*(float*)(Player + hazedumper::netvars::m_flFlashMaxAlpha) = 255.0f;
		}

		if (tPerson)
		{
			DWORD Player = *(DWORD*)(moduleBase + hazedumper::signatures::dwLocalPlayer);
			DWORD EntityList = *(DWORD*)(moduleBase + hazedumper::signatures::dwEntityList);
			*(int*)(Player + hazedumper::netvars::m_iObserverMode) = 1;
			*(int*)(EntityList + hazedumper::netvars::m_iDefaultFOV) = 120;
		}
		else if (!tPerson)
		{
			DWORD Player = *(DWORD*)(moduleBase + hazedumper::signatures::dwLocalPlayer);
			DWORD EntityList = *(DWORD*)(moduleBase + hazedumper::signatures::dwEntityList);
			*(int*)(Player + hazedumper::netvars::m_iObserverMode) = 0;
			*(int*)(EntityList + hazedumper::netvars::m_iDefaultFOV) = 90;
		}

		if (fov)
		{
			DWORD EntityList = *(DWORD*)(moduleBase + hazedumper::signatures::dwEntityList);
			*(int*)(EntityList + hazedumper::netvars::m_iDefaultFOV) = iFov;
			if (GetAsyncKeyState(VK_UP))
			{
				iFov += 4;
				Sleep(50);
			}
			else if (GetAsyncKeyState(VK_DOWN))
			{
				iFov -= 4;
				Sleep(50);
			}
			else if (GetAsyncKeyState(VK_HOME))
			{
				*(int*)(EntityList + hazedumper::netvars::m_iDefaultFOV) = 90;
			}
		}

	}

	if (GetAsyncKeyState(VK_END))
	{
		DWORD EntityList = *(DWORD*)(moduleBase + hazedumper::signatures::dwEntityList);
		*(int*)(EntityList + hazedumper::netvars::m_iDefaultFOV) = 90;
		DWORD Player = *(DWORD*)(moduleBase + hazedumper::signatures::dwLocalPlayer);
		*(int*)(Player + hazedumper::netvars::m_iObserverMode) = 0;
	}

	FreeLibraryAndExitThread(hmodule, 0);
}

BOOL WINAPI DllMain(HMODULE hmodule, DWORD ireason, LPVOID lpreserved)
{
	switch (ireason)
	{
	case DLL_PROCESS_ATTACH:
		// Initialize once for each new process.
		// Return FALSE to fail DLL load.
		DisableThreadLibraryCalls(hmodule);
		CloseHandle(CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)HackThread, hmodule, 0, nullptr));
	case DLL_THREAD_ATTACH:
		// Do thread-specific initialization.
	case DLL_THREAD_DETACH:
		// Do thread-specific cleanup.
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}



