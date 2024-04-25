#pragma once

#include <Windows.h>
#include <Minhook.h>
#include <cstdint>
#include <iostream>
#include <stdio.h>

#define MAKE_HOOK(original, hook)\
{\
	MH_CreateHook(original, &hook, reinterpret_cast<LPVOID*>(&original)); \
}

#define CONSOLE_TITLE "Hooks-Console"

#define DEBUG_TO_CONSOLE(msg) \
{ \
    std::cout << msg; \
}

#pragma region Helpers

template<typename targetType>
inline static void AssignAddressToOriginalUsingModule(
	targetType& target,
	const char* targetName,
	HMODULE hModule)
{
	if (hModule != nullptr)
	{
		FARPROC targetAddress = GetProcAddress(hModule, targetName);
		if (targetAddress != nullptr)
		{
			target = reinterpret_cast<targetType>(targetAddress);
		}
		else
		{
			return;
		}
	}
	else
	{
		return;
	}
}

#pragma endregion

#pragma region Hooks

using GetAdapterNames_t = void(__stdcall*)();
static GetAdapterNames_t GetAdapterNames_o;

static void GetAdapterNames_hook()
{
	DEBUG_TO_CONSOLE("GetAdapterNames" << " called!");

	return GetAdapterNames_o();
}

using GetDisplayNames_t = void(__stdcall*)();
static GetDisplayNames_t GetDisplayNames_o;

static void GetDisplayNames_hook()
{
	DEBUG_TO_CONSOLE("GetDisplayNames" << " called!");

	return GetDisplayNames_o();
}

using SetDriverSettings_t = bool(__stdcall*)(int64_t, int64_t, int64_t, int64_t);
static SetDriverSettings_t SetDriverSettings_o;

static bool SetDriverSettings_hook(int64_t param_1, int64_t param_2, int64_t param_3, int64_t param_4)
{
	DEBUG_TO_CONSOLE("SetDriverSettings" << " called!");

	return SetDriverSettings_o(param_1, param_2, param_3, param_4);
}

using SetWindowsSettings_t = void(__stdcall*)();
static SetWindowsSettings_t SetWindowsSettings_o;

static void SetWindowsSettings_hook()
{
	DEBUG_TO_CONSOLE("SetWindowsSettings" << " called!");

	return SetWindowsSettings_o();
}

using ApplySettings_t = void(__stdcall*)(int, int32_t, int32_t, int32_t, int32_t, char, char, int32_t, bool, int32_t, bool, bool, bool, bool, int32_t, bool, bool, bool, bool, int32_t, bool, int32_t, int32_t, int32_t, int32_t, int32_t, int32_t, bool);
static ApplySettings_t ApplySettings_o;

static void ApplySettings_hook(int param_1, int32_t param_2, int32_t param_3, int32_t param_4, int32_t param_5, char param_6, char param_7, int32_t param_8, bool param_9, int32_t param_10, bool param_11, bool param_12, bool param_13, bool param_14, int32_t param_15, bool param_16, bool param_17, bool param_18, bool param_19, int32_t param_20, bool param_21, int32_t param_22, int32_t param_23, int32_t param_24, int32_t param_25, int32_t param_26, int32_t param_27, bool param_28)
{
	DEBUG_TO_CONSOLE("ApplySettings" << " called!");

	return ApplySettings_o(param_1, param_2, param_3, param_4, param_5, param_6, param_7, param_8, param_9, param_10, param_11, param_12, param_13, param_14, param_15, param_16, param_17, param_18, param_19, param_20, param_21, param_22, param_23, param_24, param_25, param_26, param_27, param_28);
}

using Init_t = void(__stdcall*)(int64_t, int64_t, char*, int64_t);
static Init_t Init_o;

static void Init_hook(int64_t param_1, int64_t param_2, char* param_3, int64_t param_4)
{
	DEBUG_TO_CONSOLE("Init" << " called!");

	return Init_o(param_1, param_2, param_3, param_4);
}

using UnInit_t = void(__stdcall*)();
static UnInit_t UnInit_o;

static void UnInit_hook()
{
	DEBUG_TO_CONSOLE("UnInit" << " called!");

	return UnInit_o();
}

using UnInit_t = void(__stdcall*)();
static UnInit_t UnInit_o;

static void UnInit_hook()
{
	DEBUG_TO_CONSOLE("UnInit" << " called!");

	return UnInit_o();
}

#pragma endregion

void InitHooks()
{
	//Allocate console
	if (AllocConsole())
	{
		FILE* f;
		SetConsoleTitleA(CONSOLE_TITLE);
		FILE* f;
		FILE* f2;
		freopen_s(&f, "conout$", "w", stdout);
		freopen_s(&f2, "conout$", "w", stderr);
	}

	MH_STATUS minhookEnableStat = MH_Initialize();
	if (minhookEnableStat == MH_OK)
	{
		HMODULE targetModule = GetModuleHandleA("Lossless.dll");

		AssignAddressToOriginalUsingModule(
			GetAdapterNames_o,
			"GetAdapterNames",
			targetModule);
		MAKE_HOOK(GetAdapterNames_o, GetAdapterNames_hook);

		AssignAddressToOriginalUsingModule(
			GetDisplayNames_o,
			"GetDisplayNames",
			targetModule);
		MAKE_HOOK(GetDisplayNames_o, GetDisplayNames_hook);

		AssignAddressToOriginalUsingModule(
			SetDriverSettings_o,
			"SetDriverSettings",
			targetModule);
		MAKE_HOOK(SetDriverSettings_o, SetDriverSettings_hook);

		AssignAddressToOriginalUsingModule(
			SetWindowsSettings_o,
			"SetWindowsSettings",
			targetModule);
		MAKE_HOOK(SetWindowsSettings_o, SetWindowsSettings_hook);

		AssignAddressToOriginalUsingModule(
			ApplySettings_o,
			"ApplySettings",
			targetModule);
		MAKE_HOOK(ApplySettings_o, ApplySettings_hook);

		AssignAddressToOriginalUsingModule(
			Init_o,
			"Init",
			targetModule);
		MAKE_HOOK(Init_o, Init_hook);

		AssignAddressToOriginalUsingModule(
			UnInit_o,
			"UnInit",
			targetModule);
		MAKE_HOOK(UnInit_o, UnInit_hook);

		AssignAddressToOriginalUsingModule(
			UnInit_o,
			"UnInit",
			targetModule);
		MAKE_HOOK(UnInit_o, UnInit_hook);

		int enableStat = MH_EnableHook(MH_ALL_HOOKS);
		if (enableStat != MH_OK) {} //Handle errors
	}
}