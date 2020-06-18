#include "../External/Memory.hpp"
#include <iostream>
#include <windows.h>

int main() {
    SetConsoleTitle("Memory Class Test");
    std::string TARGET_PROCESS_NAME = "Dungeons-Win64-Shipping.exe";

    int PLAYER_HEALTH_BASE = 0x03B0FED8;
    int PLAYER_HEALTH_OFFSET1 = 0x830;
    int PLAYER_HEALTH_OFFSET2 = 0x8;
    int PLAYER_HEALTH_OFFSET3 = 0x1D0;
    int PLAYER_HEALTH_OFFSET4 = 0x2A8;
    int PLAYER_HEALTH_OFFSET5 = 0x310;
    int PLAYER_HEALTH_OFFSET6 = 0x230;
    int PLAYER_HEALTH_OFFSET7 = 0xF0;

    Memory Memory;
    Memory.GetDebugPrivileges();
    const char* TARGET_PROCESS_NAME2 = TARGET_PROCESS_NAME.c_str();
    DWORD processId = Memory.GetProcessId(TARGET_PROCESS_NAME2);
    HANDLE processHandle = OpenProcess(PROCESS_ALL_ACCESS, false, processId);

    long baseAddress = Memory.GetModuleBase(processHandle, TARGET_PROCESS_NAME);
    std::cout << "Base address for module \"" << TARGET_PROCESS_NAME << "\" is " << baseAddress << " (in dec)..." << std::endl;

    float playerOneHealth = Memory.ReadFloat(processHandle, baseAddress + PLAYER_HEALTH_BASE + PLAYER_HEALTH_OFFSET1 + PLAYER_HEALTH_OFFSET2 + PLAYER_HEALTH_OFFSET3 + PLAYER_HEALTH_OFFSET4 + PLAYER_HEALTH_OFFSET5 + PLAYER_HEALTH_OFFSET6 + PLAYER_HEALTH_OFFSET7);

    std::cout << "Player one has " << playerOneHealth << " health!" << std::endl;

    std::cin.get();
    return 0;
}