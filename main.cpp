#include <iostream>
#include <vector>
#include <Windows.h>
#include "proc.cpp"

// offsets from dynamic pointer address
const std::vector<unsigned int> health_offsets = {0x0, 0x20, 0xE38, 0x310, 0x308, 0x230, 0xF0};
const std::vector<unsigned int> z_offsets = {0x0, 0xE8, 0x360, 0xE88, 0x20, 0x398, 0x398};
const std::vector<unsigned int> y_offsets = {0x0, 0x20, 0x3B0, 0xC48, 0x118, 0x398, 0x388};
const std::vector<unsigned int> x_offsets = {0x0, 0x20, 0x360, 0xEA8, 0x148, 0x398, 0x384};

int main()
{
	//Get ProcId of the target process
	const DWORD procId = GetProcId(L"Dungeons-Win64-Shipping.exe");

	//Base address of Process
	const uintptr_t moduleBase = GetModuleBaseAddress(procId, L"Dungeons-Win64-Shipping.exe");

	//Get Handle to Process
	HANDLE hProcess = 0;
	hProcess = OpenProcess(PROCESS_ALL_ACCESS, NULL, procId);

	//Resolve base address of the pointer chain
	const uintptr_t dynamicPtrBaseAddr = moduleBase + 0x03D0A280;

	std::cout << "DynamicPtrBaseAddr = " << "0x" << std::hex << dynamicPtrBaseAddr << std::endl;

	// Find dynamic memory address
	const uintptr_t health_addr = FindDMAAddy(hProcess, dynamicPtrBaseAddr, health_offsets);
	const uintptr_t z_addr = FindDMAAddy(hProcess, dynamicPtrBaseAddr, z_offsets);
	const uintptr_t x_addr = FindDMAAddy(hProcess, dynamicPtrBaseAddr, x_offsets);
	const uintptr_t y_addr = FindDMAAddy(hProcess, dynamicPtrBaseAddr, y_offsets);

	std::cout << "health_addr = " << "0x" << std::hex << health_addr << std::endl;
	std::cout << "z_addr = " << "0x" << std::hex << z_addr << std::endl;
	std::cout << "x_addr = " << "0x" << std::hex << x_addr << std::endl;
	std::cout << "y_addr = " << "0x" << std::hex << y_addr << std::endl;


	//Read  Value
	int healthValue = 0;
	float x_value = 0;
	float y_value = 0;
	float z_value = 0;

	ReadProcessMemory(hProcess, (BYTE*)health_addr, &healthValue, sizeof(healthValue), nullptr);
	ReadProcessMemory(hProcess, (BYTE*)z_addr, &z_value, sizeof(z_value), nullptr);
	ReadProcessMemory(hProcess, (BYTE*)x_addr, &x_value, sizeof(z_value), nullptr);
	ReadProcessMemory(hProcess, (BYTE*)y_addr, &y_value, sizeof(z_value), nullptr);

	std::cout << "Current health = " << std::dec << healthValue << std::endl;
	std::cout << "Current z = " << std::fixed << z_value << std::endl;
	std::cout << "Current x = " << std::fixed << x_value << std::endl;
	std::cout << "Current y = " << std::fixed << y_value << std::endl;


	//Write to it
	//int newAmmo = 1337;
	//WriteProcessMemory(hProcess, (BYTE*)ammoAddr, &newAmmo, sizeof(newAmmo), nullptr);

	////Read out again
	//ReadProcessMemory(hProcess, (BYTE*)ammoAddr, &healthValue, sizeof(healthValue), nullptr);

	//std::cout << "New ammo = " << std::dec << healthValue << std::endl;

	getchar();
	return 0;
}
