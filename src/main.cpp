#include <cstdint>
#include <Windows.h>

typedef uint32_t UInt32;
typedef uint64_t UInt64;
#include "f4sevr/PluginAPI.h"

using namespace std;

// These two constants must be updated together, since in general the offset to the favorites input
// function will change when the game binary changes.
const uint32_t expectedRuntimeVersion = 0x010A08A0; // Expected runtime version for F4SEVR build: 0.6.21
const uintptr_t kFavoritesInputFunctionOffset = 0x9F4CC0;

void ApplyRuntimePatches(uintptr_t moduleBase) {
    uintptr_t targetFunctionAddress = moduleBase + kFavoritesInputFunctionOffset;

    if (targetFunctionAddress) {
        // 0xC3 is the x86/x64 machine code opcode for a 'RET' (Return) instruction.
        // Overwriting the first byte makes the input handler exit instantly when called.
        DWORD  oldProtect;
        uint8_t valueToWrite = 0xC3;
        VirtualProtect((void *)targetFunctionAddress, sizeof(uint8_t), PAGE_EXECUTE_READWRITE, &oldProtect);
        memcpy((void *)targetFunctionAddress, &valueToWrite, sizeof(uint8_t));
        VirtualProtect((void *)targetFunctionAddress, sizeof(uint8_t), oldProtect, &oldProtect);
    }
}

extern "C" {
    __declspec(dllexport) bool F4SEPlugin_Query(const F4SEInterface* f4se, PluginInfo* info) {
        info->infoVersion = PluginInfo::kInfoVersion;
        info->name = "DisableVRFavoritesWheel";
        info->version = 1;

        // Do not load if the runtime version does not match the supported one
        return f4se->runtimeVersion == expectedRuntimeVersion;
    }

    __declspec(dllexport) bool F4SEPlugin_Load(const F4SEInterface* /*f4se*/) {
        auto moduleBase = reinterpret_cast<uintptr_t>(GetModuleHandle(nullptr));
        ApplyRuntimePatches(moduleBase);
        return true;
    }
}
