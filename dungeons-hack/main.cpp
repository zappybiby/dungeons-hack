#include <iostream>
#include <vector>
#include <Windows.h>
#include "proc.cpp"

// offsets from dynamic pointer address
const std::vector<unsigned int> health_offsets = { 0x0, 0x20, 0xE38, 0x310, 0x308, 0x230, 0xF0 };
const std::vector<unsigned int> z_offsets = { 0x0, 0xE8, 0x360, 0xE88, 0x20, 0x398, 0x398 };
const std::vector<unsigned int> y_offsets = { 0x0, 0x20, 0x3B0, 0xC48, 0x118, 0x398, 0x388 };
const std::vector<unsigned int> x_offsets = { 0x0, 0x20, 0x360, 0xEA8, 0x148, 0x398, 0x384 };

int main()
{
	//Get ProcId of the target process
	const DWORD procId = GetProcId(L"Dungeons-Win64-Shipping.exe");

	//Base address of Process
	const uintptr_t module_base = GetModuleBaseAddress(procId, L"Dungeons-Win64-Shipping.exe");

	//Get Handle to Process
	HANDLE h_process = nullptr;
	h_process = OpenProcess(PROCESS_ALL_ACCESS, NULL, procId);

	//Resolve base address of the pointer chain
	const uintptr_t dynamicPtrBaseAddr = module_base + 0x03D0A280;

	std::cout << "DynamicPtrBaseAddr = " << "0x" << std::hex << dynamicPtrBaseAddr << std::endl;

	// Find dynamic memory address
	const uintptr_t health_addr = FindDMAAddy(h_process, dynamicPtrBaseAddr, health_offsets);
	const uintptr_t z_addr = FindDMAAddy(h_process, dynamicPtrBaseAddr, z_offsets);
	const uintptr_t x_addr = FindDMAAddy(h_process, dynamicPtrBaseAddr, x_offsets);
	const uintptr_t y_addr = FindDMAAddy(h_process, dynamicPtrBaseAddr, y_offsets);

	std::cout << "health_addr = " << "0x" << std::hex << health_addr << std::endl;
	std::cout << "z_addr = " << "0x" << std::hex << z_addr << std::endl;
	std::cout << "x_addr = " << "0x" << std::hex << x_addr << std::endl;
	std::cout << "y_addr = " << "0x" << std::hex << y_addr << std::endl;


	//Read  Value
	int healthValue = 0;
	float x_value = 0;
	float y_value = 0;
	float z_value = 0;

	ReadProcessMemory(h_process, (BYTE*)health_addr, &healthValue, sizeof(healthValue), nullptr);
	ReadProcessMemory(h_process, (BYTE*)z_addr, &z_value, sizeof(z_value), nullptr);
	ReadProcessMemory(h_process, (BYTE*)x_addr, &x_value, sizeof(z_value), nullptr);
	ReadProcessMemory(h_process, (BYTE*)y_addr, &y_value, sizeof(z_value), nullptr);

	std::cout << "Current health = " << std::dec << healthValue << std::endl;
	std::cout << "Current z = " << std::fixed << z_value << std::endl;
	std::cout << "Current x = " << std::fixed << x_value << std::endl;
	std::cout << "Current y = " << std::fixed << y_value << std::endl;


	//Write to it
	//float new_x = 72537.24219;
	//WriteProcessMemory(h_process, (BYTE*)x_addr, &new_x, sizeof(new_x), nullptr);

	getchar();
	return 0;
}
