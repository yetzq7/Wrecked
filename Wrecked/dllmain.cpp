// dllmain.cpp : Defines the entry point for the DLL application.
#include "framework.h"
#include "pch.h"


void WreckedMain
{
    AllocConsole();
    FILE* f;
    freopen_s(&f, "CONOUT$", "w", stdout);
    SetConsoleTitleA("Wrecked | Starting..");

    MH_Initialize();

    Gamemode::Hook();
    Misc::Hook();
    Utils::Hook();
     
    MH_EnableHook(MH_ALL_HOOKS);

    *(bool*)GIsClient = false;
    *(bool*)GIsServer = true;
    UFortEngine::GetEngine()->GameInstance->LocalPlayers.Remove(0);
    UKismetSystemLibrary::ExecuteConsoleCommand(UWorld::GetWorld(), L"open Helios_Terrain", nullptr);
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        std::thread(WreckedMain).detach();
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

