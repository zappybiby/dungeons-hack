#include <iostream>
#include "player.cpp"
#include "../utils/proc.cpp"

class Game
{
public:
	Game()
	{
		const int ADDRESS_OFFSET = 0x03D0A280;
		const wchar_t* APPLICATION_NAME = L"Dungeons-Win64-Shipping.exe";
		procId = GetProcId(APPLICATION_NAME);
		moduleBaseAddress = GetModuleBaseAddress(procId, APPLICATION_NAME);
		offsetBaseAddress = moduleBaseAddress + ADDRESS_OFFSET;
		hProcess = OpenProcess(PROCESS_ALL_ACCESS, NULL, procId);
		player = Player(hProcess, offsetBaseAddress);
		PrintPlayerValues();
	};
	void PrintPlayerValues()
	{
		std::cout << "Health: " << std::dec << player.GetHealth() << std::endl;
		std::cout << "X: " << std::fixed << player.GetXPosition() << std::endl;
		std::cout << "Y: " << std::fixed << player.GetYPosition() << std::endl;
		std::cout << "Z: " << std::fixed << player.GetZPosition() << std::endl;
	}
private:
	DWORD procId;
	uintptr_t moduleBaseAddress;
	uintptr_t offsetBaseAddress;
	HANDLE hProcess;
	Player player;
};