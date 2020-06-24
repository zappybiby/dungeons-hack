#include <iostream>
#include <vector>
#include <Windows.h>
#include "proc.cpp"

int main()
{
	//Get ProcId of the target process
	DWORD procId = GetProcId(L"Dungeons-Win64-Shipping.exe");

	//Base address of Process
	uintptr_t moduleBase = GetModuleBaseAddress(procId, L"Dungeons-Win64-Shipping.exe");

	//Get Handle to Process
	HANDLE hProcess = 0;
	hProcess = OpenProcess(PROCESS_ALL_ACCESS, NULL, procId);

	//Resolve base address of the pointer chain
	uintptr_t dynamicPtrBaseAddr = moduleBase + 0x03D0A280;

	std::cout << "DynamicPtrBaseAddr = " << "0x" << std::hex << dynamicPtrBaseAddr << std::endl;

	// offsets from dynamic pointer address
	std::vector<unsigned int> healthOffsets = {0x0, 0x20, 0xE38, 0x310, 0x308, 0x230, 0xF0};

	// Find dynamic memory address
	uintptr_t healthAddr = FindDMAAddy(hProcess, dynamicPtrBaseAddr, healthOffsets);

	std::cout << "healthAddr = " << "0x" << std::hex << healthAddr << std::endl;

	//Read Health Value
	int healthValue = 0;

	ReadProcessMemory(hProcess, (BYTE*)healthAddr, &healthValue, sizeof(healthValue), nullptr);
	std::cout << "Current health = " << std::dec << healthValue << std::endl;

	//Write to it
	//int newAmmo = 1337;
	//WriteProcessMemory(hProcess, (BYTE*)ammoAddr, &newAmmo, sizeof(newAmmo), nullptr);

	////Read out again
	//ReadProcessMemory(hProcess, (BYTE*)ammoAddr, &healthValue, sizeof(healthValue), nullptr);

	//std::cout << "New ammo = " << std::dec << healthValue << std::endl;

	getchar();
	return 0;
}
